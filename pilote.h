#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h> /* Pour l'utilisation de fmod pour le calcul des modulo pour float */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define ERROR -1
#define NBTRSCOURSE 5
#define NBTRSESSAIS 5
#define NBTRSQUALIF 5
#define NBSECTORS 3
#define SEC_MIN 30.0
#define SEC_MAX 40.0
#define SHM_WRITE 2


/* -- STRUCTURES -- */
typedef struct{
    int minutes;
    double secondes;
}FTime;

typedef struct{
    double tempsTour;
    double tbTempsSect[NBSECTORS];
}TTour;

typedef struct{
    int nbToursEssais;
    int nbToursQualif;
    int nbToursCourse;
    TTour essais[NBTRSESSAIS];
    TTour qualif[NBTRSQUALIF];
    TTour course[NBTRSCOURSE];
}TWECourse;

typedef struct{
    int pid;
    int nbPilote;
    TWECourse GPrix;
}TPilote;

/* -- PROTOTYPES -- */
void getTotalTime(double*);
double getSectorTime(double,double);
void sharedMem(int,TPilote*,int);

