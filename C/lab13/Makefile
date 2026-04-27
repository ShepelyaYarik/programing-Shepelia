CC = clang

LAB_OPTS = -I./src
C_OPTS = -std=gnu11 -g -Wall -Wextra -Werror -Wformat-security -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference -Wno-unused-variable -Werror=vla $(LAB_OPTS)

clean:
	rm -rf dist

prep:
	mkdir -p dist

compile: main.bin test.bin
	./dist/main.bin ./assets ./dist/output.txt
main.bin: src/main.c src/lib.c
	$(CC) $(C_OPTS) src/main.c src/lib.c  -o ./dist/$@

test.bin: test/test.c src/lib.c
	$(CC) $(C_OPTS) test/test.c src/lib.c -fprofile-instr-generate -fcoverage-mapping -lm -o ./dist/$@ -lcheck -lsubunit -lpthread -lrt

test: clean prep compile
	LLVM_PROFILE_FILE="dist/test.profraw" ./dist/test.bin
	llvm-profdata merge -sparse dist/test.profraw -o dist/test.profdata
	llvm-cov report dist/test.bin -instr-profile=dist/test.profdata src/*.c
	llvm-cov show dist/test.bin -instr-profile=dist/test.profdata src/*.c --format html > dist/coverage.html

run: clean prep compile
	./dist/main.bin

format:
	doxygen Doxyfile
	
V_FLAGS=--tool=memcheck --leak-check=full --show-reachable=yes \
	--undef-value-errors=yes --track-origins=no --child-silent-after-fork=no \
	--trace-children=no --error-exitcode=1
leak-check: clean prep compile
	valgrind $(V_FLAGS) --log-file=dist/valgrind.log --xml-file=dist/valgrind.xml --xml=yes dist/main.bin
	valgrind $(V_FLAGS) --log-file=dist/valgrind.log --xml-file=dist/valgrind.xml --xml=yes dist/test.bin

check:
	clang-format --verbose -dry-run --Werror src/*
	clang-tidy src/*.c -checks=-readability-uppercase-literal-suffix,-readability-magic-numbers,-clang-analyzer-deadcode
	rm -rf src/*.dump
