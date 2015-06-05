#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/wait.h>

#define ERROR -1
#define NBTRSCOURSE 5
#define NBTRSMAXESSAIS 10
#define NBTRSMAXQUALIF 5
#define NBSECTORS 3
#define SEC_MIN 30.0
#define SEC_MAX 40.0
#define SHM_WRITE 2
#define ESSAI_P1 0
#define ESSAI_P2 1
#define ESSAI_P3 2
#define QUALIF_Q1 3
#define QUALIF_Q2 4
#define QUALIF_Q3 5
#define TRUE 1
#define FALSE 0
#define MIN_DNF 0
#define MAX_DNF 100
#define DNFPROB 80
#define NBPILOTES 16


/* -- STRUCTURES -- */
typedef struct{
    int nbPilote;
    char *nomPilote;
}TPiloteID;
typedef struct{
    int minutes;
    double secondes;
}FTime;

typedef struct{
    int isOut;//DNF
    int isStand;//PIT
    double tempsTour;
    double tbTempsSect[NBSECTORS];
}TTour;

typedef struct{
    int nbTrs[6]; //Nb tours essais + qualifs
    //Essais
    int lapPit;
    int DNF;
    int lapDNF;
    TTour P1[NBTRSMAXESSAIS];
    TTour P2[NBTRSMAXESSAIS];
    TTour P3[NBTRSMAXESSAIS];
    //Qualifs
    TTour Q1[NBTRSMAXQUALIF];
    double bestLap_Q1;
    int isQualifQ2;
    TTour Q2[NBTRSMAXQUALIF];
    int isQualifQ3;
    TTour Q3[NBTRSMAXQUALIF];
    int classementCourse;
    TTour course[NBTRSCOURSE];
}TWECourse;

typedef struct{
    int pid;
    TPiloteID piloteID;
    TWECourse GPrix;
}TPilote;

/* -- PROTOTYPES -- */
int getRandomInt(int,int);
double getRandomFloat(double,double);
int floatComp(const void*, const void*);
void getStageTime(TPilote*,int,char*);
void sharedMem(int,TPilote*,int);


