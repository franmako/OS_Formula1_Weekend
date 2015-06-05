#include "afficheur.h"

main()
{
    key_t key;
    int shmid;
    void* data;
    int mode= SHM_READ;
    double test;

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
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == ERROR) {
        perror("shmget");
        exit(1);
    }

    /* attach to the segment to get a pointer to it: */
    data = shmat(shmid, (void*)0, 0);
    if (data == (void*)(ERROR)) {
        perror("shmat");
        exit(1);
    }

    /* read or modify the segment, based on the command line: */
    if (mode == SHM_WRITE) {
        printf("Ecriture dans le segment: \"%2.3f\"\n", test);
        memcpy(data, &test, SHM_SIZE);
    } else
        printf("Le segment contiens: \"%2.3f\"\n", *(double*)data);

    /* detach from the segment: */
    if (shmdt(data) == ERROR) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}

void afficheur(TPilote pilote, int etape, char* nom_etape){
    int i,j;
    int nbTrs= pilote.GPrix.nbTrs[etape];
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
