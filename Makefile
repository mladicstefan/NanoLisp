CC       = gcc
CFLAGS   = -std=c99 -Wall -Ilib -g -fsanitize=address,undefined -fno-omit-frame-pointer
LDFLAGS  = -ledit -lm -fsanitize=address,undefined

TARGET   = pnr
SRC      = main.c lib/mpc.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)
