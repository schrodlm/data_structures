CXX = g++
BASIC_FLAGS = -g -Wall -pedantic
ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer -Wno-format-security
DEPS = dynamic_array.h
OBJ = tests.o dynamic_array.o

compile: output

no_sanitize: no_san 

output: ${OBJ}
	${CXX} ${BASIC_FLAGS} ${ASAN_FLAGS} $^ -o $@.out

no_san: ${OBJ}
	${CXX} ${BASIC_FLAGS} $^ -o $@.out


run: compile
	./output.out

%.o: %.cpp $(DEPS)
	${CXX} ${BASIC_FLAGS} -c $< -o $@



clean:
	rm *.o