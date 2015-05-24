# ProjetOS_Juin2015
Author: F. O. Makokha

|--- DESCRIPTION ---|
This is a C project that I had to program as part of my Operating System course, in my second year.
It simulates a Formula 1 Grand Prix Week-End for 16 racers. 
It generates the different times for each sector of each lap of the different stages (Practice, QUalification & Race).
Each racer is made with a fork() from a parent racer. They all share their times with the server using shared memory.

The server calculates the leaderboard and determines from the leaderboard the racers that qualify to the next qualification
stage.

|--- HOW TO EXECUTE ---|
1. Execute "pilote.c" in a terminal window: gcc -o pilote pilote.c -lm
2. Open a second terminal window and execute "serveur.c": gcc -o serveur serveur.c 

|--- GUIDE D'UTILISATION ---|
1. Lancer pilote dans le terminal: gcc -o pilote pilote.c -lm
2. Lancer serveur dans une autre fenêtre du terminal: gcc -o serveur serveur.c 

