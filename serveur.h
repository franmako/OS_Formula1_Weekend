#include "pilote.h"

#define SHM_READ 0

/* STRUCTURES */
typedef struct{
    int pid;
    int nbPilote;
    TTour tour;
}Classement;

/* PROTOTYPES */
void sharedMem(int,TPilote*,int);
void afficheur(TPilote,int,char*);
