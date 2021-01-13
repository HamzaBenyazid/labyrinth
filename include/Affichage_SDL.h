#ifndef AFF_SDL
#define AFF_SDL


#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<maze_generator.h>
#include<maze_solver.h>

SDL_Surface* create_surface(char* m);
SDL_Surface* SDL_Solution(matriceDesCell m, SDL_Surface* maze,int entre[2], int sortie[2]);
int SDL_main(matriceDesCell labyrinth, char* m);
void pause();

#endif