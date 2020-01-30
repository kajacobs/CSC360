CC=gcc
CFLAGS=-Wall -Werror

SEEsh: seesh.o
	$(CC) -o SEEsh seesh.o


clean:
	- rm *.o SEEsh
