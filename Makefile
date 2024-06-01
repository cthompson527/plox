source := $(shell pwd)
build := ${source}/build

plox: main.cpp src/lexer.cpp ${build}/ninja.build
	cmake --build build --target plox

${build}/ninja.build: CMakeLists.txt
	@cmake --preset default
	@cp ${build}/compile_commands.json ${source}/compile_commands.json

clean:
	rm -rf build
	rm -f plox
