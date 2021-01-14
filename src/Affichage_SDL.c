#include"Affichage_SDL.h"


int cote=8; //cote d'une cellule de labyrinthe

SDL_Surface* create_surface(char* m)
{
    int size_ligne=N*2+(N+1);
    int size_colone=M*2+(M+1);

    SDL_Surface *maze=NULL,*wall=NULL;

    SDL_Rect position;

    maze = SDL_CreateRGBSurface(SDL_HWSURFACE,size_colone*cote,size_ligne*cote, 32, 0, 0, 0, 0);

    SDL_FillRect(maze, NULL, SDL_MapRGB(maze->format, 255, 255, 255));

    wall=IMG_Load("sol08.bmp");

    for(int i=0;i<size_ligne;i++){
        for(int j=0;j<size_colone;j++){
            if (*(m+i*size_colone+j)=='#'){
                position.x=cote*j;
                position.y=cote*i;
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
    
    
    careau = SDL_CreateRGBSurface(SDL_HWSURFACE, cote*2, cote*2, 32, 0, 0, 0, 0);
    rectangle_horiz = SDL_CreateRGBSurface(SDL_HWSURFACE, cote*2, cote, 32, 0, 0, 0, 0);
    rectangle_verti = SDL_CreateRGBSurface(SDL_HWSURFACE, cote, cote*2, 32, 0, 0, 0, 0);

    SDL_FillRect(careau, NULL, SDL_MapRGB(careau->format, 0, 255, 0)); 
    SDL_FillRect(rectangle_verti, NULL, SDL_MapRGB(rectangle_verti->format, 0, 255, 0)); 
    SDL_FillRect(rectangle_horiz, NULL, SDL_MapRGB(rectangle_horiz->format, 0, 255, 0)); 


    while( path != NULL )
    {
        position.x = (path->colonne)*2*cote + (path->colonne+1)*cote;
        position.y = (path->ligne)*2*cote + (path->ligne+1)*cote;
        if(path->suivant != NULL)
        {
            if(path->suivant->ligne == path->ligne)
            {    
                position_rectangle.y = position.y ;
                if(path->suivant->colonne > path->colonne)
                    position_rectangle.x = position.x + cote*2 ;
                else 
                    position_rectangle.x = position.x - cote ;
                SDL_BlitSurface(rectangle_verti,NULL,maze,&position_rectangle);
            }
            else 
            {    
                position_rectangle.x = position.x ;
                if(path->suivant->ligne > path->ligne)
                    position_rectangle.y = position.y + cote*2 ;
                else 
                    position_rectangle.y = position.y - cote ;
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
    int size_ligne=N*2+(N+1);
    int size_colone=M*2+(M+1);

    SDL_Surface *ecran,*maze,*solved_maze;

    SDL_Rect position;

    int entre[2] = {1,1};
    int sortie[2] = {N-1,M-1};


    ecran=SDL_SetVideoMode(size_colone*cote, size_ligne*cote, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

    if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    position.x=position.y=0;
    maze=create_surface(m);
    solved_maze = SDL_ConvertSurface(maze,maze->format,SDL_HWSURFACE);
    //SDL_Solution(labyrinth,solved_maze,entre,sortie);
    SDL_BlitSurface(maze,NULL,ecran,&position);
    SDL_Flip(ecran);

    play(ecran,maze,m,entre,sortie);
    
    SDL_FreeSurface(maze);
    SDL_FreeSurface(solved_maze);
    SDL_Quit();
    return EXIT_SUCCESS;
}


void play(SDL_Surface *ecran,SDL_Surface *maze,char *matrice,int entre[2],int sortie[2])
{
    SDL_Surface *maze_copy= SDL_ConvertSurface(maze,maze->format,SDL_HWSURFACE);
    int size_ligne=N*2+(N+1);
    int size_colonne=M*2+(M+1);
    int continuer = 1;
    SDL_Event event;
    SDL_Rect positionObjet,positionMaze={positionMaze.x=0,positionMaze.y=0};
    int ligne=entre[0],colonne=entre[1];
    SDL_Surface *objet=IMG_Load("objet.png");

    SDL_EnableKeyRepeat(10, 30);
    

    positionObjet.x = (colonne-1)*2*cote + colonne*cote;
    positionObjet.y = (ligne-1)*2*cote + (ligne)*cote;
    SDL_BlitSurface(objet,NULL,maze_copy,&positionObjet);
    SDL_BlitSurface(maze_copy,NULL,ecran,&positionMaze);
    SDL_Flip(ecran);
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        if (*(matrice+(ligne-1)*size_colonne+colonne)!='#'&&*(matrice+(ligne-1)*size_colonne+colonne+1)!='#'){
                            positionObjet.y-=cote;
                            ligne--;
                        }break;
                    case SDLK_DOWN:
                        if (*(matrice+(ligne+2)*size_colonne+colonne)!='#'&&*(matrice+(ligne+2)*size_colonne+colonne+1)!='#'){
                            positionObjet.y+=cote;
                            ligne++;
                        }break;
                    case SDLK_RIGHT:
                        if (*(matrice+ligne*size_colonne+colonne+2)!='#'&& *(matrice+(ligne+1)*size_colonne+colonne+2)!='#'){
                            positionObjet.x+=cote;
                            colonne++;
                        }break;
                    case SDLK_LEFT:
                        if (*(matrice+ligne*size_colonne+colonne-1)!='#'&&*(matrice+(ligne+1)*size_colonne+colonne-1)!='#'){
                            positionObjet.x-=cote;
                            colonne--;
                        }break;
                }
                SDL_FreeSurface(maze_copy);
                maze_copy= SDL_ConvertSurface(maze,maze->format,SDL_HWSURFACE);
                SDL_BlitSurface(objet,NULL,maze_copy,&positionObjet);
                SDL_BlitSurface(maze_copy,NULL,ecran,&positionMaze);
                SDL_Flip(ecran);
                break;
        }
    }
}
