#include "pilote.h"

int main(){
    srand(time(NULL));
    int i,j;
    double *sectorTime,*totalLapTime,*totalRaceTime;
    for(i=0;i<NBTOURS;i++){
        printf("|--------------|\n");
        printf("|*** Tour %d ***|\n",i+1);
        printf("|--------------|\n");
        sectorTime= getRandomFloat(SEC_MIN,SEC_MAX,totalLapTime);
        for(j=0;j<NBSECTORS;j++)
            printf("Temps du secteur %d : %2.3f secondes\n",j+1,*(sectorTime+j));
        getTempsTour(totalLapTime);
        //totalRaceTime += *totalLapTime;
        getTempsCourse(totalRaceTime);
    }
    return(0);
}

void getTempsTour(double *totalLapTime){
    double totalTimeSec;
    int totalTimeMin;
    totalTimeMin= (*totalLapTime/60);
	totalTimeSec= fmod(*totalLapTime,60.0);

	if(totalTimeMin != 0.0){
        printf("Temps total pour le tour= %d minute(s) %2.3f secondes \n\n",totalTimeMin,totalTimeSec);
	}else{
	    printf("Temps total pour le tour= %2.3f secondes \n\n",totalTimeSec);
	}
}

void getTempsCourse(double *totalRaceTime){
    double totalTimeSec;
    int totalTimeMin;
    totalTimeMin= (*totalRaceTime/60);
	totalTimeSec= fmod(*totalRaceTime,60.0);

	if(totalTimeMin != 0.0){
        printf("Temps total pour la course= %d minute(s) %2.3f secondes \n\n",totalTimeMin,totalTimeSec);
	}else{
	    printf("Temps total pour la course= %2.3f secondes \n\n",totalTimeSec);
	}
}

double *getRandomFloat(double a, double b,  double *lapTime) {
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
    *lapTime= totalLapTime;
    return (sectorTime);
}




