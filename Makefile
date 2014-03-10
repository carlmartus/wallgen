FLAGS=-Wall -O2 -std=c99 -lm

SRC=$(wildcard *.c)
APPS=$(SRC:%.c=%)
SAMPLEDIR=samples
SAMPLESIZE=300
SAMPLEOUTPUT=100x100
SAMPLES=$(APPS:%=$(SAMPLEDIR)/%.jpg)

.PHONY: all update-samples clean re

all: $(APPS)

%: %.c
	$(CC) -o $@ $< $(FLAGS)

$(SAMPLEDIR)/%.jpg: % Makefile
	./$< $(SAMPLESIZE) $(SAMPLESIZE) > $@.ppm
	convert -resize $(SAMPLEOUTPUT) $@.ppm $@
	$(RM) $@.ppm

update-samples: $(SAMPLES)

clean:
	$(RM) $(APPS)

re: clean all

