#include "pilote.h"

int main(){
    srand(time(NULL));//Init random
    int i,j;
    int nbTours= NBTRSCOURSE;
    TPilote pilote;

    pilote.nbPilote = 44;
    for(i=0;i<nbTours;i++){//Début boucle tours
    printf("|--------------|\n");
    printf("|*** Tour %d ***|\n",i+1);
    printf("|--------------|\n");
        for(j=0;j<NBSECTORS;j++){//Début boucle secteurs
            pilote.GPrix.course[i].tbTempsSect[j]= getSectorTime(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
            //sleep(pilote.tbTempsSecteurs[j]); //Sleep pour la génération en temps réel
            //printf("Temps du secteur %d : %2.3f secondes\n",j+1,pilote.GPrix.course[i].tbTempsSect[j]);
        }
    }
    sharedMem(SHM_WRITE,&pilote,1);//Ecriture dans le segment shm
    return 0;
}

/*
return: float(double)
a: borne max
b: borne min
Cette fonction génère et renvoie un float entre min et max.
 */
double getSectorTime(double a, double b) {
    double random,diff,r;
    static double sectorTime;

    random = ((double) rand()) / (double) RAND_MAX;
    diff = b - a;
    r = random * diff;
    sectorTime= a+r;

    return (sectorTime);
}

 /*
 mode: mode d'accès du segment mémoire (SHM_READ pour lecture ou SHM_WRITE pour écriture)
 *ptPilote: pointeur vers un type abstrait TPilote(voir pilote.h)
 nbPilotes: nombre de pilotes pour l'allocation de la taille du segment mémoire
 */
void sharedMem(int mode,TPilote *ptPilote,int nbPilotes){
    key_t key;
    int shmid;
    void* data;
    int shmSize= nbPilotes * sizeof(TPilote);

    if (mode > SHM_WRITE) {
        fprintf(stderr, "usage: shmdemo [data_to_write]\n");
        exit(1);
    }
    //Création de la clé
    if ((key = ftok("shared_memory", 'R')) == ERROR) {
        perror("ftok");
        exit(1);
    }
    //Création du segment
    if ((shmid = shmget(key, shmSize, 0644 | IPC_CREAT)) == ERROR) {
        perror("shmget");
        exit(1);
    }else{
        printf("%d",shmid);
    }
    //Attachement au segment pour recevoir un pointeur vers ce dernier
    data = shmat(shmid, (void*)0, 0);
    if (data == (void*)(ERROR)) {
        perror("shmat");
        exit(1);
    }
    //Lecture ou écriture dans le segment mémoire en fonction du mode
    if (mode == SHM_WRITE) {
        memcpy(data,ptPilote, sizeof(TPilote));
        printf("Ecriture dans la mémoire partagée: N° Pilote: %d \n",ptPilote->nbPilote);
    }else{
        memcpy(ptPilote,data, sizeof(TPilote));
    }
    //Détachement du segment
    if (shmdt(data) == ERROR) {
        perror("shmdt");
        exit(1);
    }
}
