CC = gcc
CFLAGS = -g -Wall

objects = main.o server.o command.o

webserver: $(objects)
	$(CC) $(CFLAGS) -o webserver $(objects)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c 

server.o: server.c server.h
	$(CC) $(CFLAGS) -c server.c
	
command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c

.PHONY: clean

clean:
	rm -f webserver $(objects)