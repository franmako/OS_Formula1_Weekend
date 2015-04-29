#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h> /* Pour l'utilisation de fmod pour le calcul des modulo pour flaot */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define ERROR -1
#define NBTOURS 5
#define NBSECTORS 3
#define SEC_MIN 30.0
#define SEC_MAX 40.0
#define SHM_WRITE 2
#define SHM_SIZE 1024  /* make it a 1K shared memory segment */

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
void getTotalTime(double*);
double getSectorTime(double,double);
void getTempsTour(Lap);
void sharedMemWrite();

