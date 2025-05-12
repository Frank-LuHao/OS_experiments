CC = gcc
CFLAGS = -Wall -g
TARGET = a.out
SRCDIR = ./src
OBJDIR = ./obj
INCLUDES = -I$(SRCDIR)

SRC = main.c $(SRCDIR)/manager.c $(SRCDIR)/linklist.c $(SRCDIR)/mcb.c
OBJ = $(OBJDIR)/main.o $(OBJDIR)/manager.o $(OBJDIR)/linklist.o $(OBJDIR)/mcb.o

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJDIR)/main.o: main.c $(SRCDIR)/manager.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c main.c -o $@

$(OBJDIR)/manager.o: $(SRCDIR)/manager.c $(SRCDIR)/manager.h $(SRCDIR)/linklist.h $(SRCDIR)/mcb.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCDIR)/manager.c -o $@

$(OBJDIR)/linklist.o: $(SRCDIR)/linklist.c $(SRCDIR)/linklist.h $(SRCDIR)/mcb.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCDIR)/linklist.c -o $@

$(OBJDIR)/mcb.o: $(SRCDIR)/mcb.c $(SRCDIR)/mcb.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCDIR)/mcb.c -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: clean