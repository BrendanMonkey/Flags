#include "ihct.h"
#include "include/flags.h"
#include <stdio.h>


IHCT_TEST(test_flag) {

	char* expected_str = FLAG_STR("'hello testing world!'");

	char* margs[] = {
		FLAG_STR("-print"),
		FLAG_STR("="),
		expected_str
	};

	int margs_len = LEN(margs, char*);

	char* print_str = NULL;
	struct Flag f[] = {
		flag_string(FLAG_STR("print"), &print_str),
	};

	struct Flags flags = flags_new(f, LEN(f, struct Flag));
	flags_parse(margs_len, margs, flags);

	IHCT_ASSERT(print_str != NULL);
	IHCT_ASSERT_STR(print_str, expected_str);
}

int main(int argc, char **argv) {

	return IHCT_RUN(argc, argv);
}