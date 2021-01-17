#ifndef AFF_SDL
#define AFF_SDL


#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<maze_generator.h>
#include<Affichage.h>
#include"maze_solver.h"

SDL_Surface* create_surface(char* m);
int SDL_main(/*matriceDesCell labyrinth,char* m*/);
void play(int* continuer,SDL_Surface *ecran,SDL_Surface *original_maze, SDL_Surface *solved_maze,matriceDesCell labyrinth,char *matrice,int entre[2],int sortie[2]);

#endif