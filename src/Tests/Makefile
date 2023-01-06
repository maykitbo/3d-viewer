CC=g++
CFLAGS= -Wall -Werror -Wextra

build_test_parser:
	$(CC) $(CFLAGS) ../Parser/Parser.cc TestParser.cc -o test_parser

test_parser: build_test_parser
	./test_parser
	

valgrind_parser: build_test_parser
	valgrind ./test_parser

clean:
	rm -rf test_parser