#include "../../src/include/flags.h"
#include <stdio.h>

int main(int argc, char** argv) {

	int x = 0;
	int y = 0;

	struct Flag f[] = {
		flag_int(FLAG_STR("x"), &x),
		flag_int(FLAG_STR("y"), &y)
	};

	struct Flags flags = flags_new(f, LEN(f, struct Flag));
	flags_parse(argc, argv, flags);

	int out = x * y;
	printf("multiplication out=%d\n", out);
}