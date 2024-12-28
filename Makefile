CC := gcc
SRCDIR ?= src
HEADIR ?= header
OBJDIR ?= object
TARGET ?= exec
CFLAGS= -Wall

OBJS := $(shell find $(SRCDIR) -name "*.c" | sed 's/.c$$/.o/g' | sed 's/$(SRCDIR)/$(OBJDIR)/g')

.PHONY : clean

all: $(TARGET)

$(TARGET): $(OBJS) main.c
	@$(CC) -o $(TARGET) main.c $(OBJS) -lSDL2 -lncurses

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR) 
	$(CC) $(CFLAGS) -c $< -o $@



clean :
	rm -rf $(OBJDIR) *

mrproper : clean
	rm -f $(TARGET)
