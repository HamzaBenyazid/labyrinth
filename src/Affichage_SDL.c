#include"Affichage_SDL.h"

int size=N*2+(N+1);

SDL_Surface* create_surface(char* m)
{
    SDL_Surface *maze,*wall=NULL;

    SDL_Rect position;

    

    maze = SDL_CreateRGBSurface(SDL_HWSURFACE,size*32,size*32, 32, 0, 0, 0, 0);

    SDL_FillRect(maze, NULL, SDL_MapRGB(maze->format, 255, 255, 255)); 

    wall=IMG_Load("sol.bmp");

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if (*(m+i*size+j)=='#'){
                position.x=32*i;
                position.y=32*j;
                SDL_BlitSurface(wall,NULL,maze,&position);
            }
        }
    }

    return maze;
}

int SDL_main(char* m)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface *ecran,*maze;

    SDL_Rect position;

    ecran=SDL_SetVideoMode(size*32, size*32, 32, SDL_HWSURFACE);

    position.x=position.y=0;
    maze=create_surface(m);
    SDL_BlitSurface(maze,NULL,ecran,&position);
    SDL_Flip(ecran);

    pause();


    SDL_FreeSurface(maze);
    SDL_Quit();
    return EXIT_SUCCESS;
}

void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}