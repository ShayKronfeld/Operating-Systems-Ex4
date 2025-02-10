# Compiler and flags
CC = gcc
CFLAGS = -g -std=c11 -Wall

# Executable name and source file
TARGET = hello
SRC = hello.c
VALGRIND_REPORT_DIR = valgrindReport

# Default target: compile the hello.c program
all: $(TARGET)

# Compile the source file into an executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Run Valgrind with memcheck and save the report
valgrind: $(TARGET)
	@mkdir -p $(VALGRIND_REPORT_DIR)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=$(VALGRIND_REPORT_DIR)/valgrind_memcheck.txt ./$(TARGET) Hello World 123

# Run Valgrind with GDB server enabled
valgrind_gdb: $(TARGET)
	valgrind --leak-check=full --vgdb=yes --vgdb-error=0 ./$(TARGET) Hello World 123

# Clean up generated files and reports
clean:
	rm -f $(TARGET)
	rm -rf $(VALGRIND_REPORT_DIR)

# Phony targets
.PHONY: all clean valgrind valgrind_gdb
