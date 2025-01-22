
#ifndef __RING_H_ 
#define __RING_H_ 

#include <assert.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
typedef struct record_item{
    const char* op_name;
    uint64_t Memory_usage;
    uint64_t op_time;
}record_item;

typedef struct {
    uint32_t size, gap;
} ringbuf_element_t;

typedef struct {
    size_t size, mask, rsvd /* reserved */, gapd;
    memory_order acquire, release;
    atomic_size_t head, tail;
    uint8_t buf[] __attribute__((aligned(sizeof(ringbuf_element_t))));
} ringbuf_t;

#define ARRAY_LENGTH 9000

typedef struct _ringbuf_shm_t ringbuf_shm_t;

struct _ringbuf_shm_t {
    char *name;
    int fd;
    ringbuf_t *ringbuf;
};

static int ringbuf_shm_init(ringbuf_shm_t *ringbuf_shm,
                            const char *name,
                            size_t minimum,
                            bool release_and_acquire);

static void ringbuf_shm_deinit(ringbuf_shm_t *ringbuf_shm);

static inline void *ringbuf_write_request_max(ringbuf_t *ringbuf,
                                              size_t minimum,
                                              size_t *maximum);


static inline void ringbuf_write_advance(ringbuf_t *ringbuf, size_t written);
static inline const void *ringbuf_read_request(ringbuf_t *ringbuf, size_t *toread);
static inline void ringbuf_read_advance(ringbuf_t *ringbuf);
void Saving(ringbuf_t *ringbuf, uint64_t *index, char *name, uint64_t Size, record_item *shared_array);
uint64_t Reading(ringbuf_t *ringbuf, record_item *shared_array, int shm_fd, uint64_t *prev);
# endif
