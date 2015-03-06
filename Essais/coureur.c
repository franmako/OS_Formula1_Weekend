#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int sectorTime=0,totalTime=0,min,hr,i;
    srand(time(NULL));

    for(i=0;i<3;i++){
    sectorTime= ((rand()%11)+30); //rand()% x + n | n = min et n +(x-1) = max.
	//sleep(sectorTime);//Attends le nb de secondes du random avant d'afficher le temps
        printf("Temps du secteur %d : %d\n",i,sectorTime);
	totalTime += sectorTime;//Affiche le temps total après chaque secteur
	if(totalTime >= 60){
        min= totalTime/60;
        hr= min/60;
        printf("Temps total= %d heure(s) %d mins %d s\n",hr,min,sectorTime);
	}else
        printf("Temps total= %d\n",totalTime);
    }
    return 0;
}
