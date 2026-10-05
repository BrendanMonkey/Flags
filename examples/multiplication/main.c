#include "../../src/include/flags.h"
#include <stdio.h>

int main(int argc, char** argv) {

	struct Flag flag_x_mul = flag_int("x\0", 5);
	struct Flag flag_y_mul = flag_int("y\0", 10);

	struct Flag* f[] = {
		&flag_x_mul,
		&flag_y_mul
	};

	struct Flags flags = flags_new(f, FLAG_LENGTH(f));
	flags_parse(argc, argv, flags);

	int out = flag_x_mul.data.integer * flag_y_mul.data.integer;
	printf("multiplication out=%d\n", out);
}