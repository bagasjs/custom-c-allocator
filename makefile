CFLAGS = -g -Werror -Wextra -std=c11 -I.

all:
	$(CC) $(CFLAGS) -o app main.c mem.c
