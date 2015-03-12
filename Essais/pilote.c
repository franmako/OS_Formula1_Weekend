#include "pilote.h"

int main(){
    srand(time(NULL));
    int i,j;
    double *sectorTime;
    for(i=0;i<NBTOURS;i++){
        printf("|--------------|\n");
        printf("|*** Tour %d ***|\n",i+1);
        printf("|--------------|\n");
        sectorTime= getRandomFloat(SEC_MIN,SEC_MAX);
        //getTempsTour(totalLapTime);
        for(j=0;j<NBSECTORS;j++)
            printf("Temps du secteur %d : %2.2f secondes\n",j+1,*(sectorTime+j));
    }
    return(0);
}

void getTempsTour(int totalLapTime){
    int totalTimeMin,totalTimeSec;
    totalTimeMin= (totalLapTime/60);
	totalTimeSec= (totalLapTime%60);
	if(totalTimeMin != 0){
        printf("Temps total pour le tour= %d minute(s) %d secondes \n\n",totalTimeMin,totalTimeSec);
	}else{
	    printf("Temps total pour le tour= %d secondes \n\n",totalTimeSec);
	}
}

double *getRandomFloat(double a, double b) {
    double random,diff,r,totalLapTime;
    static double sectorTime[NBSECTORS];
    int i;
    for(i=0;i<NBSECTORS;i++){
        random = ((double) rand()) / (double) RAND_MAX;
        diff = b - a;
        r = random * diff;
        sectorTime[i]= a+r;
        totalLapTime += sectorTime[i];
    }
    return (sectorTime);
}




