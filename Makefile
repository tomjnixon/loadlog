

all:loadavg

loadavg:loadavg.c
	gcc -Wall loadavg.c -o loadavg