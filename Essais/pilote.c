#include "pilote.h"

int main(){
    srand(time(NULL));
    int i,j,totalTimeMin;
    double *sectorTime,totalRaceTime,totalTimeSec;
    for(i=0;i<NBTOURS;i++){
        printf("|--------------|\n");
        printf("|*** Tour %d ***|\n",i+1);
        printf("|--------------|\n");
        sectorTime= getRandomFloat(SEC_MIN,SEC_MAX);
        for(j=0;j<NBSECTORS;j++){
            printf("Temps du secteur %d : %2.3f secondes\n",j+1,*(sectorTime+j));
            totalRaceTime += *sectorTime;
        }
        totalTimeMin= (totalRaceTime/60);
        totalTimeSec= fmod(totalRaceTime,60.0);

        if(totalTimeMin != 0){
            printf("Temps total pour la course= %d minute(s) %2.3f secondes \n\n",totalTimeMin,totalTimeSec);
        }else{
            printf("Temps total pour la course= %2.3f secondes \n\n",totalTimeSec);
        }
    }
    return(0);
}

void getTempsTour(double lapTime){
    double timeSec;
    int timeMin;
    timeMin= (lapTime/60);
    timeSec= fmod(lapTime,60.0);

    if(timeMin != 0.0){
        printf("Temps tour= %d minute %2.3f secondes\n",timeMin,timeSec);
    }else{
        printf("Temps tour= %2.3f secondes\n",timeSec);
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

double *getRandomFloat(double a, double b) {
    double random,diff,r,lapTime;
    static double sectorTime[NBSECTORS];
    int i;
    for(i=0;i<NBSECTORS;i++){
        random = ((double) rand()) / (double) RAND_MAX;
        diff = b - a;
        r = random * diff;
        sectorTime[i]= a+r;
        lapTime += sectorTime[i];
    }
    getTempsTour(lapTime);
    return (sectorTime);
}




