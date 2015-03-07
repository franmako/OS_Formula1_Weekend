#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ 27
main(){
    char c,d;
    int shmid;
    key_t key;
    char *shm, *s,*shm2,*s2;

    //On nomme le segment de mémoire partagée "5678"
    key = 75;
    key2=889;

    //Création du segment de mémoire
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("!!Erreur Creation Segment Mem!!");
        exit(1);
    }
    if ((shmid2 = shmget(key2, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("!!Erreur Creation Segment Mem!!");
        exit(1);
    }

    //On attache le segment à notre espace de données
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("!!Erreur attachement segment à espace données!!");
        exit(1);
    }
    if ((shm2 = shmat(shmid2, NULL, 0)) == (char *) -1) {
        perror("!!Erreur attachement segment à espace données!!");
        exit(1);
    }

    //On place des char dans la mémoire partagée pour que les client puisse le lire
    //printf("Ecriture dans la mémoire partagée...");
    s = shm;
    s2= shm2;

    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    s = NULL;
    for(d= 'z';d <= 'a';d--)
    	*s2++ = d; 

    //printf("Ecriture complet! Attente de l'ACK...");
    //Attente de l'ack du client
    while (*shm != '*')
        sleep(1);
    while (*shm2 != '*')
        sleep(1);

    exit(0);
}
