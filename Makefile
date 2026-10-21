CC     = g++
CFLAGS = -Wall -g -Isrc -Ilib -Iinclude -std=c++23

TARGET = bin/main.exe

OBJS = obj/main.o obj/code.o obj/tests.o obj/unity.o

all: $(TARGET)

$(TARGET): $(OBJS) | bin
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

bin:
	mkdir bin

obj/main.o: src/main.cpp | obj
	$(CC) $(CFLAGS) -c src/main.cpp -o obj/main.o

obj/code.o: src/code.cpp include/code.hpp | obj
	$(CC) $(CFLAGS) -c src/code.cpp -o obj/code.o

obj/tests.o: src/tests.cpp | obj
	$(CC) $(CFLAGS) -c src/tests.cpp -o obj/tests.o

obj/unity.o: src/unity.c | obj
	$(CC) $(CFLAGS) -c src/unity.c -o obj/unity.o

obj:
	mkdir obj

clean:
	rm -rf obj bin