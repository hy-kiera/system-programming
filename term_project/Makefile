CC = gcc
TARGET = hysh
STRIP = strip
# CFLAGS = -W -Wall
OBJS = hysh.o \
pwd.o \
echo.o \
clear.o \
cat.o \
rm.o \
mv.o \
cp.o \
hello.o \
mkdir.o \
ls.o \
file_size.o \
get_type.o \
execution.o

SRCS = $(OBJS:.o=.c)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	$(STRIP) $(TARGET)

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

rm.o: ./bin/rm.c
	$(CC) -c -o rm.o ./bin/rm.c

mv.o: ./bin/mv.c
	$(CC) -c -o mv.o ./bin/mv.c

cp.o: ./bin/cp.c
	$(CC) -c -o cp.o ./bin/cp.c

hello.o: ./bin/hello.c
	$(CC) -c -o hello.o ./bin/hello.c

mkdir.o: ./bin/mkdir.c
	$(CC) -c -o mkdir.o ./bin/mkdir.c

ls.o: ./bin/ls.c
	$(CC) -c -o ls.o ./bin/ls.c

execution.o: ./bin/execution.c
	$(CC) -c -o execution.o ./bin/execution.c

file_size.o: ./bin/utils/file_size.c
	$(CC) -c -o file_size.o ./bin/utils/file_size.c

get_type.o: ./bin/utils/get_type.c
	$(CC) -c -o get_type.o ./bin/utils/get_type.c

clean:
	rm -rf $(TARGET) $(OBJS)
