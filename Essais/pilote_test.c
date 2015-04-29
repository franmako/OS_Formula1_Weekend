#include "pilote.h"

int main(){
    srand(time(NULL));
    int i,j;Lap tour;Race course;

   for(i=0;i<NBTOURS;i++){
    printf("|--------------|\n");
    printf("|*** Tour %d ***|\n",i+1);
    printf("|--------------|\n");
        for(j=0;j<NBSECTORS;j++){
            tour.tbSectorTime[j]= getSectorTime(SEC_MIN,SEC_MAX);
            //sleep(tour.tbSectorTime[j]);
            printf("Temps du secteur %d : %2.3f secondes\n",j+1,tour.tbSectorTime[j]);
            sharedMemWrite(tour.tbSectorTime[j]);
            //tour.lapTimeS += tour.tbSectorTime[j];
        }
        //getTempsTour(tour);
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
double getSectorTime(double a, double b) {
    double random,diff,r;
    static double sectorTime;

    random = ((double) rand()) / (double) RAND_MAX;
    diff = b - a;
    r = random * diff;
    sectorTime= a+r;

    return (sectorTime);
}

void sharedMemWrite(double sectorTime){
    key_t key;
    int shmid;
    void* data;
    int mode= SHM_WRITE;
    double test= sectorTime;

    if (mode > SHM_WRITE) {
        fprintf(stderr, "usage: shmdemo [data_to_write]\n");
        exit(1);
    }

    /* make the key: */
    if ((key = ftok("shared_memory", 'R')) == ERROR) {
        perror("ftok");
        exit(1);
    }

    /* connect to (and possibly create) the segment: */
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == ERROR) {
        perror("shmget");
        exit(1);
    }

    /* attach to the segment to get a pointer to it: */
    data = shmat(shmid, (void*)0, 0);
    if (data == (void*)(ERROR)) {
        perror("shmat");
        exit(1);
    }

    /* read or modify the segment, based on the command line: */
    if (mode == SHM_WRITE) {
        printf("Ecriture dans le segment: \"%2.3f\"\n", test);
        memcpy(data, &test, SHM_SIZE);
    } else
        printf("Le segment contiens: \"%2.3f\"\n", *(double*)data);

    /* detach from the segment: */
    if (shmdt(data) == ERROR) {
        perror("shmdt");
        exit(1);
    }
}
