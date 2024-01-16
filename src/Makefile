#--------------------------------------------------------------
# Formant Speech Synthesizer Makefile
# Author: Alan Crispin <crispinalan@gmail.com> 
# Date: January 2024
# Changelog: 0.02 (.c files now located in src directory)
# target is fspeak
#----------------------------------------------------------------

CC ?= gcc
CFLAGS = -Wall 
LIBS = -lm 
#MAKEFLAGS += --silent
SRCDIR   = src
SOURCES  := $(wildcard $(SRCDIR)/*.c)

#substitution reference
OBJECTS	:= $(SOURCES:$(SRCDIR)/%.c=$(SRCDIR)/%.o)

#target %.o matches any file ending in .o with filename ending in .c present
%.o : $(SRCDIR)/%.c
	$(CC) -c -o $(@F) $(CFLAGS)  $<
	
#target fspeak
fspeak: $(OBJECTS)
	$(CC) -o $(@F) $(OBJECTS) $(LIBS)

clean:
	rm -f $(OBJECTS)
	rm -f fspeak





