#include "include/flags.h"

int main(int argc, char** argv) {


	printf("%d\n", int_from_str("123\0"));

	// Mock args
	char* a[] = {
		"-monkey\0",
		"=\0",
		"1\0",
		"-abc\0",
	};

	const int size = LENGTH( a, char* );

	struct Flag flag_monkey;
	flag_monkey.name = "-monkey\0";
	flag_monkey.type = String;

	struct Flag flag_abc;
	flag_abc.name = "-abc\0";
	flag_abc.type = Boolean;

	struct Flag* flags[] = {
		&flag_monkey,
		&flag_abc,
	};

	struct Flags f = flags_new(flags, LENGTH(flags, struct Flag*));

	flags_parse(size, a, f);
}