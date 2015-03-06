#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

main(){
    int sectorTime=0,totalTime=0,totalTimeMin,totalTimeSec,i;
    srand(time(NULL));

    for(i=0;i<3;i++){
    sectorTime= ((rand()%11)+30); //rand()% x + n | n = min et n +(x-1) = max.
	//sleep(sectorTime);//Attends le nb de secondes du random avant d'afficher le temps
    printf("Temps du secteur %d : %d\n",i+1,sectorTime);
    totalTime += sectorTime;//Calcule le temps total après chaque tour
    }
}
void tempsTour(int ){
    totalTimeMin= (totalTime/60);
	totalTimeSec= (totalTime%60);
    printf("Temps total pour le tour= %d minute(s) %d secondes \n",totalTimeMin,totalTimeSec);
}
