#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define NBTOURS 5
#define NBSECTORS 3
#define SEC_MIN 30.0
#define SEC_MAX 40.0

/* -- PROTOTYPES -- */

int *getTempsSecteur();
void getTotalTime(double*);
double *getRandomFloat(double,double,double*);
void getTempsTour(double*);
void getTempsCourse(double*);


