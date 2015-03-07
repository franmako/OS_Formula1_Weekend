#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include "afficheur.h"

#define SHMSZ     27

main()
{
    sharedMemClient();
    exit(0);
}
void sharedMemClient(){
    int shmid;
    key_t key;
    char *shm, *s;
    key = 85;

    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {//Recherche du segment
        perror("shmget");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {//Attachement du segment
        perror("shmat");
        exit(1);
    }

    s=shm;//Lecture du segment
    printf("%s\n",s);//Affichage du segment
    *shm = '*';//Envoi de l'ACK
}
