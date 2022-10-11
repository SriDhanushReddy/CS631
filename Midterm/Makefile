#
# In order to execute this "Makefile" just type "make"
#

OBJS	= main.o ls.o
SOURCE	= main.c ls.c
HEADER	= ls.h
OUT	= myls
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 
# -g option enables debugging mode 
# -c flag generates object code for separate files


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)


# create/compile the individual files >>separately<<
main.o: main.c
	$(CC) $(FLAGS) main.c 

ls.o: ls.c
	$(CC) $(FLAGS) ls.c 


# clean house
clean:
	rm -f $(OBJS) $(OUT)
