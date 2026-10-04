#include "ihct.h"
#include "include/flags.h"
#include <stdio.h>


IHCT_TEST(test_define_flag_and_get_value) {

	char* expected_str = "'hello testing world!'\0";
	char* margs[] = {
		"-print\0",
		"=\0",
		expected_str
	};

	int margs_len = LENGTH(margs, char*);

	struct Flag flag_print = flag_string("print\0", NULL);

	struct Flag* f[] = {
		&flag_print
	};

	struct Flags flags = flags_new(f, LENGTH(f, struct Flag*));
	flags_parse(margs_len, margs, flags);

	IHCT_ASSERT(flag_print.data.string != NULL);

	IHCT_ASSERT_STR(flag_print.data.string, expected_str);

	printf("%s\n", flag_print.data.string);
}

IHCT_TEST(test_define_and_misspell) {

	int x = 10;
	char* margs[] = {
		"-rint\0", // Misspell the command!
		"=\0",
		"'hello testing world!'\0"
	};

	int margs_len = LENGTH(margs, char*);

	struct Flag flag_print = flag_string("print\0", NULL);
	
	struct Flag* f[] = {
		&flag_print
	};

	struct Flags flags = flags_new(f, LENGTH(f, struct Flag*));
	flags_parse(margs_len, margs, flags);

	// This should be null!!!
	IHCT_ASSERT(flag_print.data.string == NULL);

}



IHCT_TEST(test_define) {

	char* margs[] = {
		"-print\0", // Misspell the command!
		"'hello testing world!'\0",
		"-a",
	};

	int margs_len = LENGTH(margs, char*);

	struct Flag flag_print = flag_string("print\0", NULL);
	
	struct Flag* f[] = {
		&flag_print
	};

	struct Flags flags = flags_new(f, LENGTH(f, struct Flag*));
	flags_parse(margs_len, margs, flags);

	// This should be null!!!
	IHCT_ASSERT(flag_print.data.string == NULL);
	
	
}
int main(int argc, char **argv) {

    return IHCT_RUN(argc, argv);
}