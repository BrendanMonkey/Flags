#ifndef MDEV_FLAGS
#define MDEV_FLAGS

#define FLAG_TAG '-'
#define FLAG_EQUAL '='

#include "stdio.h"
#include "assert.h"

#define FLAG_STR(a) a "\0"
#define LENGTH(a, x) (sizeof(a) / sizeof(x))
#define FLAG_LENGTH(a) (sizeof(a) / sizeof(struct Flag*))

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


int flags_parse(int argc, char** argv, struct Flags flags);

struct Flags flags_new(struct Flag** flags, int count) ;

struct Flag flag_int(char* name, int def);
struct Flag flag_boolean(char* name, int def);
struct Flag flag_string(char* name, char* def);

#endif