CC = gcc
CFLAGS = -Wall -Wextra -std=c18
SRCS = main.c signal_strength.c
EXEC = wifi

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC)

clean:
	rm -f $(EXEC)
