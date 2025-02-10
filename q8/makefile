
#!make -f

CXX = g++
CXXFLAGS = -std=c++11 -Werror -Wsign-conversion -fprofile-arcs -ftest-coverage -g -pg
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean reports cps

all: main

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o main

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

reports: main
	./main 2> /dev/null 2>&1
	@mkdir  valgrindReport
	valgrind $(VALGRIND_FLAGS) ./main > valgrindReport/valgrindReport.txt 2>&1 || true
	valgrind --tool=callgrind ./main  > valgrindReport/callgrind.txt 2>&1 || true
	callgrind_annotate callgrind.out.* > valgrindReport/callgrindReport.txt
	
	@mv callgrind.out.* valgrindReport/
clean:
	rm -f -r *.o main   valgrindReport   callgrind.out.* *.out *.gcov *.gcda *.gcno
