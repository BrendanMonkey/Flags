#include "include/flags.h"

int main(int argc, char** argv) {

	// Mock args
	char* a[] = {
		"-monkey\0",
		"=\0",
		"1\0",
		"-abc\0",
	};

	const int size = FLAG_VARG_LENGTH( a, char* );

	struct Flag flag_monkey;
	flag_monkey.name = "-monkey\0";


	struct Flag flag_abc;
	flag_monkey.name = "-abc\0";

	struct Flag* flags[] = {
		&flag_monkey,
		&flag_abc,
	};

	struct Flags f = flags_new(flags, LENGTH(flags, struct Flag*));

	flags_parse(size, a, f);

}