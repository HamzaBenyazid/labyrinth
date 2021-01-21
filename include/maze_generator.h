#ifndef MAZE
#define MAZE

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"stack.h"

int N  ;
int M  ;



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