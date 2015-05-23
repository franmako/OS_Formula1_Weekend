#include "pilote.h"

int main(){
    srand(time(NULL));//Init random
    int i,j,nbTrsP1,nbTrsP2,nbTrsP3;
    TPilote pilote;
    TPilote *ptPilote= &pilote;
    pilote.nbPilote = 44;
    pilote.GPrix.isOut= FALSE;
    pilote.GPrix.isStand= FALSE;

    //Essais P1
    pilote.GPrix.nbTrsEssais[ESSAI_P1]= getRandomInt(1,NBTRSMAXESSAIS);
    pilote.GPrix.DNF= getRandomInt(MIN_DNF,MAX_DNF);//Génération d'un int pour savoir si le pilote sera out
    pilote.GPrix.lapPit= getRandomInt(1,pilote.GPrix.nbTrsEssais[ESSAI_P1]);//Choix du tour pour aller dans les stands
    printf("DNF probability: %d \n",pilote.GPrix.DNF);
    if(pilote.GPrix.DNF >= DNFPROB){
        pilote.GPrix.lapDNF= getRandomInt(1,pilote.GPrix.nbTrsEssais[ESSAI_P1]); //Tours à partir du quel le pilote est OUT
        pilote.GPrix.lapPit= getRandomInt(1,pilote.GPrix.lapDNF);//Choix du tour pour aller dans les stands
        printf("DNF lap: %d \n",pilote.GPrix.lapDNF);
        printf("Pit Stop: lap %d \n",pilote.GPrix.lapPit);
        printf("Nb tours essais prévus, vendredi matin: %d \n",pilote.GPrix.nbTrsEssais[ESSAI_P1]);
        for(i=0;i <= pilote.GPrix.lapDNF;i++){
            printf("|--------------|\n");
            printf("|*** Tour %d ***|\n",i);
            printf("|--------------|\n");
            if(i == pilote.GPrix.lapPit){//Si le tour n'est pas le tour pour aller aux stands
                pilote.GPrix.isStand= TRUE;
                for(j=0;j<NBSECTORS;j++){
                    pilote.GPrix.P1[i].tbTempsSect[j]= 0.0;
                    printf("Temps Secteur: %2.3f (P) \n",pilote.GPrix.P1[i].tbTempsSect[j]);
                }
                sharedMem(SHM_WRITE,ptPilote,1);
            }else if(i == pilote.GPrix.lapDNF){
                pilote.GPrix.isOut= TRUE;
                for(j=0;j<NBSECTORS;j++){
                    pilote.GPrix.P1[i].tbTempsSect[j]= 0.0;
                    printf("Temps Secteur: %2.3f (DNF) \n",pilote.GPrix.P1[i].tbTempsSect[j]);
                }
                sharedMem(SHM_WRITE,ptPilote,1);
            }else{
                for(j=0;j<NBSECTORS;j++){//Début boucle secteurs
                    pilote.GPrix.P1[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                    //sleep(pilote.GPrix.P1[i].tbTempsSect[j]);
                    printf("Temps Secteur: %2.3f \n",pilote.GPrix.P1[i].tbTempsSect[j]);
                }
                sharedMem(SHM_WRITE,ptPilote,1);
            }
        }
    }else{
        printf("Pit Stop: lap %d \n",pilote.GPrix.lapPit);
        printf("Nb tours essais vendredi matin: %d \n",pilote.GPrix.nbTrsEssais[ESSAI_P1]);
        for(i=0;i<pilote.GPrix.nbTrsEssais[ESSAI_P1];i++){
            printf("|--------------|\n");
            printf("|*** Tour %d ***|\n",i);
            printf("|--------------|\n");
            if(i == pilote.GPrix.lapPit){//Si le tour n'est pas le tour pour aller aux stands
                pilote.GPrix.isStand= TRUE;
                for(j=0;j<NBSECTORS;j++){
                    pilote.GPrix.P1[i].tbTempsSect[j]= 0.0;
                    printf("Temps Secteur: %2.3f (P) \n",pilote.GPrix.P1[i].tbTempsSect[j]);
                }
            }else{
                for(j=0;j<NBSECTORS;j++){//Début boucle secteurs
                    pilote.GPrix.P1[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                    //sleep(pilote.GPrix.P1[i].tbTempsSect[j]);
                    printf("Temps Secteur: %2.3f \n",pilote.GPrix.P1[i].tbTempsSect[j]);
                }
            }
        }
    }
    //Essais P2
    pilote.GPrix.nbTrsEssais[ESSAI_P2]= getRandomInt(1,NBTRSMAXESSAIS);
    pilote.GPrix.DNF= getRandomInt(MIN_DNF,MAX_DNF);//Génération d'un int pour savoir si le pilote sera out
    pilote.GPrix.lapPit= getRandomInt(1,pilote.GPrix.nbTrsEssais[ESSAI_P2]);//Choix du tour pour aller dans les stands
    printf("DNF probability: %d \n",pilote.GPrix.DNF);
    if(pilote.GPrix.DNF >= DNFPROB){
        pilote.GPrix.lapDNF= getRandomInt(1,pilote.GPrix.nbTrsEssais[ESSAI_P2]); //Tours à partir du quel le pilote est OUT
        pilote.GPrix.lapPit= getRandomInt(1,pilote.GPrix.lapDNF);//Choix du tour pour aller dans les stands
        printf("DNF lap: %d \n",pilote.GPrix.lapDNF);
        printf("Pit Stop: lap %d \n",pilote.GPrix.lapPit);
        printf("Nb tours essais prévus, vendredi après-midi: %d \n",pilote.GPrix.nbTrsEssais[ESSAI_P2]);
        for(i=0;i <= pilote.GPrix.lapDNF;i++){
            printf("|--------------|\n");
            printf("|*** Tour %d ***|\n",i);
            printf("|--------------|\n");
            if(i == pilote.GPrix.lapPit){//Si le tour n'est pas le tour pour aller aux stands
                pilote.GPrix.isStand= TRUE;
                for(j=0;j<NBSECTORS;j++){
                    pilote.GPrix.P2[i].tbTempsSect[j]= 0.0;
                    printf("Temps Secteur: %2.3f (P) \n",pilote.GPrix.P2[i].tbTempsSect[j]);
                }
                sharedMem(SHM_WRITE,ptPilote,1);
            }else if(i == pilote.GPrix.lapDNF){
                pilote.GPrix.isOut= TRUE;
                for(j=0;j<NBSECTORS;j++){
                    pilote.GPrix.P2[i].tbTempsSect[j]= 0.0;
                    printf("Temps Secteur: %2.3f (DNF) \n",pilote.GPrix.P2[i].tbTempsSect[j]);
                }
                sharedMem(SHM_WRITE,ptPilote,1);
            }else{
                for(j=0;j<NBSECTORS;j++){//Début boucle secteurs
                    pilote.GPrix.P2[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                    //sleep(pilote.GPrix.P1[i].tbTempsSect[j]);
                    printf("Temps Secteur: %2.3f \n",pilote.GPrix.P2[i].tbTempsSect[j]);
                }
                sharedMem(SHM_WRITE,ptPilote,1);
            }
        }
    }else{
        printf("Pit Stop: lap %d \n",pilote.GPrix.lapPit);
        printf("Nb tours essais vendredi après-midi: %d \n",pilote.GPrix.nbTrsEssais[ESSAI_P2]);
        for(i=0;i<pilote.GPrix.nbTrsEssais[ESSAI_P2];i++){
            printf("|--------------|\n");
            printf("|*** Tour %d ***|\n",i);
            printf("|--------------|\n");
            if(i == pilote.GPrix.lapPit){//Si le tour n'est pas le tour pour aller aux stands
                pilote.GPrix.isStand= TRUE;
                for(j=0;j<NBSECTORS;j++){
                    pilote.GPrix.P2[i].tbTempsSect[j]= 0.0;
                    printf("Temps Secteur: %2.3f (P) \n",pilote.GPrix.P2[i].tbTempsSect[j]);
                }
            }else{
                for(j=0;j<NBSECTORS;j++){//Début boucle secteurs
                    pilote.GPrix.P2[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                    //sleep(pilote.GPrix.P1[i].tbTempsSect[j]);
                    printf("Temps Secteur: %2.3f \n",pilote.GPrix.P2[i].tbTempsSect[j]);
                }
            }
        }
    }
     //Essais P3
    pilote.GPrix.nbTrsEssais[ESSAI_P3]= getRandomInt(1,NBTRSMAXESSAIS);
    pilote.GPrix.DNF= getRandomInt(MIN_DNF,MAX_DNF);//Génération d'un int pour savoir si le pilote sera out
    pilote.GPrix.lapPit= getRandomInt(1,pilote.GPrix.nbTrsEssais[ESSAI_P3]);//Choix du tour pour aller dans les stands
    printf("DNF probability: %d \n",pilote.GPrix.DNF);
    if(pilote.GPrix.DNF >= DNFPROB){
        pilote.GPrix.lapDNF= getRandomInt(1,pilote.GPrix.nbTrsEssais[ESSAI_P3]); //Tours à partir du quel le pilote est OUT
        pilote.GPrix.lapPit= getRandomInt(1,pilote.GPrix.lapDNF);//Choix du tour pour aller dans les stands
        printf("DNF lap: %d \n",pilote.GPrix.lapDNF);
        printf("Pit Stop: lap %d \n",pilote.GPrix.lapPit);
        printf("Nb tours essais prévus, samedi matin: %d \n",pilote.GPrix.nbTrsEssais[ESSAI_P3]);
        for(i=0;i <= pilote.GPrix.lapDNF;i++){
            printf("|--------------|\n");
            printf("|*** Tour %d ***|\n",i);
            printf("|--------------|\n");
            if(i == pilote.GPrix.lapPit){//Si le tour n'est pas le tour pour aller aux stands
                pilote.GPrix.isStand= TRUE;
                for(j=0;j<NBSECTORS;j++){
                    pilote.GPrix.P3[i].tbTempsSect[j]= 0.0;
                    printf("Temps Secteur: %2.3f (P) \n",pilote.GPrix.P3[i].tbTempsSect[j]);
                }
                sharedMem(SHM_WRITE,ptPilote,1);
            }else if(i == pilote.GPrix.lapDNF){
                pilote.GPrix.isOut= TRUE;
                for(j=0;j<NBSECTORS;j++){
                    pilote.GPrix.P3[i].tbTempsSect[j]= 0.0;
                    printf("Temps Secteur: %2.3f (DNF) \n",pilote.GPrix.P3[i].tbTempsSect[j]);
                }
                sharedMem(SHM_WRITE,ptPilote,1);
            }else{
                for(j=0;j<NBSECTORS;j++){//Début boucle secteurs
                    pilote.GPrix.P3[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                    //sleep(pilote.GPrix.P1[i].tbTempsSect[j]);
                    printf("Temps Secteur: %2.3f \n",pilote.GPrix.P3[i].tbTempsSect[j]);
                }
                sharedMem(SHM_WRITE,ptPilote,1);
            }
        }
    }else{
        printf("Pit Stop: lap %d \n",pilote.GPrix.lapPit);
        printf("Nb tours essais samedi matin: %d \n",pilote.GPrix.nbTrsEssais[ESSAI_P3]);
        for(i=0;i<pilote.GPrix.nbTrsEssais[ESSAI_P3];i++){
            printf("|--------------|\n");
            printf("|*** Tour %d ***|\n",i);
            printf("|--------------|\n");
            if(i == pilote.GPrix.lapPit){//Si le tour n'est pas le tour pour aller aux stands
                pilote.GPrix.isStand= TRUE;
                for(j=0;j<NBSECTORS;j++){
                    pilote.GPrix.P3[i].tbTempsSect[j]= 0.0;
                    printf("Temps Secteur: %2.3f (P) \n",pilote.GPrix.P3[i].tbTempsSect[j]);
                }
            }else{
                for(j=0;j<NBSECTORS;j++){//Début boucle secteurs
                    pilote.GPrix.P3[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                    //sleep(pilote.GPrix.P1[i].tbTempsSect[j]);
                    printf("Temps Secteur: %2.3f \n",pilote.GPrix.P3[i].tbTempsSect[j]);
                }
            }
        }
    }
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
void getEssais(int etape_essais){
    pilote.GPrix.nbTrsEssais[etape_essais]= getRandomInt(1,NBTRSMAXESSAIS);
    pilote.GPrix.DNF= getRandomInt(MIN_DNF,MAX_DNF);//Génération d'un int pour savoir si le pilote sera out
    pilote.GPrix.lapPit= getRandomInt(1,pilote.GPrix.nbTrsEssais[etape_essais]);//Choix du tour pour aller dans les stands
    printf("DNF probability: %d \n",pilote.GPrix.DNF);
    if(pilote.GPrix.DNF >= DNFPROB){
        pilote.GPrix.lapDNF= getRandomInt(1,pilote.GPrix.nbTrsEssais[etape_essais]); //Tours à partir du quel le pilote est OUT
        pilote.GPrix.lapPit= getRandomInt(1,pilote.GPrix.lapDNF);//Choix du tour pour aller dans les stands
        printf("DNF lap: %d \n",pilote.GPrix.lapDNF);
        printf("Pit Stop: lap %d \n",pilote.GPrix.lapPit);
        printf("Nb tours essais prévus, vendredi matin: %d \n",pilote.GPrix.nbTrsEssais[etape_essais]);
        for(i=0;i <= pilote.GPrix.lapDNF;i++){
            printf("|--------------|\n");
            printf("|*** Tour %d ***|\n",i);
            printf("|--------------|\n");
            if(i == pilote.GPrix.lapPit){//Si le tour n'est pas le tour pour aller aux stands
                pilote.GPrix.isStand= TRUE;
                for(j=0;j<NBSECTORS;j++){
                    pilote.GPrix.P1[i].tbTempsSect[j]= 0.0;
                    printf("Temps Secteur: %2.3f (P) \n",pilote.GPrix.P1[i].tbTempsSect[j]);
                }
                sharedMem(SHM_WRITE,ptPilote,1);
            }else if(i == pilote.GPrix.lapDNF){
                pilote.GPrix.isOut= TRUE;
                for(j=0;j<NBSECTORS;j++){
                    pilote.GPrix.P1[i].tbTempsSect[j]= 0.0;
                    printf("Temps Secteur: %2.3f (DNF) \n",pilote.GPrix.P1[i].tbTempsSect[j]);
                }
                sharedMem(SHM_WRITE,ptPilote,1);
            }else{
                for(j=0;j<NBSECTORS;j++){//Début boucle secteurs
                    pilote.GPrix.P1[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                    //sleep(pilote.GPrix.P1[i].tbTempsSect[j]);
                    printf("Temps Secteur: %2.3f \n",pilote.GPrix.P1[i].tbTempsSect[j]);
                }
                sharedMem(SHM_WRITE,ptPilote,1);
            }
        }
    }else{
        printf("Pit Stop: lap %d \n",pilote.GPrix.lapPit);
        printf("Nb tours essais vendredi matin: %d \n",pilote.GPrix.nbTrsEssais[etape_essais]);
        for(i=0;i<pilote.GPrix.nbTrsEssais[etape_essais];i++){
            printf("|--------------|\n");
            printf("|*** Tour %d ***|\n",i);
            printf("|--------------|\n");
            if(i == pilote.GPrix.lapPit){//Si le tour n'est pas le tour pour aller aux stands
                pilote.GPrix.isStand= TRUE;
                for(j=0;j<NBSECTORS;j++){
                    pilote.GPrix.P1[i].tbTempsSect[j]= 0.0;
                    printf("Temps Secteur: %2.3f (P) \n",pilote.GPrix.P1[i].tbTempsSect[j]);
                }
            }else{
                for(j=0;j<NBSECTORS;j++){//Début boucle secteurs
                    pilote.GPrix.P1[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                    //sleep(pilote.GPrix.P1[i].tbTempsSect[j]);
                    printf("Temps Secteur: %2.3f \n",pilote.GPrix.P1[i].tbTempsSect[j]);
                }
            }
        }
    }
}
*/
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
