#include "ihct.h"
#include "include/flags.h"
#include <stdio.h>

/*
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


IHCT_TEST(test_missing_rune) {

	char* margs[] = {
		"-print\0", 
		"money\0",
		"-a\0",
	};

	int margs_len = LENGTH(margs, char*);

	struct Flag flag_print_a = flag_string("print\0", NULL);
	struct Flag flag_a = flag_boolean("a\0", false);
	
	struct Flag* f[] = {
		&flag_print_a,
		&flag_a
	};

	struct Flags flags = flags_new(f, LENGTH(f, struct Flag*));
	flags_parse(margs_len, margs, flags);

	printf("%s\n", flag_print_a.data.string);
	// This should be null!!!
	IHCT_ASSERT(flag_print_a.data.string == NULL);

	IHCT_ASSERT(flag_a.data.boolean == true);

}

*/


int main(int argc, char **argv) {

	char* margs[] = {
		"-print\0", 
		"=\0",
		"money\0",
		"-a\0",
	};

	int margs_len = LENGTH(margs, char*);

	struct Flag flag_print_a = flag_string("print\0", NULL);
	struct Flag flag_a = flag_boolean("a\0", false);
	
	struct Flag* f[] = {
		&flag_print_a,
		&flag_a
	};

	struct Flags flags = flags_new(f, LENGTH(f, struct Flag*));
	flags_parse(margs_len, margs, flags);

	printf("%s\n", flag_print_a.data.string);
	// This should be null!!!

    return 0;
}