CC = gcc
TARGET = hysh
CFLAGS = -W -Wall
SOURCES = ./bin/execution.c ./bin/pwd.c ./bin/echo.c ./bin/clear.c ./bin/cat.c ./bin/cd.c
OBJS = hysh.o execution.o pwd.o echo.o clear.o cat.o cd.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

hysh.o: hysh.c
	$(CC) -c -o hysh.o hysh.c

pwd.o: ./bin/pwd.c
	$(CC) -c -o pwd.o ./bin/pwd.c

echo.o: ./bin/echo.c
	$(CC) -c -o echo.o ./bin/echo.c

clear.o: ./bin/clear.c
	$(CC) -c -o clear.o ./bin/clear.c

cat.o: ./bin/cat.c
	$(CC) -c -o cat.o ./bin/cat.c

cd.o: ./bin/cd.c
	$(CC) -c -o cd.o ./bin/cd.c

execution.o: ./bin/execution.c
	$(CC) -c -o execution.o ./bin/execution.c

clean:
	rm -rf $(TARGET) $(OBJS)
