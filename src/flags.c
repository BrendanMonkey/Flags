#include "include/flags.h"
#include <stdio.h>

struct KeyValue {
	int key_eq; // Does the key have an equal operator, and where is the location?
	char* key;
	char* val;
};

int max(int a, int b) {
	if (a > b ) {
		return a;
	}
	return b;
}

int find_char(char* a, char t) {

	int i = 0; 

	while(*a != '\0') {
		if ( *a++ == t ) {
			return i;
		}
		i++;
	}

	return EOF;
}

// 's' is an integer used to control how many N chars should be searched. 
int str_match(char* a, char* b, int s) {

	assert(a != NULL);
	assert(b != NULL);

	int i = 0;
	while(*a != '\0' && *b != '\0' && (s == 0 || i++ < s)) {

		char a1 = *a++;
		char b1 = *b++;

		if ( a1 != b1 ) {
			return 0;
		}	
	}

	return 1;
}

int get_chars(int argc, char** argv, int* i, char** c) {

	int i_c = *i;

	if ( i_c >= argc ) {
		return EOF;
	}

	char* t = argv[i_c];
	
	*c = t;
	(*i)++;

	return i_c;
}

// I used a pointer as this allows for negative integers,
// so validating if this function succeeded is hard if we just return EOF or something.
int str_to_int(char* c, int* to) {

	int x = 0;
	int m = 1;

	// Is this a negative integer?
	if ( *c == '-' ) {
		m = -1; 
		c++;
	}
	
	while(*c != '\0') {

		int n = *c++ - '0';

		if ( n < 0 || n > 9 ) {
			return 0;
		}
	
		x = (x * 10) + n;
	}

	// Support for negatives.
	x *= m; 
	*to = x; 

	return 1;
}

// I think break_arg_k is doing too much work.
// it handles cases like -a=b, and [-a, =b] where a is a seperate string from b.
int break_arg_k(char* arg_k, char** arg_v, int* eq_pos, int s_off) {

	int sep_e = 0;
	int sep_i = s_off;

	char* arg_k_cp = arg_k;

	// Todo: change this to 'find_char'
	while(arg_k_cp[sep_i] != '\0') {
		if ( arg_k_cp[sep_i] == FLAG_EQUAL ) {
			sep_e = sep_i;
			break;
		}
		sep_i++;
	}

	if ( sep_e <= 0 && (arg_k[sep_e] != FLAG_EQUAL) ) {		
		return 0;
	}

	if ( arg_k[sep_e+1] == '\0' ) {
		return 0;
	} 
	
	char* off = arg_k + (sep_e+1); // Offset in memory.
	*arg_v = off;
	*eq_pos = max(sep_e, 0);
	
	return 1;
}

// I kinda hate this parser, like, even after re-writing it, i hate it.
int parse_chars(int argc, char** argv, struct KeyValue* kvs) {

	int i = 0; 
	int kvs_i = 0;	
	
	while (i < argc) {

		char* arg_k = NULL;
		char* arg_v = NULL;
		char* arg_eq = NULL;

		if (get_chars(argc, argv, &i, &arg_k) == EOF) {
			break;
		}

		// If there is no flag_tag, continue.
		if ( arg_k[0] != FLAG_TAG ) {
			continue;
		}

		int k = kvs_i++;

		struct KeyValue* kv = &kvs[k];
		kv->key_eq = 0;
		kv->key = arg_k; 
		kv->val = NULL;
		
		get_chars(argc, argv, &i, &arg_eq);

		// This means arg_k likely holds the key and value.
		if ( arg_eq == NULL || arg_eq[0] != FLAG_EQUAL ) {

			if (arg_eq != NULL && arg_eq[0] == FLAG_TAG  ) {
				i--; // Go back 1.		
			}
						
			int eq_i = find_char(arg_k, FLAG_EQUAL);

			if ( eq_i == EOF ) {
				continue;
			}
			
			// eq_i is where the equal char starts.
			if (break_arg_k(arg_k, &arg_v, &kv->key_eq, eq_i)) {
				arg_eq = NULL;		
			}
		}

		// arg_eq holds the value.
		if ( arg_eq != NULL){
			if ( arg_eq[0] == FLAG_EQUAL ) {
				break_arg_k(arg_eq,&arg_v, &kv->key_eq, 0);
			} else {
				arg_v = arg_eq;
			}
		}

		// unpack our value.
		if ( arg_v == NULL ) {
			get_chars(argc, argv, &i, &arg_v);
		}

		kvs[k].val = arg_v;

	};

	return kvs_i;
};

// A hash map would be nice, as this is a O(N*M) where N is the count of pairs to search, and M is the LEN of the pairs key.
int search_kvs_for_flag( int c, struct Flag* f, struct KeyValue* dst, struct KeyValue* kvs) {

	for (int i = 0; i < c; i ++ ) {

		struct KeyValue k = kvs[i];

		if (k.key == NULL) {
			continue;
		}

		char* a = k.key;
		a++; // Sub out the '-', we shouldaaa done this earlier..
		
		if (str_match(a, f->name, k.key_eq)) {
			*dst = k;
			return 1;
		}
	}

	return 0;
}

void map_kv_data_to_flag(struct Flag* f, struct KeyValue kv) {
	switch(f->type) {
		case Boolean:
			{
				int bool_val = (kv.val[0] == '1' ? 1 : (kv.val[0] == '0' ? 0 : -1));
				
				if ( bool_val != -1 ) {
					*f->data.integer = bool_val;
					break;
				}
				
				*f->data.integer = str_match(kv.val, "true\0", 0);
			}
			break;
		case Int:
			str_to_int(kv.val, f->data.integer);
			break;
		case String:	
			*f->data.string = kv.val;
			break;
	}
}

int flags_parse(int argc, char** argv, struct Flags flags) {

	// This is always bigger than it needs to be...
	// I didn't think of that while designing the parser.
	// It shouldn't be a problem??? Maybe it could cause a stack overflow, if you had a load of args.
	struct KeyValue kvs[argc];

	// Take a first parse on all our arguments.
	// 'c' is the real size of all the arguments.
	int kvs_c = parse_chars(argc, argv, kvs);

	for (int i = 0; i < flags.count; i++) {

		struct KeyValue kv;
		struct Flag f = flags.flags[i];
	
		assert(f.name != NULL); // You messed up if a flag name is null lmao.

		if ( !search_kvs_for_flag(kvs_c, &f, &kv, kvs) ) {
			continue;
		}

		if (kv.val == NULL ) {
			if ( f.type != Boolean ) {
				continue;
			}

			kv.val = FLAG_STR("1");
		}

		map_kv_data_to_flag(&f, kv);
	}

	return kvs_c;
}

struct Flags flags_new(struct Flag* flags, int count) {

	struct Flags f;
	f.flags = flags;
	f.count = count;
	
	return f;
};	

struct Flag flag_new(char* name, enum Type type) {
	struct Flag f;
	f.name = name;
	f.type = type;
	return f;
}

struct Flag flag_string(char* name, char** ptr) {
	
	struct Flag f = flag_new(name, String);
	f.data.string = ptr;
	
	return f;
}

struct Flag flag_int(char* name, int* ptr) {
	
	struct Flag f = flag_new(name, Int);
	f.data.integer = ptr;
	
	return f;
}

struct Flag flag_boolean(char* name, int* ptr) {

	struct Flag f = flag_new(name, Boolean);
	f.data.integer = ptr;
	
	return f;
}