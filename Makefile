
cflags = -Wall -Werror

all:loadavg

loadavg:loadavg.o lock.o
	gcc $(cflags) loadavg.o lock.o -o loadavg

loadavg.o:loadavg.c
	gcc $(cflags) -c loadavg.c -o loadavg.o

lock.o:lock.c
	gcc $(cflags) -c lock.c -o lock.o
