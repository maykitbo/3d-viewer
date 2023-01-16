CC=g++
CFLAGS= -Wall -Werror -Wextra

# buildcommand:
# 	$(MAKE) -C CommandsTest/Build
# 	./CommandsTest/Nuild/commands_test

command:
	cmake -B"CommandsTest/Build" -H"CommandsTest/Build"
	$(MAKE) -C CommandsTest/Build
	./CommandsTest/Build/commands_test

valgrind_command:
	valgrind ./CommandsTest/Build/commands_test

build_test_parser:
	$(CC) $(CFLAGS) ../Parser/Parser.cc TestParser.cc -o test_parser

parser: build_test_parser
	./test_parser
	

valgrind_parser: build_test_parser
	valgrind ./test_parser

clean:
	rm -rf test_parser
	rm -rf CommandsTest/Build/CPackSourceConfig.cmake
	rm -rf CommandsTest/Build/CPackConfig.cmake
	rm -rf CommandsTest/Build/CMakeCache.txt
	rm -rf CommandsTest/Build/CMakeFiles
	rm -rf CommandsTest/Build/cmake_install.cmake
	rm -rf CommandsTest/Build/Makefile
	rm -rf CommandsTest/Build/commands_test_autogen
	rm -rf CommandsTest/Build/commands_test
	rm -rf CommandsTest/Build/lib
	rm -rf CommandsTest/Build/bin
	rm -rf CommandsTest/Build/_deps