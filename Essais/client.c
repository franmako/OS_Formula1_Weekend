#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ     27

main()
{
    int shmid;
    key_t key;
    char *shm, *s;

    //Choix du segment de mémoire
    key = 45;//La clé doit correspondre à celle du segment du serveur

    //Trouver emplacement segment
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    //Attachement du segment à l'espace de données
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    //Lecture du segment
    for (s = shm; s != NULL; s++)
        putchar(*s);
    putchar('\n');

    //Envoi de l'ACK
    *shm = '*';

    exit(0);
}
