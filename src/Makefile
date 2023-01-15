all: install start

r: uninstall install start

# test:
# 	$(MAKE) -C tests

# clean:
# 	$(MAKE) -C tests clean

install:
	QT_QPA_PLATFORM=xcb
	cmake -B"build" -H"build"
	$(MAKE) -C build
	mv build/viewer app

start:
	./app/viewer

uninstall:
	rm -rf app/viewer
	rm -rf build-*
	rm -rf build/cmake_install.cmake
	rm -rf build/CMakeCache.txt
	rm -rf build/CMakeFiles
	rm -rf build/Makefile
	rm -rf build/viewer_autogen
	rm -rf build/viewer.app
	rm -rf app/viewer
	rm -rf build/CMakeLists.txt.user
	rm -rf build/.cmake
	rm -rf build/viewer.cbp
	rm -rf build-build-Desktop-Debug
	rm -rf build/CPack*