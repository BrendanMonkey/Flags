#include "include/flags.h"

int main(int argc, char** argv) {

	// Mock args
	char* a[] = {
		"-monkey\0",
		"=\0",
		"world!\0"
	};

	const int size = LENGTH(a, char*);
	char* to[size*2];

	parse(size, a, to);

}