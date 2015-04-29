#include "afficheur.h"

main()
{
    key_t key;
    int shmid;
    void* data;
    int mode= SHM_READ;
    double test;

    if (mode > SHM_WRITE) {
        fprintf(stderr, "usage: shmdemo [data_to_write]\n");
        exit(1);
    }

    /* make the key: */
    if ((key = ftok("shared_memory", 'R')) == ERROR) {
        perror("ftok");
        exit(1);
    }

    /* connect to (and possibly create) the segment: */
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == ERROR) {
        perror("shmget");
        exit(1);
    }

    /* attach to the segment to get a pointer to it: */
    data = shmat(shmid, (void*)0, 0);
    if (data == (void*)(ERROR)) {
        perror("shmat");
        exit(1);
    }

    /* read or modify the segment, based on the command line: */
    if (mode == SHM_WRITE) {
        printf("Ecriture dans le segment: \"%2.3f\"\n", test);
        memcpy(data, &test, SHM_SIZE);
    } else
        printf("Le segment contiens: \"%2.3f\"\n", *(double*)data);

    /* detach from the segment: */
    if (shmdt(data) == ERROR) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
