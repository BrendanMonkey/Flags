all: tests run_tests
	
tests: 
	gcc src/*_tests.c src/flags.c -I /usr/local/include -L /usr/local/lib/ -g -o bin/test.o -lihct -Wl,-R /usr/local/lib

run_tests: 
	./bin/test.o
