CC := gcc
CFLAGS := -Iinclude -Wall -Wextra -std=c11
LDFLAGS := -Llib/SDL3/i686-w64-mingw32/lib -lSDL3
SDL_CFLAGS := -Ilib/SDL3/i686-w64-mingw32/include
SDL_LDFLAGS := -Llib/SDL3/i686-w64-mingw32/lib -lSDL3 

SRCDIR := src
OBJDIR := obj
BINDIR := bin

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
TARGET := $(BINDIR)/game.exe

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(SDL_LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean


# all: 
	# gcc -o rpg.exe src/main.c -I src/ -I include/ -I lib/SDL3/i686-w64-mingw32/include/ -L lib/SDL3/i686-w64-mingw32/lib/ -lSDL3 -mwindows 
	# cp ./lib/SDL3/i686-w64-mingw32/bin/SDL3.dll .
