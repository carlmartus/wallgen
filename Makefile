FLAGS=-Wall -O2 -std=c99 -lm

SRC=$(wildcard *.c)
APPS=$(SRC:%.c=%)

all: $(APPS)

%: %.c
	$(CC) -o $@ $< $(FLAGS)

clean:
	$(RM) $(APPS)

re: clean all

