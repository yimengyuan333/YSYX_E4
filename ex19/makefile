CC = clang
CFLAGS = -Wall -g
SRCS = object.c ex19.c
TARGET = ex19

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean