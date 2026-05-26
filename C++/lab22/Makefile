CXX = clang++

LAB_OPTS = -I./src
CXX_OPTS = -std=c++17 -g -Wall -Wextra -Werror -Wformat-security -Wfloat-equal -Wshadow -Wconversion

clean:
	rm -rf dist

prep:
	mkdir -p dist

compile: main.bin test.bin

# Компільовано лише через main.cpp, оскільки вся логіка тепер в entity.hpp та list.hpp
main.bin: src/main.cpp src/entity.hpp src/list.hpp
	$(CXX) $(CXX_OPTS) src/main.cpp -o dist/$@

# Компільовано лише через test.cpp, лінкуємо Google Test (-lgtest -lgtest_main -pthread)
test.bin: test/test.cpp src/entity.hpp src/list.hpp
	$(CXX) $(CXX_OPTS) test/test.cpp -fprofile-instr-generate -fcoverage-mapping -lgtest -lgtest_main -pthread -o dist/$@

# Збір логів покриття коду змінено на аналіз файлів .hpp у папці src/
test: clean prep compile
	LLVM_PROFILE_FILE="dist/test.profraw" ./dist/test.bin
	llvm-profdata merge -sparse dist/test.profraw -o dist/test.profdata
	llvm-cov report dist/test.bin -instr-profile=dist/test.profdata src/*.hpp
	llvm-cov show dist/test.bin -instr-profile=dist/test.profdata src/*.hpp --format html > dist/coverage.html

run: clean prep compile
	./dist/main.bin

format:
	doxygen Doxyfile

V_FLAGS=--tool=memcheck --leak-check=full --show-reachable=yes \
	--undef-value-errors=yes --track-origins=no --child-silent-after-fork=no \
	--trace-children=no --error-exitcode=1

leak-check: clean prep compile
	valgrind $(V_FLAGS) --log-file=dist/valgrind.log --xml-file=dist/valgrind.xml --xml=yes dist/main.bin
	valgrind $(V_FLAGS) --log-file=dist/valgrind_test.log --xml-file=dist/valgrind_test.xml --xml=yes dist/test.bin

# Маски розширень оновлено під нову структуру (.hpp замість .h та .cpp для бізнес-логіки)
check:
	clang-format --verbose -dry-run --Werror src/*.cpp src/*.hpp test/*.cpp
	clang-tidy src/*.cpp test/*.cpp -checks=-readability-uppercase-literal-suffix,-readability-magic-numbers,-clang-analyzer-deadcode
	rm -rf src/*.dump