CC := gcc
CFLAGS := -g -std=c99 -Wall -pedantic
TARGET := reverse

$(TARGET): reverse.c
	$(CC) reverse.c -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)