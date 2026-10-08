#include "include/flags.h"
#include <stdio.h>

struct KeyValue {
	char* key;
	char* val;
};

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

int str_match(char* a, char* b) {

	assert(a != NULL);
	assert(b != NULL);

	while(*a != '\0' && *b != '\0' ) {
		char a1 = *a++;
		char b1 = *b++;

		if ( a1 != b1 ) {
			return 0;
		}	

		// This needs to go ASAP, it is caused by me not wanting to heap allocate anything.
		// So, if -key=value, this isn't broken into [-key, =, value], and if we want to seperate the key, we need to heap allocate the key.
		if ( a1 == '=' || b1 =='=' ) {
			return 1;
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
int int_from_str(char* c, int* to) {

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
int break_arg_k(char* arg_k, char** arg_v, int s_off) {

	int sep_e = 0;
	int sep_i = s_off;

	char* arg_k_cp = arg_k;

	while(arg_k_cp[sep_i] != '\0') {
		if ( arg_k_cp[sep_i] == '=' ) {
			sep_e = sep_i;
			break;
		}
		sep_i++;
	}

	if ( sep_e <= 0 && (arg_k[sep_e] != '=') ) {		
		return 0;
	}

	if ( arg_k[sep_e+1] == '\0' ) {
		return 0;
	} 
	
	char* off = arg_k + (sep_e+1); // Offset in memory.
	*arg_v = off;
	
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
		kvs[k].key = arg_k; 
		kvs[k].val = NULL;
		
		get_chars(argc, argv, &i, &arg_eq);

		// This means arg_k likely holds the key and value.
		if ( arg_eq == NULL || arg_eq[0] != FLAG_EQUAL ) {

			if (arg_eq != NULL && arg_eq[0] == FLAG_TAG  ) {
				i--; // Go back 1.		
			}
						
			int eq_i = find_char(arg_k, '=');

			if ( eq_i == EOF ) {
				continue;
			}
			
			if (break_arg_k(arg_k, &arg_v, eq_i)) {
				arg_eq = NULL;		
			}
		}

		// arg_eq holds the value.
		if ( arg_eq != NULL){
			if ( arg_eq[0] == '=' ) {
				break_arg_k(arg_eq,&arg_v, 0);
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

// A hash map would be nice, as this is a O(N*M) where N is the count of pairs to search, and M is the length of the pairs key.
int search_kvs_for_flag( int c, struct Flag* f, struct KeyValue* dst, struct KeyValue* kvs) {

	for (int i = 0; i < c; i ++ ) {

		struct KeyValue k = kvs[i];

		if (k.key == NULL) {
			continue;
		}

		char* a = k.key;
		a++; // Sub out the '-', we shouldaaa done this earlier..
		
		if (str_match(a, f->name)) {
			*dst = k;
			return 1;
		}
	}

	return 0;
}

void map_kv_data_to_flag(struct Flag* f, struct KeyValue f_kv) {
	switch(f->type) {
		case Boolean:
			{
				int bool_val = (f_kv.val[0] == '1' ? 1 : (f_kv.val[0] == '0' ? 0 : -1));
				
				if ( bool_val != -1 ) {
					f->data.boolean = bool_val;
					break;
				}
				
				f->data.boolean = str_match(f_kv.val, "true\0") || str_match(f_kv.val, "false\0"); 
			}
			break;
		case Int:
			int_from_str(f_kv.val, &f->data.integer);
			break;
		case String:	
			f->data.string = f_kv.val;
			break;
	}
}

int flags_parse(int argc, char** argv, struct Flags flags) {

	// This is always bigger than it needs to be...
	// I didn't think of that while designing the parser.
	// It shouldn't be a problem??? Maybe it would cause a stack overflow, if you had a load of args.
	struct KeyValue kvs[argc];

	// Take a first parse on all our arguments.
	// 'c' is the real size of all the arguments.
	int kvs_c = parse_chars(argc, argv, kvs);

	for (int i = 0; i < flags.count; i++) {

		struct KeyValue f_kv;
		struct Flag* f = flags.flags[i];
	
		assert(f->name != NULL); // You messed up if a flag name is null lmao.

		if ( !search_kvs_for_flag(kvs_c, f, &f_kv, kvs) ) {
			continue;
		}

		if (f_kv.val == NULL ) {
			continue;
		}

		map_kv_data_to_flag(f, f_kv);
	}

	return kvs_c;
}

struct Flags flags_new(struct Flag** flags, int count) {

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

struct Flag flag_string(char* name, char* def) {
	
	struct Flag f = flag_new(name, String);
	f.data.string = def;
	
	return f;
}

struct Flag flag_int(char* name, int def) {
	
	struct Flag f = flag_new(name, Int);
	f.data.integer = def;
	
	return f;
}

struct Flag flag_boolean(char* name, int def) {

	struct Flag f = flag_new(name, Boolean);
	f.data.boolean = def;
	
	return f;
}