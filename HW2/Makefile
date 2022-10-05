TARGET = ls
CC = cc
CFLAGS  = -ansi -g -Wall -Werror -Wextra -Wformat=2 -Wjump-misses-init -Wlogical-op -Wpedantic -Wshadow
RM = rm -f

default: $(TARGET)
all: default

$(TARGET): ls.o
	$(CC) $(CFLAGS) -o $(TARGET) ls.o

ls.o: ls.c ls.h
	$(CC) $(CFLAGS) -c ls.c


clean:
	$(RM) $(TARGET) *.o 
