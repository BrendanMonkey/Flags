all: tests run_tests run_examples
	
tests: 
	gcc -g src/*_tests.c src/flags.c -I /usr/local/include -L /usr/local/lib/ -o bin/test.o -lihct -Wl,-R /usr/local/lib

example:
	gcc -g src/flags.c examples/multiplication/main.c -o bin/examples.o

run_examples: example
	./bin/examples.o

run_tests: 
	./bin/test.o -t 99999