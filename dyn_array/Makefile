CXX = g++
BASIC_FLAGS = -g -Wall -pedantic
ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer -Wno-format-security
DEPS = dynamic_array.h
OBJ = tests.o dynamic_array.o

compile: out

no_sanitize: out_no_f 

out: ${OBJ}
	${CXX} ${BASIC_FLAGS} ${ASAN_FLAGS} $^ -o $@

out_no_f: ${OBJ}
	${CXX} ${BASIC_FLAGS} $^ -o $@


run: compile
	./out

%.o: %.cpp $(DEPS)
	${CXX} ${BASIC_FLAGS} -c $< -o $@



clean:
	rm *.o