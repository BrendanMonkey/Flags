#include "ihct.h"
#include "include/flags.h"
#include <stdio.h>

IHCT_TEST(test_define_flag_and_get_value) {

	char* margs[] = {
		"a",
		"b"
	};

	int margs_len = LENGTH(margs, char*);

	struct Flag flag_print;
	flag_print.name = "print\0";
	flag_print.type = String;

	struct Flag* f[] = {
		&flag_print
	};

	struct Flags flags = flags_new(f, LENGTH(flags, struct Flag*));
	flags_parse(margs_len, margs, flags);

	IHCT_ASSERT(flag_print.data.string != NULL);


}


int main(int argc, char **argv) {

    return IHCT_RUN(argc, argv);
}