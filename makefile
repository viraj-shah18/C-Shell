# This makefile was taken from the text-book.
#  specify all source files here
SRCS = main.c input.c cmds/pwd.c cmds/ls.c cmds/mkdir.c cmds/cd.c cmds/chmod.c cmds/cat.c cmds/rm.c cmds/mv.c
# specify target here (name of executable)
TARG = shell
# specify compiler, compile flags, and needed libs
CC = gcc
OPTS = -Wall -O
LIBS = -lm
# this translates .c files in src list to .o’s
OBJS = $(SRCS:.c=.o)
# all is not really needed, but is used to generate the target
all: $(TARG)
# this generates the target executable
$(TARG): $(OBJS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS)

# this is a generic rule for .o files
%.o: %.c
	$(CC) $(OPTS) -c $< -o $@
# and finally, a clean line
clean:
	rm -f $(OBJS) $(TARG)
