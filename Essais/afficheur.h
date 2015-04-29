#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define ERROR -1
#define SHM_SIZE 1024  /* make it a 1K shared memory segment */
#define SHM_READ 0
#define SHM_WRITE 2
