CC	= gcc
CFLAGS	= -Wall -g
YACC	= bison --yacc
YFLAGS	= -d
LEX	= flex
LFLAGS	=

OBJS	= bbcp.o

all: bbcp

bbcp: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

clean:
	rm -f *.tab.? *.o *.bak *~  core bbcp

cleanall: clean
	rm -f :* freefds* nofiles* killmyself* sigdfl*

depend:
	makedepend bbcp.c
