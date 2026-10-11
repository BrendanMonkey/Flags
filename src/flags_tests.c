#include "ihct.h"
#include "include/flags.h"
#include <stdio.h>

IHCT_TEST(test_flag_string) {

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

IHCT_TEST(test_flag_int) {

	char* margs[] = {
		FLAG_STR("-x"),
		FLAG_STR("="),
		FLAG_STR("1"),
	};

	int margs_len = LEN(margs, char*);

	int x = -1;
	struct Flag f[] = {
		flag_int(FLAG_STR("x"), &x),
	};

	struct Flags flags = flags_new(f, LEN(f, struct Flag));
	flags_parse(margs_len, margs, flags);

	IHCT_ASSERT(x == 1);
}

IHCT_TEST(test_flag_explicit_boolean) {

	char* margs[] = {
		FLAG_STR("-x"),
		FLAG_STR("="),
		FLAG_STR("true"),
		FLAG_STR("-y"),
		FLAG_STR("="),
		FLAG_STR("1"),
	};

	int margs_len = LEN(margs, char*);

	int x = 0;
	int y = 0;

	struct Flag f[] = {
		flag_boolean(FLAG_STR("x"), &x),
		flag_boolean(FLAG_STR("y"), &y),
	};

	struct Flags flags = flags_new(f, LEN(f, struct Flag));
	flags_parse(margs_len, margs, flags);

	IHCT_ASSERT(x);
	IHCT_ASSERT(y);
}

IHCT_TEST(test_flag_implicit_boolean) {

	char* margs[] = {
		FLAG_STR("-x"),
	};

	int margs_len = LEN(margs, char*);

	int x = 0;
	struct Flag f[] = {
		flag_boolean(FLAG_STR("x"), &x),
	};

	struct Flags flags = flags_new(f, LEN(f, struct Flag));
	flags_parse(margs_len, margs, flags);

	IHCT_ASSERT(x);
}

IHCT_TEST(test_flag_negative_int) {

	char* margs[] = {
		FLAG_STR("-x"),
		FLAG_STR("="),
		FLAG_STR("-100"),
	};

	int margs_len = LEN(margs, char*);

	int x = 0;
	struct Flag f[] = {
		flag_int(FLAG_STR("x"), &x),
	};

	struct Flags flags = flags_new(f, LEN(f, struct Flag));
	flags_parse(margs_len, margs, flags);

	IHCT_ASSERT(x == -100);
}

IHCT_TEST(test_missing_equal_operator) {

	char* margs[] = {
		FLAG_STR("-x"),
		FLAG_STR("10"),
		FLAG_STR("-y"),
		FLAG_STR("="),
		FLAG_STR("-100"),
		FLAG_STR("-z"),
		FLAG_STR("="),
	};

	int margs_len = LEN(margs, char*);

	int x = 0;
	int y = 0;
	int z = 0;
	struct Flag f[] = {
		flag_int(FLAG_STR("x"), &x),
		flag_int(FLAG_STR("y"), &y),
		flag_int(FLAG_STR("z"), &z),
	};

	struct Flags flags = flags_new(f, LEN(f, struct Flag));
	flags_parse(margs_len, margs, flags);

	IHCT_ASSERT(x == 0);
	IHCT_ASSERT(y == -100);
	IHCT_ASSERT(z == 0);
}

int main(int argc, char **argv) {

	return IHCT_RUN(argc, argv);
}