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
            //sleep(tour.tbSectorTime[j]);
            printf("Temps du secteur %d : %2.3f secondes\n",j+1,tour.tbSectorTime[j]);
            tour.lapTimeS += tour.tbSectorTime[j];
        }
        getTempsTour(tour);
    }

    return 0;
}

void getTempsTour(Lap tour){
    (tour.lapTimeF.minutes)= (tour.lapTimeS/60);
    (tour.lapTimeF.secondes)= fmod(tour.lapTimeS,60.0);
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




