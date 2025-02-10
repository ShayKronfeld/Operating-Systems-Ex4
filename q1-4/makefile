# Makefile for compiling the graph project

# Compiler
CXX = g++ -pg

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -g -fprofile-arcs -ftest-coverage 

# Source files
SRCS = graph.cpp main.cpp

# Header files
HEADERS = graph.hpp

# Output executable name
TARGET = graph_program

# Build rules
all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Clean up build files
clean:
	rm -f $(TARGET) *.gcda *.gcno *.gcov gmon.out callgrind.out.* *.o 

# Clean everything including logs and reports
clean-all: clean
	rm -f gprof_report.txt callgrind_report.txt
