#include <stdio.h>
#include <stdlib.h>
#include "ringbffer.h"

int shm_fd;
record_item *shared_array;
uint64_t INDEX = 0;
int main(int argc, char **argv)
{

    pid_t pid = fork();
    assert(pid != -1);
    const char *name = "/ringbuf_shm_test";
    if (pid == 0) { /* child process */
        ringbuf_shm_t ringbuf_shm;
        assert(ringbuf_shm_init(&ringbuf_shm, name, ARRAY_LENGTH*8, true) == 0);

        for(uint64_t i =0; i< 200;i++)
        {
            Saving(ringbuf_shm.ringbuf, &i, "Test", sizeof(record_item),shared_array);
        }
        
        ringbuf_shm_deinit(&ringbuf_shm);
    } else { /* parent process */
        ringbuf_shm_t ringbuf_shm;
        assert(ringbuf_shm_init(&ringbuf_shm, name, ARRAY_LENGTH*8, true) == 0);
        uint64_t prev = 0;

        for(int i =0; i< 200;i++)
        {
            Reading(ringbuf_shm.ringbuf, shared_array, ringbuf_shm.fd, &prev);
            printf("prev == %lld\n", prev);
        }

        ringbuf_shm_deinit(&ringbuf_shm);
    }

    
    return 0;
}