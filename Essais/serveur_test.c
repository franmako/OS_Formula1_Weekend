#include "serveur.h"

int main(){
    int i,j;
    int nbTours= NBTRSCOURSE;
    TPilote pilote_serv;
    TPilote *ptPilote= &pilote_serv;
    sharedMem(SHM_READ,ptPilote,1);
    printf("N° Pilote: %d \n",pilote_serv.nbPilote);

    for(i=0;i<nbTours;i++){
    printf("|--------------|\n");
    printf("|*** Tour %d ***|\n",i+1);
    printf("|--------------|\n");
        for(j=0;j<NBSECTORS;j++){
            printf("Temps du secteur %d : %2.3f secondes\n",j+1,pilote_serv.GPrix.course[i].tbTempsSect[j]);
        }
    }
    return 0;
}
void sharedMem(int mode,TPilote *ptPilote,int nbPilotes){
    key_t key;
    int shmid;
    void* data;
    int shmSize= nbPilotes * sizeof(TPilote);

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
    if ((shmid = shmget(key, shmSize, 0644 | IPC_CREAT)) == ERROR) {
        perror("shmget");
        exit(1);
    }else{
        printf("%d",shmid);
    }

    /* attach to the segment to get a pointer to it: */
    data = shmat(shmid, (void*)0, 0);
    if (data == (void*)(ERROR)) {
        perror("shmat");
        exit(1);
    }

    /* read or modify the segment, based on the command line: */
    if (mode == SHM_WRITE) {
        printf("Ecriture dans la mémoire partagée: \"N° Pilote: %d \"\n",ptPilote->nbPilote);
        memcpy(data,ptPilote, sizeof(TPilote));
        //data= ptPilote;
    }else{
        memcpy(ptPilote,data, sizeof(TPilote));
        //ptPilote= (TPilote*)data;
        //printf("Le segment contiens: N° Pilote: %d \n",ptPilote.nbPilote);
    }

    /* detach from the segment: */
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }
}
