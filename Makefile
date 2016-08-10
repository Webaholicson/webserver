CC = gcc
CFLAGS = -g -Wall
HTTP_FLAGS = -I/deps/http-parser -L./deps/http-parser -lhttp_parser
LIBEVENT_FLAGS = -I/deps/libevent -L./deps/libevent -levent

LIBEVENT_BUILD_DIR = $(join $(shell pwd), /deps/libevent/build)

OBJECTS = main.o server.o command.o config.o site.o request.o

ALL = $(OBJECTS)
HTTP = http-parser
LIBEVENT = libevent

all: $(OBJECTS) $(HTTP) $(LIBEVENT)
	$(CC) $(CFLAGS) -o webserver $(OBJECTS) $(HTTP_FLAGS) $(LIBEVENT_FLAGS)

http-parser:
	cd deps/http-parser && $(MAKE) package

libevent:
	cd deps/libevent && ./configure --prefix=$(LIBEVENT_BUILD_DIR) && $(MAKE) && $(MAKE) install

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

server.o: server.c server.h
	$(CC) $(CFLAGS) -c server.c

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c

config.o: config.c config.h
	$(CC) $(CFLAGS) -c config.c

site.o: site.c site.h
	$(CC) $(CFLAGS) -c site.c

.PHONY: clean clean_lua clean_http clean_libevent

clean: clean_lua clean_http clean_libevent
	rm -f webserver $(OBJECTS)

clean_http:
	cd deps/http-parser && $(MAKE) clean

clean_libevent:
	cd deps/libevent && $(MAKE) clean
