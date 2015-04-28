#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h> /* Pour l'utilisation de fmod pour le calcul des modulo pour flaot */

#define NBTOURS 5
#define NBSECTORS 3
#define SEC_MIN 30.0
#define SEC_MAX 40.0

/* -- STRUCTURES -- */
typedef struct{
    int minutes;
    double secondes;
}FTime;

typedef struct{
    double tbSectorTime[NBSECTORS];
    double lapTimeS;
    FTime lapTimeF;
}Lap;

typedef struct{
    Lap tbLap[NBTOURS];
    double totalTimeS;
    FTime totalTimeF;
}Race;

/* -- PROTOTYPES -- */

int *getTempsSecteur();
void getTotalTime(double*);
double getRandomFloat(double,double);
void getTempsTour(Lap);

