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

IHCT_TEST(test_define_random) {

	char* monkey_str = "test\0";
	char* margs[] = {
		"-print\0",
		"-monkey\0",
		"=\0",
		monkey_str,
		"'hello testing world!'\0",
		"-c\0",
	};

	int margs_len = LENGTH(margs, char*);

	struct Flag flag_print = flag_string("print\0", NULL);
	struct Flag flag_monkey = flag_string("monkey\0", NULL);
	
	struct Flag flag_monkey2 = flag_string("monkey2\0", NULL);
	
	struct Flag* f[] = {
		&flag_monkey,
		&flag_print,
	};

	struct Flags flags = flags_new(f, LENGTH(f, struct Flag*));
	flags_parse(margs_len, margs, flags);

	// This should be null!!!
	IHCT_ASSERT(flag_print.data.string == NULL);
	
	// This should not be null!!!
	IHCT_ASSERT(flag_monkey.data.string != NULL);
	IHCT_ASSERT(flag_monkey.data.string == monkey_str);
	
//	IHCT_ASSERT(flag_a.data.boolean == 1);

}

IHCT_TEST(test_boolean_values) {

	char* margs[] = {
		"-a\0",
		"-b\0",
		"=\0",
		"1\0",
		"-c\0",
		"=\0",
		"0\0",
		"-d\0",
		"=\0",
		"true\0",
	};

	int margs_len = LENGTH(margs, char*);

	struct Flag flag_a = flag_boolean("a\0", 0);
	struct Flag flag_b = flag_boolean("b\0", 0);
	struct Flag flag_c = flag_boolean("c\0", 0);
	struct Flag flag_d = flag_boolean("d\0", 0);

	struct Flag* f[] = {
		&flag_a,
		&flag_b,
		&flag_c,
		&flag_d,
	};

	struct Flags flags = flags_new(f, LENGTH(f, struct Flag*));
	flags_parse(margs_len, margs, flags);

	IHCT_ASSERT(flag_a.data.boolean == 1);
	IHCT_ASSERT(flag_b.data.boolean == 1);
	IHCT_ASSERT(flag_c.data.boolean == 0);
	IHCT_ASSERT(flag_d.data.boolean == 1);
	
}

IHCT_TEST(test_int_values) {

	char* margs[] = {
		"-a\0",
		"=\0",
		"123\0",
		"-b\0",
		"=\0",
		"12a\0",
		"-c\0",
		"=\0",
		"-9\0"
	};

	int margs_len = LENGTH(margs, char*);

	struct Flag flag_a = flag_int("a\0", 0);
	struct Flag flag_b = flag_int("b\0", 0);
	struct Flag flag_c = flag_int("c\0", 0);

	struct Flag* f[] = {
		&flag_a,
		&flag_b,
		&flag_c,
	};

	struct Flags flags = flags_new(f, LENGTH(f, struct Flag*));
	flags_parse(margs_len, margs, flags);

	IHCT_ASSERT(flag_a.data.integer == 123);
	IHCT_ASSERT(flag_b.data.integer == 0);
	IHCT_ASSERT(flag_c.data.integer == -9);
}

int main(int argc, char **argv) {

	return IHCT_RUN(argc, argv);
}