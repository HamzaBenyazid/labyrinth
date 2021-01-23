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
#define ESCAPE -1

int SDL_main();
SDL_Surface* create_surface(matriceDesCell labyrithe);
SDL_Surface* SDL_Solution(matriceDesCell m, SDL_Surface* maze,int entre[2], int sortie[2]);
int interact(SDL_Surface *ecran,SDL_Surface *original_maze, matriceDesCell labyrinth,int entre[2],int sortie[2]);
void play(SDL_Surface* ecran);
int menu1(SDL_Surface* ecran);
int menu2(SDL_Surface *ecran);

#endif