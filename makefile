CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
LIBS = -lncurses
SRCDIR = src
INCDIR = include
TARGET = todo

# Find all .c files in src directory
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRCDIR)/*.o $(TARGET)

.PHONY: clean
