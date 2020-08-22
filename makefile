# hw: hw.o helper.o
# 	gcc -o hw hw.o helper.o -lm
ls: ls.c
	gcc -O -Wall -c ls.c -o ls
# helper.o: helper.c
# 	gcc -O -Wall -c helper.c
# clean:
# 	rm -f ls.o main.o main


# specify all source files here
SRCS = main.c input.c pwd.c
# specify target here (name of executable)
TARG = main
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
