CC = gcc
CFLAGS = -std=c99 -Wall -Ilib
LDFLAGS = -ledit -lm

TARGET = pnr
SRC = main.c lib/mpc.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

