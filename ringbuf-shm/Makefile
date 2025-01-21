CFLAGS = -Wall -std=gnu11 -fsanitize=address,undefined
LDFLAGS = -fsanitize=address,undefined -lpthread -lrt

all:
	$(CC) $(CFLAGS) -o ringbuffer ringbuffer.c $(LDFLAGS)

clean:
	rm -f ringbuffer

indent:
	clang-format -i ringbuffer.c

