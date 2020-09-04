# This makefile was taken from the text-book.

# all the source files
SRCS = main.c helper.c daemon.c cmds/pwd.c cmds/ls.c cmds/mkdir.c cmds/cd.c cmds/chmod.c cmds/cat.c cmds/rm.c cmds/mv.c cmds/grep.c cmds/cp.c
TARG = shell
CC = gcc
OPTS = -Wall -O
LIBS = -lm -lreadline
OBJS = $(SRCS:.c=.o)
all: $(TARG)
$(TARG): $(OBJS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS)
%.o: %.c
	$(CC) $(OPTS) -c $< -o $@
clean:
	rm -f $(OBJS) $(TARG)
