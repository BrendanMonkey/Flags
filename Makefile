bin/test: src/*.c src/include/*.h
	gcc src/*_tests.c src/flags.c -I /usr/local/include -L /usr/local/lib/ -g -o bin/test -lihct -Wl,-R /usr/local/lib