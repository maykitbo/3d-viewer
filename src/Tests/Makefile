CC=g++
CFLAGS= -Wall -Werror -Wextra

command:
	# QT_QPA_PLATFORM=xcb
	cmake -B"CommandsTest" -H"CommandsTest"
	$(MAKE) -C CommandsTest
	./CommandsTest/commands_test

valgrind_command:
	valgrind ./CommandsTest/commands_test

build_test_parser:
	$(CC) $(CFLAGS) ../Parser/Parser.cc TestParser.cc -o test_parser

parser: build_test_parser
	./test_parser
	

valgrind_parser: build_test_parser
	valgrind ./test_parser

clean:
	rm -rf test_parser
	rm -rf CommandsTest/CPackSourceConfig.cmake
	rm -rf CommandsTest/CPackConfig.cmake
	rm -rf CommandsTest/CMakeCache.txt
	rm -rf CommandsTest/CMakeFiles
	rm -rf CommandsTest/cmake_install.cmake
	rm -rf CommandsTest/Makefile
	rm -rf CommandsTest/commands_test_autogen
	rm -rf CommandsTest/commands_test