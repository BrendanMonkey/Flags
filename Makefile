BUILD_DIR := ./bin
SRC := ./src

TEST_CODE := $(SRC)/flags_tests.c
CODE_SRC := $(SRC)/flags.c

BASE_LIB_DIR := /usr/local/include
LIB_FLAGS := -lihct -Wl,-R $(BASE_LIB_DIR) 

TEST_OBJ := $(BUILD_DIR)/test.o
TEST_CFLAGS := -g -o ${TEST_OBJ} $(LIB_FLAGS)

all: flag_build_test flag_run_test clean
	
flag_build_test:
	$(CC) $(CODE_SRC) $(TEST_CODE) $(TEST_CFLAGS)

flag_run_test: flag_build_test
	$(BUILD_DIR)/test.o -t 100

clean:
	rm $(BUILD_DIR)/*.o