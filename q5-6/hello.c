/*The following code has some problems. Run Valgrind/memcheck on it. And report the
errors (10 pts)
Origin : https://www.parasoft.com/blog/finding-memory-leaks-in-c-or-c/

* File: hello.c


how to run
cd q5-6
make
make valgrind

q6
make valgrind_gdb
 
In a new terminal:
gdb ./hello
Connect GDB to Valgrind by running:

target remote | vgdb
c
c
c

*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
char *string, *string_so_far;
int i, length; length = 0;
for(i=0; i<argc; i++) {
length += strlen(argv[i])+1;
string = malloc(length+1);
/* * Copy the string built so far. */
if(string_so_far != (char *)0)
strcpy(string, string_so_far);
else *string = '\0';
strcat(string, argv[i]);
if(i < argc-1) strcat(string, " ");
string_so_far = string;
}
printf("You entered: %s\n", string_so_far);
return (0);
}