#include "ihct.h"
#include "include/flags.h"
#include <stdio.h>

IHCT_TEST(test_define_flag_and_get_value) {

	char* expected_str = "'hellotesting world!'\0";
	char* margs[] = {
		"-print\0",
		"=\0",
		expected_str
	};

	int margs_len = LENGTH(margs, char*);

	struct Flag flag_print = flag_string(FLAG_STR("print"), NULL);

	struct Flag* f[] = {
		&flag_print
	};

	struct Flags flags = flags_new(f, LENGTH(f, struct Flag*));
	flags_parse(margs_len, margs, flags);

	IHCT_ASSERT(flag_print.data.string != NULL);

	IHCT_ASSERT_STR(flag_print.data.string, expected_str);
}

IHCT_TEST(test_define_and_misspell_argv) {

	int x = 10;
	char* margs[] = {
		"-rint\0", // Misspell the command!
		"=\0",
		"'hello testing world!'\0"
	};

	int margs_len = LENGTH(margs, char*);

	struct Flag flag_print = flag_string(FLAG_STR("print"), NULL);
	
	struct Flag* f[] = {
		&flag_print
	};

	struct Flags flags = flags_new(f, LENGTH(f, struct Flag*));
	flags_parse(margs_len, margs, flags);

	// This should be null!!!
	IHCT_ASSERT(flag_print.data.string == NULL);

}

IHCT_TEST(test_boolean_flags) {

	char* margs[] = {
		"-a\0",
		"-b\0",
		"=\0",
		"1\0",
		"-c\0",
		"=\0",
		"-d\0",
		"=\0",
		"0\0",
	};

	int margs_len = LENGTH(margs, char*);

	struct Flag flag_a = flag_boolean(FLAG_STR("a"), 1);
	struct Flag flag_b = flag_boolean(FLAG_STR("b"), 0);
	struct Flag flag_c = flag_boolean(FLAG_STR("c"), 0);
	struct Flag flag_d = flag_boolean(FLAG_STR("d"), 1);

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

IHCT_TEST(test_int_flags) {

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

	struct Flag flag_a = flag_int(FLAG_STR("a"), 0);
	struct Flag flag_b = flag_int(FLAG_STR("b"), 0);
	struct Flag flag_c = flag_int(FLAG_STR("c"), 0);

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

IHCT_TEST(test_weird_parsing_strings_1) {

	char* margs[] = {
		"-a\0",
		"=1\0",
	};

	int margs_len = LENGTH(margs, char*);

	struct Flag flag_a = flag_int(FLAG_STR("a"), 0);
	
	struct Flag* f[] = {
		&flag_a,
	};

	struct Flags flags = flags_new(f, LENGTH(f, struct Flag*));
	flags_parse(margs_len, margs, flags);

	IHCT_ASSERT(flag_a.data.integer == 1);
	
}

IHCT_TEST(test_weird_parsing_strings_2) {

	char* margs[] = {
		"-a=\0",
		"1\0",
	};

	int margs_len = LENGTH(margs, char*);

	struct Flag flag_a = flag_int(FLAG_STR("a"), 0);
	
	struct Flag* f[] = {
		&flag_a,
	};

	struct Flags flags = flags_new(f, LENGTH(f, struct Flag*));
	flags_parse(margs_len, margs, flags);

	IHCT_ASSERT(flag_a.data.integer == 1);
	
}

IHCT_TEST(test_weird_parsing_strings_3) {

	char* margs[] = {
		"-a=1\0",
	};

	int margs_len = LENGTH(margs, char*);

	struct Flag flag_a = flag_int(FLAG_STR("a"), 0);
	
	struct Flag* f[] = {
		&flag_a,
	};

	struct Flags flags = flags_new(f, LENGTH(f, struct Flag*));
	flags_parse(margs_len, margs, flags);

	IHCT_ASSERT(flag_a.data.integer == 1);
	
}

int main(int argc, char **argv) {

	return IHCT_RUN(argc, argv);
}