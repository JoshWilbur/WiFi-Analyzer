CC = gcc
CFLAGS = -Wall -Wextra -std=c18
LDFLAGS = -lcurl
SRC1 = signal_strength.c
EXEC1 = strength
SRC2 = speed_test.c
EXEC2 = speed

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(SRC1)
	$(CC) $(CFLAGS) $(SRC1) -o $(EXEC1)

$(EXEC2): $(SRC2)
	$(CC) $(CFLAGS) $(SRC2) -o $(EXEC2) $(LDFLAGS)

clean:
	rm -f $(EXEC1) $(EXEC2)
