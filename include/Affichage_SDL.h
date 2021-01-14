#ifndef AFF_SDL
#define AFF_SDL


#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<maze_generator.h>
<<<<<<< HEAD
#include"maze_solver.h"

SDL_Surface* create_surface(char* m);
int SDL_main(matriceDesCell labyrinth,char* m);
=======
#include<maze_solver.h>

SDL_Surface* create_surface(char* m);
SDL_Surface* SDL_Solution(matriceDesCell m, SDL_Surface* maze,int entre[2], int sortie[2]);
int SDL_main(matriceDesCell labyrinth, char* m);
>>>>>>> 30bc74f14749de84cf93ea0ec7bb59b37dc680db
void pause();

#endif