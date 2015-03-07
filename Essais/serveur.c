#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include "serveur.h"
#define SHMSZ 27

main(){
    sharedMemServer();
    exit(0);
}
void sharedMemServer(){
    char c;
    int shmid;
    key_t key;
    char *shm, *s;
    key = 85;//Nom segment mémoire

    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {//Création du segment de mémoire
        perror("!!Erreur Creation Segment Mem!!");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {//On attache le segment à notre espace de données
        perror("!!Erreur attachement segment à espace données!!");
        exit(1);
    }

    s = shm;
    for (c = 'a'; c <= 'z'; c++)//Ecriture dans le segment
        *s++ = c;
    s = NULL;

    while (*shm != '*')//Attente de l'ACK de l'afficheur
        sleep(1);
}
