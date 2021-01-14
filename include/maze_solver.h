#ifndef MAZE_SOLVER
#define MAZE_SOLVER


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"maze_generator.h"
#include"stack.h"


int RandomPath_Sol(matriceDesCell m,int line,int col,int* visited);
stack* solveMaze(matriceDesCell m,int entre[2],int sortie[2]);



#endif