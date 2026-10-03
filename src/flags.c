#include "include/flags.h"

int calc_argc(int argc) {	
	return argc * 2;
}



int parse(int argc, char** argv, char** argt) {

	int argt_c = calc_argc(argc);


	for (int i = 0; i < argc; i++) {
		
		char* argr = argv[i];
		
		if ( argr[0] != FLAG_TAG ) {
			continue;
		}

	}




};
