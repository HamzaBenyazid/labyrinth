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
                position.y=32*i;
                position.x=32*j;
                SDL_BlitSurface(wall,NULL,maze,&position);
            }
        }
    }

    return maze;
}

SDL_Surface* SDL_Solution(matriceDesCell m, SDL_Surface* maze,int entre[2], int sortie[2])
{
    SDL_Surface* careau = NULL;
    SDL_Surface* rectangle_horiz = NULL;
    SDL_Surface* rectangle_verti = NULL;
    SDL_Rect position, position_rectangle;
    
    stack* path = solveMaze(m, entre, sortie);
    
    
    careau = SDL_CreateRGBSurface(SDL_HWSURFACE, 32*2, 32*2, 32, 0, 0, 0, 0);
    rectangle_horiz = SDL_CreateRGBSurface(SDL_HWSURFACE, 32*2, 32, 32, 0, 0, 0, 0);
    rectangle_verti = SDL_CreateRGBSurface(SDL_HWSURFACE, 32, 32*2, 32, 0, 0, 0, 0);

    SDL_FillRect(careau, NULL, SDL_MapRGB(careau->format, 0, 255, 0)); 
    SDL_FillRect(rectangle_verti, NULL, SDL_MapRGB(rectangle_verti->format, 0, 255, 0)); 
    SDL_FillRect(rectangle_horiz, NULL, SDL_MapRGB(rectangle_horiz->format, 0, 255, 0)); 


    while( path != NULL )
    {
        position.x = (path->colonne)*2*32 + (path->colonne+1)*32;
        position.y = (path->ligne)*2*32 + (path->ligne+1)*32;
        if(path->suivant != NULL)
        {
            if(path->suivant->ligne == path->ligne)
            {    
                position_rectangle.y = position.y ;
                if(path->suivant->colonne > path->colonne)
                    position_rectangle.x = position.x + 32*2 ;
                else 
                    position_rectangle.x = position.x - 32 ;
                SDL_BlitSurface(rectangle_verti,NULL,maze,&position_rectangle);
            }
            else 
            {    
                position_rectangle.x = position.x ;
                if(path->suivant->ligne > path->ligne)
                    position_rectangle.y = position.y + 32*2 ;
                else 
                    position_rectangle.y = position.y - 32 ;
                SDL_BlitSurface(rectangle_horiz,NULL,maze,&position_rectangle);
            }
        }
        SDL_BlitSurface(careau,NULL,maze,&position);
        path = path->suivant ;

    }
    return maze;
}

int SDL_main(matriceDesCell labyrinth,char* m)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface *ecran,*maze,*solved_maze;

    SDL_Rect position;

    int entre[2] = {0,0};
    int sortie[2] = {N-1,N-1};

    ecran=SDL_SetVideoMode(size*32, size*32, 32, SDL_HWSURFACE);

    position.x=position.y=0;
    maze=create_surface(m);
    solved_maze = SDL_ConvertSurface(maze,maze->format,SDL_HWSURFACE);
    SDL_Solution(labyrinth,solved_maze,entre,sortie);
    SDL_BlitSurface(solved_maze,NULL,ecran,&position);
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