#include "pilote.h"

int main(){
    srand(time(NULL));
    int i,j;Lap tour;Race course;

    for(i=0;i<NBTOURS;i++){
    printf("|--------------|\n");
    printf("|*** Tour %d ***|\n",i+1);
    printf("|--------------|\n");
        for(j=0;j<NBSECTORS;j++){
            tour.tbSectorTime[j]= getRandomFloat(SEC_MIN,SEC_MAX);
            sleep(tour.tbSectorTime[j]);
            printf("Temps du secteur %d : %2.3f secondes\n",j+1,tour.tbSectorTime[j]);
            tour.lapTimeS += tour.tbSectorTime[j];
        }
        tour.lapTimeF = getTempsTour(tour.lapTimeS)
    }

    return 0;
}
/*
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
            //sleep(*(sectorTime+j));
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
}*/

void getTempsTour(double lapTime){
    double timeSec;
    int timeMin;
    timeMin= (lapTime/60);
    timeSec= fmod(lapTime,60.0);

   /* if(timeMin != 0.0){
        printf("Temps tour= %d minute %2.3f secondes\n",timeMin,timeSec);
    }else{
        printf("Temps tour= %2.3f secondes\n",timeSec);
    }*/
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

double getRandomFloat(double a, double b) {
    double random,diff,r;
    static double sectorTime;

    random = ((double) rand()) / (double) RAND_MAX;
    diff = b - a;
    r = random * diff;
    sectorTime= a+r;

    return (sectorTime);
}




