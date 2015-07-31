CC = gcc
CFLAGS = -g -Wall
LUA_FLAGS = -I./deps/lua/src -L./deps/lua/src -llua -lm -ldl
HTTP_FLAGS = -I/deps/http-parser -L./deps/http-parser -lhttp_parser

OBJECTS = main.o server.o command.o config.o site.o

ALL = $(OBJECTS)
LUA = lua
HTTP = http-parser

all: $(OBJECTS) $(LUA) $(HTTP)
	$(CC) $(CFLAGS) -o webserver $(OBJECTS) $(LUA_FLAGS) $(HTTP_FLAGS)

lua:
	cd deps/lua/src && $(MAKE) linux
	
http-parser:
	cd deps/http-parser && $(MAKE) package

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

.PHONY: clean

clean:
	rm -f webserver $(OBJECTS) deps/lua/src/*.o deps/lua/src/*.a \
		deps/lua/src/lua deps/lua/src/luac \
		deps/http-parser/*.a deps/http-parser/*.a