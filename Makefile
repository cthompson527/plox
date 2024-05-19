bin := $(shell pwd)/.bin
build := $(shell pwd)/build
tools := ${bin}/cmake ${bin}/clang++ ${bin}/clang

plox: main.cpp src/lexer.cpp ${build}/Makefile
	cmake --build build --target plox

${build}/Makefile: ${tools} CMakeLists.txt
	${bin}/cmake --preset default

${tools}:
	mkdir -p ${bin}
	ln -s /usr/local/opt/llvm/bin/clang++ ${bin}/clang++
	ln -s /usr/local/opt/llvm/bin/clang ${bin}/clang
	ln -s /usr/local/bin/cmake ${bin}/cmake

clean:
	rm -rf build
	rm -rf ${bin}
	rm -f plox
