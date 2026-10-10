#include "../../src/include/flags.h"
#include <stdio.h>

int x = 0;
int y = 0;

int main(int argc, char** argv) {

	struct Flag flag_x_mul = flag_int(FLAG_STR("x"), &x);
	struct Flag flag_y_mul = flag_int(FLAG_STR("y"), &y);

	struct Flag f[] = {
		flag_x_mul,
		flag_y_mul
	};

	struct Flags flags = flags_new(f, LEN(f, struct Flag));
	flags_parse(argc, argv, flags);

	int out = x * y;
	printf("multiplication out=%d\n", out);
}