#include "include/flags.h"
#include <stdio.h>


int main(int argc, char** argv) {


	char* a[] = {
		"-monkey\0",
		"=\0",
		"world!\0"
	};

	const int size = (sizeof(a) / sizeof(char*));
	char* to[size*2];


	parse(size, a, to);


}