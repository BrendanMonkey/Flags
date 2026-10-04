#ifndef MDEV_FLAGS
#define MDEV_FLAGS

#define FLAG_TAG '-'
#define FLAG_EQUAL '='

#include "stdio.h"

inline int calc_argc(int argc);

int parse(int argc, char** argv, char** argt);

#endif