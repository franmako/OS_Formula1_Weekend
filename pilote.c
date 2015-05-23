#include "pilote.h"

int main(){
    srand(time(NULL));//Init random
    int i,j,nbTrsP1,nbTrsP2,nbTrsP3;
    TPilote pilote;
    TPilote *ptPilote= &pilote;
    pilote.nbPilote = 44;
    pilote.GPrix.isOut= FALSE;
    pilote.GPrix.isStand= FALSE;

    //Essais
    getEssais(ptPilote,ESSAI_P1,"Essais Vendredi Matin");
    getEssais(ptPilote,ESSAI_P2,"Essais Vendredi Après-Midi");
    getEssais(ptPilote,ESSAI_P3,"Essais Samedi Matin");
    //Qualifs Q1

    //Course
    //for(i=0;i<NBTRSCOURSE;i++){//Début boucle tours
    /*printf("|--------------|\n");
    printf("|*** Tour %d ***|\n",i+1);
    printf("|--------------|\n");*//*
        for(j=0;j<NBSECTORS;j++){//Début boucle secteurs
            pilote.GPrix.course[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
            //sleep(pilote.tbTempsSecteurs[j]); //Sleep pour la génération en temps réel
            //printf("Temps du secteur %d : %2.3f secondes\n",j+1,pilote.GPrix.course[i].tbTempsSect[j]);
        }
    }
    //sharedMem(SHM_WRITE,&pilote,1);//Ecriture dans le segment shm
    return 0;*/
}

/*
return: entier entre 0 et n
n: nb max de la génération aléatoire
 */
int getRandomInt(int min,int max) {
    int x = (rand()%(max-min))+min;
    return x;
}

/*
return: float(double) entre b et a
a: borne max
b: borne min
Cette fonction génère et renvoie un float entre min et max.
 */
double getRandomFloat(double a, double b) {
    double random,diff,r;
    static double sectorTime;

    random = ((double) rand()) / (double) RAND_MAX;
    diff = b - a;
    r = random * diff;
    sectorTime= a+r;

    return (sectorTime);
}
/*

*/
void getEssais(TPilote *ptPilote,int etape,char* nom_etape){
    int i,j;
    ptPilote->GPrix.nbTrsEssais[etape]= getRandomInt(1,NBTRSMAXESSAIS);
    ptPilote->GPrix.DNF= getRandomInt(MIN_DNF,MAX_DNF);//Génération d'un int pour savoir si le pilote sera out
    ptPilote->GPrix.lapPit= getRandomInt(1,ptPilote->GPrix.nbTrsEssais[etape]);//Choix du tour pour aller dans les stands
    printf("DNF probability: %d \n\n",ptPilote->GPrix.DNF);
    if(ptPilote->GPrix.DNF >= DNFPROB){
        ptPilote->GPrix.lapDNF= getRandomInt(1,ptPilote->GPrix.nbTrsEssais[etape]); //Tours à partir du quel le pilote est OUT
        ptPilote->GPrix.lapPit= getRandomInt(1,ptPilote->GPrix.lapDNF);//Choix du tour pour aller dans les stands
        printf("Nombre de tours prévus - %s : %d \n",nom_etape,ptPilote->GPrix.nbTrsEssais[etape]);
        printf("DNF lap: %d \n",ptPilote->GPrix.lapDNF);
        printf("Pit Stop: lap %d \n",ptPilote->GPrix.lapPit);
        for(i=0;i <= ptPilote->GPrix.lapDNF;i++){
            printf("|--------------|\n");
            printf("|*** Tour %d ***|\n",i);
            printf("|--------------|\n");
            if(i == ptPilote->GPrix.lapPit){//Si le tour n'est pas le tour pour aller aux stands
                ptPilote->GPrix.isStand= TRUE;
                for(j=0;j<NBSECTORS;j++){
                    switch(etape){
                        case ESSAI_P1:
                            ptPilote->GPrix.P1[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.P1[i].tbTempsSect[j]);
                            printf("Temps Secteur: %2.3f (PIT) \n",ptPilote->GPrix.P1[i].tbTempsSect[j]);
                            break;
                        case ESSAI_P2:
                            ptPilote->GPrix.P2[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.P1[i].tbTempsSect[j]);
                            printf("Temps Secteur: %2.3f (PIT) \n",ptPilote->GPrix.P2[i].tbTempsSect[j]);
                            break;
                        case ESSAI_P3:
                            ptPilote->GPrix.P3[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.P1[i].tbTempsSect[j]);
                            printf("Temps Secteur: %2.3f (PIT) \n",ptPilote->GPrix.P3[i].tbTempsSect[j]);
                            break;
                    }
                    sharedMem(SHM_WRITE,ptPilote,1);
                }
            }else if(i == ptPilote->GPrix.lapDNF){
                ptPilote->GPrix.isOut= TRUE;
                for(j=0;j<NBSECTORS;j++){
                    switch(etape){
                        case ESSAI_P1:
                            ptPilote->GPrix.P1[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.P1[i].tbTempsSect[j]);
                            printf("Temps Secteur: %2.3f (DNF) \n",ptPilote->GPrix.P1[i].tbTempsSect[j]);
                            break;
                        case ESSAI_P2:
                            ptPilote->GPrix.P2[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.P2[i].tbTempsSect[j]);
                            printf("Temps Secteur: %2.3f (DNF) \n",ptPilote->GPrix.P2[i].tbTempsSect[j]);
                            break;
                        case ESSAI_P3:
                            ptPilote->GPrix.P3[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.P3[i].tbTempsSect[j]);
                            printf("Temps Secteur: %2.3f (DNF) \n",ptPilote->GPrix.P3[i].tbTempsSect[j]);
                            break;
                    }
                    sharedMem(SHM_WRITE,ptPilote,1);
                }
            }else{
                for(j=0;j<NBSECTORS;j++){//Début boucle secteurs
                    printf("Temps Secteur: %2.3f \n",ptPilote->GPrix.P1[i].tbTempsSect[j]);
                    switch(etape){
                        case ESSAI_P1:
                            ptPilote->GPrix.P1[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                            //sleep(ptPilote->GPrix.P1[i].tbTempsSect[j]);
                            printf("Temps Secteur: %2.3f \n",ptPilote->GPrix.P1[i].tbTempsSect[j]);
                            break;
                        case ESSAI_P2:
                            ptPilote->GPrix.P2[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                            //sleep(ptPilote->GPrix.P2[i].tbTempsSect[j]);
                            printf("Temps Secteur: %2.3f \n",ptPilote->GPrix.P2[i].tbTempsSect[j]);
                            break;
                        case ESSAI_P3:
                            ptPilote->GPrix.P3[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                            //sleep(ptPilote->GPrix.P3[i].tbTempsSect[j]);
                            printf("Temps Secteur: %2.3f \n",ptPilote->GPrix.P3[i].tbTempsSect[j]);
                            break;
                    }
                    sharedMem(SHM_WRITE,ptPilote,1);
                }
            }
        }
    }else{
        printf("Nombre de tours prévus - %s : %d \n",nom_etape,ptPilote->GPrix.nbTrsEssais[etape]);
        printf("Pit Stop: lap %d \n",ptPilote->GPrix.lapPit);
        for(i=0;i<ptPilote->GPrix.nbTrsEssais[etape];i++){
            printf("|--------------|\n");
            printf("|*** Tour %d ***|\n",i);
            printf("|--------------|\n");
            if(i == ptPilote->GPrix.lapPit){//Si le tour n'est pas le tour pour aller aux stands
                ptPilote->GPrix.isStand= TRUE;
                for(j=0;j<NBSECTORS;j++){
                    switch(etape){
                        case ESSAI_P1:
                            ptPilote->GPrix.P1[i].tbTempsSect[j]= 0.0;
                            printf("Temps Secteur: %2.3f (PIT) \n",ptPilote->GPrix.P1[i].tbTempsSect[j]);
                            break;
                        case ESSAI_P2:
                            ptPilote->GPrix.P2[i].tbTempsSect[j]= 0.0;
                            printf("Temps Secteur: %2.3f (PIT) \n",ptPilote->GPrix.P2[i].tbTempsSect[j]);
                            break;
                        case ESSAI_P3:
                            ptPilote->GPrix.P3[i].tbTempsSect[j]= 0.0;
                            printf("Temps Secteur: %2.3f (PIT) \n",ptPilote->GPrix.P3[i].tbTempsSect[j]);
                            break;
                    }
                    sharedMem(SHM_WRITE,ptPilote,1);
                }
            }else{
                for(j=0;j<NBSECTORS;j++){//Début boucle secteurs
                    switch(etape){
                        case ESSAI_P1:
                            ptPilote->GPrix.P1[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                            //sleep(ptPilote->GPrix.P1[i].tbTempsSect[j]);
                            printf("Temps Secteur: %2.3f \n",ptPilote->GPrix.P1[i].tbTempsSect[j]);
                            break;
                        case ESSAI_P2:
                            ptPilote->GPrix.P2[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                            //sleep(ptPilote->GPrix.P2[i].tbTempsSect[j]);
                            printf("Temps Secteur: %2.3f \n",ptPilote->GPrix.P2[i].tbTempsSect[j]);
                            break;
                        case ESSAI_P3:
                            ptPilote->GPrix.P3[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                            //sleep(ptPilote->GPrix.P1[i].tbTempsSect[j]);
                            printf("Temps Secteur: %2.3f \n",ptPilote->GPrix.P3[i].tbTempsSect[j]);
                            break;
                    }
                    sharedMem(SHM_WRITE,ptPilote,1);
                }
            }
        }
    }
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
