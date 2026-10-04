#ifndef MDEV_FLAGS
#define MDEV_FLAGS

#define FLAG_TAG '-'
#define FLAG_EQUAL '='

#include "stdio.h"
#include "assert.h"

#define FLAG_NULL_VALUE "aa"

#define LENGTH(a, x) (sizeof(a) / sizeof(x))

// (/3) is the ideal size, realisically the size will always be a bit bigger than that. 
// That is fine though as we avoid heap allocations!
#define FLAG_VARG_LENGTH(a, x) (LENGTH(a, x) / 3) + 1

int int_from_str(char* c);

enum Type {
	Int,
	Boolean,
	String,
};

union TypeData {
	int integer;
	int boolean;
	char* string;
};

struct Flag {
	char* name;
	enum Type type; // I might move this over to a macro, I just really, really hate macro syntax.
	union TypeData data;
};

struct Flags {
	int count;
	struct Flag** flags; // I think this creates fragmentation, although it makes using flags nicer, so the tradeoff from memory lookup is worth it.
};

struct Flags flags_new(struct Flag** flags, int count) ;

inline int calc_argc(int argc);

int flags_parse(int argc, char** argv, struct Flags flags);

#endif