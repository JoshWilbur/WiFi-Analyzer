CC = gcc
CFLAGS = -Wall -Wextra -std=c18
SRCS = signal_strength.c
EXEC = strength

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC)

clean:
	rm -f $(EXEC)
