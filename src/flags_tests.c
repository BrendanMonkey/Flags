#include "ihct.h"
#include "include/flags.h"
#include <stdio.h>

IHCT_TEST(test_define_flag_and_get_value) {

	char* margs[] = {
		"-print\0",
		"=\0",
		"'hello testing world!'\0"
	};

	int margs_len = LENGTH(margs, char*);

	struct Flag flag_print;
	flag_print.name = "print\0";
	flag_print.type = String;

	struct Flag* f[] = {
		&flag_print
	};

	struct Flags flags = flags_new(f, LENGTH(f, struct Flag*));
	flags_parse(margs_len, margs, flags);

	IHCT_ASSERT(flag_print.data.string != NULL);

	printf("%s\n", flag_print.data.string);
}


int main(int argc, char **argv) {

    return IHCT_RUN(argc, argv);
}