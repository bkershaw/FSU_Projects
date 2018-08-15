CC=gcc
DEBUG=-g -O0
CFLAGS=$(DEBUG)

all: inc_x_thread.exe thrd-posix.exe

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< 

inc_x_thread.exe: inc_x_thread.o
	$(CC) -o $@ $< -lpthread

thrd-posix.exe: thrd-posix.o
	$(CC) -o $@ $< -lpthread

clean:
	rm -f *.o  inc_x_thread.exe thrd-posix.exe \#*\# *~
