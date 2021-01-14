#ifndef MAZE
#define MAZE

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"stack.h"

<<<<<<< HEAD
#define N 29
#define M 50



=======
#define N 10
>>>>>>> 30bc74f14749de84cf93ea0ec7bb59b37dc680db
enum direction{up,right,down,left};


typedef struct _cell
{
    int right;
    int left;
    int up;
    int down;
    
}cell;

typedef cell* matriceDesCell;
void init(matriceDesCell *m);
int randomPath(matriceDesCell m,int line,int col,int* visited);
matriceDesCell generate_maze();

#endif