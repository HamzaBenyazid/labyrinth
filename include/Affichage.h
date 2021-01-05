#ifndef AFF
#define AFF

#include<stdio.h>
#include<stdlib.h>
#include"maze_generator.h"

char* matrix2show(matriceDesCell m);
void affichage(char* matrix_2_show);
void fill(cell* m,int i,int j,int up, int right, int down, int left);


#endif