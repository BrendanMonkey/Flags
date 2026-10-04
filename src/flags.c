#include "include/flags.h"
#include <stdio.h>
#include <string.h>

inline int calc_argc(int argc) {	
	return argc * 2;
}

int get_chars(int argc, char** argv, int* i, char** c) {

	int i_c = *i;

	if ( i_c >= argc ) {
		return -1;
	}

	char* t = argv[i_c];
	
	*c = t;

	(*i)++;

	return i_c;
}

int parse(int argc, char*** argv, char*** argt) {

	int i = 0; 
	int argt_i = 0;	
	while (i < argc) {

		char* arg_k = NULL;
		char* arg_v = NULL;
		char* arg_eq = NULL;
	
		// Assign arg_k with the first chars
		if ( get_chars(argc, *argv, &i, &arg_k) == -1 ) {
			break;
		}

		// Do we start with a flag char?
		if (arg_k[0] != FLAG_TAG) {
			continue;
		}

		// Assign flag_eq with the next chars
		if ( get_chars(argc, *argv, &i, &arg_eq) == -1 ) {
			continue;
		}
	
		// set arg_k to true inside the lookup table.
		if (arg_eq[0] != FLAG_EQUAL) {
			continue;
		}

		if ( get_chars(argc, *argv, &i, &arg_v) == -1 ) {
			break;
		}

		*argt[0] = "a";
		//*argt[argt_i++] = arg_v;

	};

	return 0;
};
