#include "serveur.h"

int main(){
    int i,j;
    int nbTours= NBTRSCOURSE;
    TPilote pilote_serv;
    TPilote *ptPilote= &pilote_serv;

    sharedMem(SHM_READ,ptPilote,1);
    //Affichage Essais
    //afficheur(pilote_serv,ESSAI_P1,"Vendredi Matin");
    //afficheur(pilote_serv,ESSAI_P2,"Vendredi Après-Midi");
    //afficheur(pilote_serv,ESSAI_P3,"Samedi Matin");
    //Affichage Qualifs
    afficheur(pilote_serv,QUALIF_Q1,"Qualification - Q1");

    return 0;
}
void afficheur(TPilote pilote, int etape, char* nom_etape){
    int i,j;
    int nbTrs= pilote.GPrix.nbTrs[etape];
    printf("Meilleur temps tour: %f",pilote.GPrix.bestLap_Q1);
    printf("N° Pilote: %d \n",pilote.nbPilote);
    printf("Nombre de tours prévus - %s : %d \n",nom_etape,nbTrs);
    for(i=0;i<nbTrs;i++){
        printf("|--------------|\n");
        printf("|*** Tour %d ***|\n",i);
        printf("|--------------|\n");
        for(j=0;j<NBSECTORS;j++){
            switch(etape){
                case ESSAI_P1:
                    if(pilote.GPrix.P1[i].isStand == TRUE){
                        printf("Temps secteur: %2.3f (PIT) \n",pilote.GPrix.P1[i].tbTempsSect[j]);
                    }else if(pilote.GPrix.P1[i].isOut == TRUE){
                        printf("Temps secteur: %2.3f (DNF) \n",pilote.GPrix.P1[i].tbTempsSect[j]);
                    }else{
                        printf("Temps secteur: %2.3f \n",pilote.GPrix.P1[i].tbTempsSect[j]);
                    }
                    break;
                case ESSAI_P2:
                    if(pilote.GPrix.P2[i].isStand == TRUE){
                        printf("Temps secteur: %2.3f (PIT) \n",pilote.GPrix.P2[i].tbTempsSect[j]);
                    }else if(pilote.GPrix.P2[i].isOut == TRUE){
                        printf("Temps secteur: %2.3f (DNF) \n",pilote.GPrix.P2[i].tbTempsSect[j]);
                    }else{
                        printf("Temps secteur: %2.3f \n",pilote.GPrix.P2[i].tbTempsSect[j]);
                    }
                    break;
                case ESSAI_P3:
                    if(pilote.GPrix.P3[i].isStand == TRUE){
                        printf("Temps secteur: %2.3f (PIT) \n",pilote.GPrix.P3[i].tbTempsSect[j]);
                    }else if(pilote.GPrix.P3[i].isOut == TRUE){
                        printf("Temps secteur: %2.3f (DNF) \n",pilote.GPrix.P3[i].tbTempsSect[j]);
                    }else{
                        printf("Temps secteur: %2.3f \n",pilote.GPrix.P3[i].tbTempsSect[j]);
                    }
                    break;
                case QUALIF_Q1:
                    if(pilote.GPrix.Q1[i].isStand == TRUE){
                        printf("Temps secteur: %2.3f (PIT) \n",pilote.GPrix.Q1[i].tbTempsSect[j]);
                    }else if(pilote.GPrix.Q1[i].isOut == TRUE){
                        printf("Temps secteur: %2.3f (DNF) \n",pilote.GPrix.Q1[i].tbTempsSect[j]);
                    }else{
                        printf("Temps secteur: %2.3f \n",pilote.GPrix.Q1[i].tbTempsSect[j]);
                    }
                    break;
                case QUALIF_Q2:
                    if(pilote.GPrix.Q2[i].isStand == TRUE){
                        printf("Temps secteur: %2.3f (PIT) \n",pilote.GPrix.Q2[i].tbTempsSect[j]);
                    }else if(pilote.GPrix.Q2[i].isOut == TRUE){
                        printf("Temps secteur: %2.3f (DNF) \n",pilote.GPrix.Q2[i].tbTempsSect[j]);
                    }else{
                        printf("Temps secteur: %2.3f \n",pilote.GPrix.Q2[i].tbTempsSect[j]);
                    }
                    break;
                case QUALIF_Q3:
                    if(pilote.GPrix.Q3[i].isStand == TRUE){
                        printf("Temps secteur: %2.3f (PIT) \n",pilote.GPrix.Q3[i].tbTempsSect[j]);
                    }else if(pilote.GPrix.Q3[i].isOut == TRUE){
                        printf("Temps secteur: %2.3f (DNF) \n",pilote.GPrix.Q3[i].tbTempsSect[j]);
                    }else{
                        printf("Temps secteur: %2.3f \n",pilote.GPrix.Q3[i].tbTempsSect[j]);
                    }
                    break;
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
    }else

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
