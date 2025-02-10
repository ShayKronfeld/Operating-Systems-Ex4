CC = gcc
CFLAGS = -Wall -g -pthread

all: helgrind

race: race.c
	$(CC) $(CFLAGS) $< -o $@

helgrind: race
	valgrind --tool=helgrind --log-file=helgrindReport.txt ./race

clean:
	rm -rf race helgrindReport.txt