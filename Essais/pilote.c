#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "pilote.h"
#define NBTOURS 5
#define NBSECTORS 3

/*typedef struct{
    int[NBTOURS] tempsTours;
}Course*/

int main(){
    int i,j,*sectorTime;
    srand(time(NULL));
    for(i=0;i<NBTOURS;i++){
        printf("|--------------|\n");
        printf("|*** Tour %d ***|\n",i+1);
        printf("|--------------|\n");
        sectorTime= getTempsSecteur();
        //getTempsTour(totalLapTime);
        for(j=0;j<NBSECTORS;j++)
            printf("Temps du secteur %d : %d secondes\n",j+1,*(sectorTime+j));
    }
    return(0);
}
int* getTempsSecteur(){
    int i,totalLapTime;
    static int sectorTime[2];
    for(i=0;i<3;i++){
        sectorTime[i]= ((rand()%11)+30); //rand()% x + n | n = min et n +(x-1) = max.
        //sleep(sectorTime);//Attends le nb de secondes du random avant d'afficher le temps
        totalLapTime += sectorTime[i];//Calcule le temps total après chaque tour
    }
    return(sectorTime);
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




