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
	$(BUILD_DIR)/test.o -t 100
	
clean:
	rm $(BUILD_DIR)/*.o