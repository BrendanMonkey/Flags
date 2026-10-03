#include "include/flags.h"

int calc_argc(int argc) {	
	return argc * 2;
}

int find_char(int argc, char** argv, int s, char c) {

	for (int i = s; i < argc; i++) {
		char* argr = argv[i];
		
		if ( argr[0] == c ) {
			return i;
		}
	}

	return -1;
}

inline int get_chars(int argc, char** argv, int* i, char* c) {

	int i_c = *i;

	if ( i_c >= argc ) {
		return -1;
	}

	c = argv[i_c];

	*i+=1;

	return i_c;
}

int parse(int argc, char** argv, char** argt) {

	int i = 0; 
	
	while (i < argc) {

		char* arg_k;
		char* arg_v;
		char* arg_eq;
	
		// Assign arg_k with the first chars
		if ( get_chars(argc, argv, &i, arg_k) == -1 ) {
			break;
		}

		// Do we start with a flag char?
		if (arg_k[0] != FLAG_TAG) {
			continue;
		}

		// Assign flag_eq with the next chars
		if ( get_chars(argc, argv, &i, arg_eq) == -1 ) {
			break;
		}
	
		// set arg_k to true inside the lookup table.
		if (arg_eq[0] != FLAG_TAG) {
			continue;
		}

		if ( get_chars(argc, argv, &i, arg_v) == -1 ) {
			break;
		}
	
	};

	return 0;
};
