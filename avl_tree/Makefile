CXX = g++
BASIC_FLAGS = -g -Wall -pedantic
ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer -Wno-format-security
OBJ = tests.o

compile: output

output: ${OBJ}
	${CXX} ${BASIC_FLAGS} ${ASAN_FLAGS} $^ -o a.out

no_san: ${OBJ}
	${CXX} ${BASIC_FLAGS} $^ -o a.out

run: compile
	./a.out

%.o: %.cpp %.hpp
	${CXX} ${BASIC_FLAGS} -c $< -o $@

graph: compile
	./a.out | dot -Tsvg > graph.png


clean:
	rm *.o