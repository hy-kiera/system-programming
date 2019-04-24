CC = gcc
TARGET = hysh
CFLAGS = -W Wall
SOURCES = ./bin/pwd.c ./bin/echo.c ./bin/clear.c ./bin/execution.c
OBJS = pwd.o echo.o clear.o execution.o

all: $(TARGET)

$(TARGET): hysh.o $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) hysh.o $(OBJS)

hysh.o: hysh.c
	$(CC) -c -o hysh.o hysh.c

pwd.o: ./bin/pwd.c
	$(CC) -c -o pwd.o ./bin/pwd.c

echo.o: ./bin/echo.c
	$(CC) -c -o echo.o ./bin/echo.c

clear.o: ./bin/clear.c
	$(CC) -c -o clear.o ./bin/clear.c

execution.o: ./bin/execution.c
	$(CC) -c -o execution.o ./bin/execution.c

clean:
	rm $(TARGET)
