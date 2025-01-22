CFLAGS = -Wall -std=gnu11 -fsanitize=address,undefined
LDFLAGS = -fsanitize=address,undefined -lpthread -lrt

all: ringbuffer main

ringbuffer: ringbuffer.c
	$(CC) $(CFLAGS) -o ringbuffer ringbuffer.c $(LDFLAGS)

main: main.c
	$(CC) $(CFLAGS) -o main main.c $(LDFLAGS)

clean:
	rm -f ringbuffer main

indent:
	clang-format -i ringbuffer.c main.c
