CC := gcc
CFLAGS := -fsanitize=address -Wall -Wextra -Wuninitialized -Wshadow -O3
TARGET := hydro

SRCS := \
	main.c \
	Vec2/charfuncs.c \
	Vec2/doublefuncs.c \
	Vec2/floatfuncs.c \
	Vec2/intfuncs.c \
	Vec2/strfuncs.c \
	lexer/lex.c \
	lexer/lex_vecs.c

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean

