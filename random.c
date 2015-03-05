#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    int temps;
    int i;
    srand(time(NULL));

    for(i=0;i<3;i++){
    temps= ((rand()%20)+27); //rand()% x + n | n = min et n +(x-1) = max.
        printf("Secteur %d Temps: %d\n",i,temps);
    }
    return 0;
}
