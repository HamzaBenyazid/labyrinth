#ifndef AFF_SDL
#define AFF_SDL


#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<maze_generator.h>
#include<Affichage.h>
#include"maze_solver.h"

#define FACILE 0
#define MOYEN 1
#define DIFFICILE 2

SDL_Surface* create_surface(matriceDesCell labyrithe);
int SDL_main(/*matriceDesCell labyrinth,char* m*/);
void interact(int* continuer,SDL_Surface *ecran,SDL_Surface *original_maze, SDL_Surface *solved_maze,matriceDesCell labyrinth,int entre[2],int sortie[2]);

#endif