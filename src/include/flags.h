#ifndef MDEV_FLAGS
#define MDEV_FLAGS

#define FLAG_TAG '-'
#define FLAG_EQUAL '='

#include "stdio.h"

#define LENGTH(a, x) (sizeof(a) / sizeof(x))

struct Flag {
	char* name;
};

struct Flags {
	struct Flag* flags;
	int count;
};

struct Flags flags_new(struct Flag* flags, int count) ;

inline int calc_argc(int argc);

int parse(int argc, char** argv, char** argt);

#endif