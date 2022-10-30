CXX = g++
BASIC_FLAGS = -g -Wall -pedantic
ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer -Wno-format-security
OBJ = tests.o bts.o

compile: output

no_sanitize: no_sanitize

output: ${OBJ}
	${CXX} ${BASIC_FLAGS} ${ASAN_FLAGS} $^ -o $@.out

no_san: ${OBJ}
	${CXX} ${BASIC_FLAGS} $^ -o $@.out

run: compile
	./output.out

%.o: %.cpp %.h
	${CXX} ${BASIC_FLAGS} -c $< -o $@

clean:
	rm *.o