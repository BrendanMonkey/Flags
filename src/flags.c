#include "include/flags.h"
#include <assert.h>
#include <stdio.h>

struct KeyValue {
	char* key;
	char* val;
};

int str_match(char* a, char* b) {

	assert(a != NULL);
	assert(b != NULL);

	while(*a != '\0' && *b != '\0' ) {
		if ( *a++ != *b++ ) {
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

int parse(int argc, char** argv, struct KeyValue* argt) {

	int i = 0; 
	int argt_i = 0;	
	
	while (i < argc) {

		char* arg_k = NULL;
		char* arg_v = NULL;
		char* arg_eq = NULL;
	
		// Assign arg_k with the first chars
		if ( get_chars(argc, argv, &i, &arg_k) == EOF || arg_k == NULL ) {
			break;
		}

		// Do we start with a flag char?
		if (arg_k[0] != FLAG_TAG) {
			continue;
		}

		// Assign flag_eq with the next chars
		if ( get_chars(argc, argv, &i, &arg_eq) == EOF || arg_eq == NULL ) {
			break;
		}

		int k = argt_i++;
		
		// Set the key ( we set it before finding the equal operator, as flags can be used as booleans -myBool)
		argt[k].key = arg_k;
	
		// set arg_k to true inside the lookup table.
		if (arg_eq[0] != FLAG_EQUAL) {
			continue;
		} 

		if ( get_chars(argc, argv, &i, &arg_v) == EOF || arg_v == NULL ) {
			break;
		}
	
		// Set our value
		argt[k].val = arg_v;

	};

	return argt_i;
};


int find_flag_kv_pair( int c, struct Flag* f, struct KeyValue* dst, struct KeyValue* kv) {

	for (int j = 0; j < c; j++ ) {

		struct KeyValue k = kv[j];

		if (k.key == NULL) {
			continue;
		}
		
		if (str_match(k.key, f->name)) {
			*dst = k;
			return 1;
		}
	}

	return 0;
}

int flags_parse(int argc, char** argv, struct Flags flags) {

	// key=-a, val = b
	// key=-c, val = a
	struct KeyValue argt[argc];

	// flags
	// key=-a
	// key=-b
	// key=-c
	// key=-d

	// Take a first parse on all our arguments.
	// 'c' is the real size of all the arguments.
	int c = parse(argc, argv, argt);

	struct Flags* f_ptr = &flags;

	for (int i = 0; i < flags.count; i++) {

		struct KeyValue f_kv;
		struct Flag* f = flags.flags[i];
		
		assert(f->name != NULL);

		if ( !find_flag_kv_pair(c, f, &f_kv, argt) ) {
			continue;
		}

		if (f_kv.val == NULL ) {
			if (f->type == Boolean) {
				f->data.boolean = 1;
			}
			continue;
		}
	
		switch(f->type) {
			case Boolean:
				f->data.boolean = str_match(f_kv.val, "true\0"); // Todo: check type!
				break;
			case Int:
	
				break;
			case String:
				f->data.string = f_kv.val;
				break;
		}
	
	}

	return -1; // Change me
}

struct Flags flags_new(struct Flag** flags, int count) {

	struct Flags f;
	f.flags = flags;
	f.count = count;
	
	return f;
};	