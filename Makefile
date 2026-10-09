BUILD_DIR := ./bin
SRC := ./src

TEST_SRC := $(SRC)/*_tests.c
CODE_SRC := $(SRC)/flags.c

BASE_LIB_DIR := /usr/local/include
LIB_FLAGS := -lihct -Wl,-R $(BASE_LIB_DIR)

TEST_OBJ := $(BUILD_DIR)/test.o
CFLAGS_TEST := -g -o ${TEST_OBJ} $(LIB_FLAGS)

all: build_tests run_tests run_examples
	
build_tests: 
	$(CC) $(CODE_SRC) $(TEST_SRC) $(CFLAGS_TEST)

run_tests: build_tests
	./bin/test.o -t 99999

example:
	$(CC) -g $(CODE_SRC) examples/multiplication/main.c -o bin/examples.o

run_examples: example
	./bin/examples.o
