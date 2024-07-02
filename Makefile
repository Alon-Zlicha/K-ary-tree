CXX=g++
CXXFLAGS=-std=c++17 -Werror -Wno-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --error-exitcode=99
LDFLAGS= -lsfml-graphics -lsfml-window -lsfml-system
SOURCES=complex.cpp tree.hpp node.hpp
OBJECTS=$(SOURCES:.cpp=.o)

.PHONY: all clean run tidy valgrind

all: demo test 

tree: demo
	./demo

demo: demo.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo $(LDFLAGS)

test: TestCounter.o test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-,clang-analyzer-,cppcoreguidelines-,performance-,portability-,readability-,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-*

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo test core.* 
