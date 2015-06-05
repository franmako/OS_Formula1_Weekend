#include "pilote.h"

int main(){
    TPiloteID tbPIloteID[NBPILOTES]= {{44,"HAMILTON"},{6,"ROSBERG"},{3,"RICCIARDO"},{26,"KVYAT"},{19,"MASSA"},
    {77,"BOTTAS"},{5,"VETTEL"},{7,"RAIKKONEN"},{14,"ALONSO"},{22,"BUTTON"},{11,"PEREZ"},{27,"HULKENBERG"},
    {33,"VERSTAPPEN"},{55,"SAINZ Jr."},{8,"GROSJEAN"},{13,"MALDONADO"}}; //DB noms et nb pilotes

    int i;
    pid_t *tbPid_children = NULL; //Tb pour les pid des pilotes enfants
    pid_t pid;//pid pour le pilote parent
    tbPid_children= malloc(NBPILOTES * sizeof(pid_t));


    /* Démarrage des pilotes*/
    for (i=0;i < NBPILOTES;++i) {
        if ((pid = fork()) == 0) {
            srand(time(NULL));//Init random
            TPilote pilote;
            TPilote *ptPilote= &pilote;

            //Init pilote
            pilote.piloteID.nbPilote= tbPIloteID[i].nbPilote;
            pilote.piloteID.nomPilote= tbPIloteID[i].nomPilote;
            printf("Pilote: %s - Num: %d",pilote.piloteID.nomPilote,pilote.piloteID.nbPilote);
            //Essais
            getStageTime(ptPilote,ESSAI_P1,"Essais Vendredi Matin");
            getStageTime(ptPilote,ESSAI_P2,"Essais Vendredi Après-Midi");
            getStageTime(ptPilote,ESSAI_P3,"Essais Samedi Matin");
            //Qualifs
            getStageTime(ptPilote,QUALIF_Q1,"Qualifs Q1");

            exit(0);
        }else {
            tbPid_children[i] = pid;
        }
    }

    /*if(pilote.GPrix.isQualifQ2 == TRUE){
        getStageTime(ptPilote,QUALIF_Q2,"Qualifs Q2");
        if(pilote.GPrix.isQualifQ3 == TRUE){
            getStageTime(ptPilote,QUALIF_Q3,"Qualifs Q3");
        }
    }*/

    //Course

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

int floatComp(const (void*)TTour tour1,const (void*)TTour tour2){
    if(tour1->tempsTour < tour2->tempsTour)
        return (-1);
    return (tour1->tempsTour > tour2->tempsTour);
}*/
/*

*/
void getStageTime(TPilote *ptPilote,int etape,char* nom_etape){
    int i,j;
    ptPilote->GPrix.nbTrs[etape]= getRandomInt(1,NBTRSMAXESSAIS);//Génère le nb tours de l'étape
    ptPilote->GPrix.DNF= getRandomInt(MIN_DNF,MAX_DNF);//Génération d'un int pour savoir si le pilote sera out
    ptPilote->GPrix.lapPit= getRandomInt(1,ptPilote->GPrix.nbTrs[etape]);//Choix du tour pour aller dans les stands
    if(ptPilote->GPrix.DNF >= DNFPROB){
        ptPilote->GPrix.lapDNF= getRandomInt(1,ptPilote->GPrix.nbTrs[etape]); //Tours à partir du quel le pilote est OUT
        ptPilote->GPrix.lapPit= getRandomInt(1,ptPilote->GPrix.lapDNF);//Choix du tour pour aller dans les stands
        for(i=0;i <= ptPilote->GPrix.lapDNF;i++){
            if(i == ptPilote->GPrix.lapPit){//Tour PIT
                for(j=0;j<NBSECTORS;j++){
                    switch(etape){
                        case ESSAI_P1:
                            ptPilote->GPrix.P1[i].isStand= TRUE;//Variable pour indiquer que c'est le tour PIT
                            ptPilote->GPrix.P1[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.P1[i].tbTempsSect[j]); //Sleep pour envoyer les données en temps réel
                            ptPilote->GPrix.P1[i].tempsTour= 0.0;
                            break;
                        case ESSAI_P2:
                            ptPilote->GPrix.P2[i].isStand= TRUE;
                            ptPilote->GPrix.P2[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.P1[i].tbTempsSect[j]);
                            ptPilote->GPrix.P2[i].tempsTour= 0.0;
                            break;
                        case ESSAI_P3:
                            ptPilote->GPrix.P3[i].isStand= TRUE;
                            ptPilote->GPrix.P3[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.P1[i].tbTempsSect[j]);
                            ptPilote->GPrix.P3[i].tempsTour= 0.0;
                            break;
                        case QUALIF_Q1:
                            ptPilote->GPrix.Q1[i].isStand= TRUE;
                            ptPilote->GPrix.Q1[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.Q1[i].tbTempsSect[j]);
                            ptPilote->GPrix.Q1[i].tempsTour= 0.0;
                            break;
                        case QUALIF_Q2:
                            ptPilote->GPrix.Q2[i].isStand= TRUE;
                            ptPilote->GPrix.Q2[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.Q2[i].tbTempsSect[j]);
                            ptPilote->GPrix.Q2[i].tempsTour= 0.0;
                            break;
                        case QUALIF_Q3:
                            ptPilote->GPrix.Q3[i].isStand= TRUE;
                            ptPilote->GPrix.Q3[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.Q1[i].tbTempsSect[j]);
                            ptPilote->GPrix.Q3[i].tempsTour= 0.0;
                            break;
                    }
                    sharedMem(SHM_WRITE,ptPilote,1);
                }
            }else if(i == ptPilote->GPrix.lapDNF){
                for(j=0;j<NBSECTORS;j++){
                    switch(etape){
                        case ESSAI_P1:
                            ptPilote->GPrix.P1[i].isOut= TRUE;//Variable pour indiquer que la voiture est OUT pour ce tour
                            ptPilote->GPrix.P1[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.P1[i].tbTempsSect[j]);
                            ptPilote->GPrix.P1[i].tempsTour= 0.0;
                            break;
                        case ESSAI_P2:
                            ptPilote->GPrix.P2[i].isOut= TRUE;
                            ptPilote->GPrix.P2[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.P2[i].tbTempsSect[j]);
                            ptPilote->GPrix.P2[i].tempsTour= 0.0;
                            break;
                        case ESSAI_P3:
                            ptPilote->GPrix.P3[i].isOut= TRUE;
                            ptPilote->GPrix.P3[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.P3[i].tbTempsSect[j]);
                            ptPilote->GPrix.P3[i].tempsTour= 0.0;
                            break;
                        case QUALIF_Q1:
                            ptPilote->GPrix.Q1[i].isOut= TRUE;
                            ptPilote->GPrix.Q1[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.Q1[i].tbTempsSect[j]);
                            ptPilote->GPrix.Q1[i].tempsTour= 0.0;
                            break;
                        case QUALIF_Q2:
                            ptPilote->GPrix.Q2[i].isOut= TRUE;
                            ptPilote->GPrix.Q2[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.Q2[i].tbTempsSect[j]);
                            ptPilote->GPrix.Q2[i].tempsTour= 0.0;
                            break;
                        case QUALIF_Q3:
                            ptPilote->GPrix.Q3[i].isOut= TRUE;
                            ptPilote->GPrix.Q3[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.Q1[i].tbTempsSect[j]);
                            ptPilote->GPrix.Q3[i].tempsTour= 0.0;
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
                            ptPilote->GPrix.P1[i].tempsTour += ptPilote->GPrix.P1[i].tbTempsSect[j];
                            break;
                        case ESSAI_P2:
                            ptPilote->GPrix.P2[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                            //sleep(ptPilote->GPrix.P2[i].tbTempsSect[j]);
                            ptPilote->GPrix.P2[i].tempsTour += ptPilote->GPrix.P2[i].tbTempsSect[j];
                            break;
                        case ESSAI_P3:
                            ptPilote->GPrix.P3[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                            //sleep(ptPilote->GPrix.P3[i].tbTempsSect[j]);
                            ptPilote->GPrix.P3[i].tempsTour += ptPilote->GPrix.P3[i].tbTempsSect[j];
                            break;
                        case QUALIF_Q1:
                            ptPilote->GPrix.Q1[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);
                            //sleep(ptPilote->GPrix.Q1[i].tbTempsSect[j]);
                            ptPilote->GPrix.Q1[i].tempsTour += ptPilote->GPrix.Q1[i].tbTempsSect[j];
                            break;
                        case QUALIF_Q2:
                            ptPilote->GPrix.Q2[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);
                            //sleep(ptPilote->GPrix.Q2[i].tbTempsSect[j]);
                            ptPilote->GPrix.Q2[i].tempsTour += ptPilote->GPrix.Q2[i].tbTempsSect[j];
                            break;
                        case QUALIF_Q3:
                            ptPilote->GPrix.Q3[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);
                            //sleep(ptPilote->GPrix.Q3[i].tbTempsSect[j]);
                            ptPilote->GPrix.Q3[i].tempsTour += ptPilote->GPrix.Q3[i].tbTempsSect[j];
                            break;
                    }
                    sharedMem(SHM_WRITE,ptPilote,1);
                }
            }
        }
    }else{
        printf("| -- Nombre de tours prévus - %s : %d --| \n",nom_etape,ptPilote->GPrix.nbTrs[etape]);
        for(i=0;i<ptPilote->GPrix.nbTrs[etape];i++){
            printf("|--------------|\n");
            printf("|*** Tour %d ***|\n",i);
            printf("|--------------|\n");
            if(i == ptPilote->GPrix.lapPit){//Si le tour n'est pas le tour pour aller aux stands
                for(j=0;j<NBSECTORS;j++){
                    switch(etape){
                        case ESSAI_P1:
                            ptPilote->GPrix.P1[i].isStand= TRUE;
                            ptPilote->GPrix.P1[i].tbTempsSect[j]= 0.0;
                            ptPilote->GPrix.P1[i].tempsTour= 0.0;
                            break;
                        case ESSAI_P2:
                            ptPilote->GPrix.P2[i].isStand= TRUE;
                            ptPilote->GPrix.P2[i].tbTempsSect[j]= 0.0;
                            ptPilote->GPrix.P2[i].tempsTour= 0.0;
                            break;
                        case ESSAI_P3:
                            ptPilote->GPrix.P3[i].isStand= TRUE;
                            ptPilote->GPrix.P3[i].tbTempsSect[j]= 0.0;
                            ptPilote->GPrix.P3[i].tempsTour= 0.0;
                            break;
                        case QUALIF_Q1:
                            ptPilote->GPrix.Q1[i].isStand= TRUE;
                            ptPilote->GPrix.Q1[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.Q1[i].tbTempsSect[j]);
                            ptPilote->GPrix.Q1[i].tempsTour= 0.0;
                            break;
                        case QUALIF_Q2:
                            ptPilote->GPrix.Q2[i].isStand= TRUE;
                            ptPilote->GPrix.Q2[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.Q2[i].tbTempsSect[j]);
                            ptPilote->GPrix.Q2[i].tempsTour= 0.0;
                            break;
                        case QUALIF_Q3:
                            ptPilote->GPrix.Q3[i].isStand= TRUE;
                            ptPilote->GPrix.Q3[i].tbTempsSect[j]= 0.0;
                            //sleep(ptPilote->GPrix.Q1[i].tbTempsSect[j]);
                            ptPilote->GPrix.Q3[i].tempsTour= 0.0;
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
                            ptPilote->GPrix.P1[i].tempsTour += ptPilote->GPrix.P1[i].tbTempsSect[j];
                            break;
                        case ESSAI_P2:
                            ptPilote->GPrix.P2[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                            //sleep(ptPilote->GPrix.P2[i].tbTempsSect[j]);
                            ptPilote->GPrix.P2[i].tempsTour += ptPilote->GPrix.P2[i].tbTempsSect[j];
                            break;
                        case ESSAI_P3:
                            ptPilote->GPrix.P3[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);//Génération temps secteur entre 30.0 et 40.0
                            //sleep(ptPilote->GPrix.P1[i].tbTempsSect[j]);
                            ptPilote->GPrix.P3[i].tempsTour += ptPilote->GPrix.P3[i].tbTempsSect[j];
                            break;
                        case QUALIF_Q1:
                            ptPilote->GPrix.Q1[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);
                            //sleep(ptPilote->GPrix.Q1[i].tbTempsSect[j]);
                            ptPilote->GPrix.Q1[i].tempsTour += ptPilote->GPrix.Q1[i].tbTempsSect[j];
                            break;
                        case QUALIF_Q2:
                            ptPilote->GPrix.Q2[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);
                            //sleep(ptPilote->GPrix.Q2[i].tbTempsSect[j]);
                            ptPilote->GPrix.Q2[i].tempsTour += ptPilote->GPrix.Q2[i].tbTempsSect[j];
                            break;
                        case QUALIF_Q3:
                            ptPilote->GPrix.Q3[i].tbTempsSect[j]= getRandomFloat(SEC_MIN,SEC_MAX);
                            //sleep(ptPilote->GPrix.Q3[i].tbTempsSect[j]);
                            ptPilote->GPrix.Q3[i].tempsTour += ptPilote->GPrix.Q3[i].tbTempsSect[j];
                            break;
                    }
                    sharedMem(SHM_WRITE,ptPilote,1);
                }
            }
        }
    }
    //qsort((void*)ptPilote,NBTRSMAXQUALIF,sizeof(TPilote),floatComp());
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
        printf("Ecriture dans la mémoire partagée par %s \n",ptPilote->piloteID.nomPilote);
    }else{
        memcpy(ptPilote,data, sizeof(TPilote));
    }
    //Détachement du segment
    if (shmdt(data) == ERROR) {
        perror("shmdt");
        exit(1);
    }
}
