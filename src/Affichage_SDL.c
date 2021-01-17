#include"Affichage_SDL.h"

int cote=16; //cote d'une cellule de labyrinthe

SDL_Surface* create_surface(char* m)
{

    SDL_Surface *maze=NULL,*wall=NULL;

    SDL_Rect position;

    maze = SDL_CreateRGBSurface(SDL_HWSURFACE,size_colonne*cote,size_ligne*cote, 32, 0, 0, 0, 0);

    SDL_FillRect(maze, NULL, SDL_MapRGB(maze->format, 255, 255, 255));

    wall=IMG_Load("images/sol16.bmp");

    for(int i=0;i<size_ligne;i++){
        for(int j=0;j<size_colonne;j++){
            if (*(m+i*size_colonne+j)=='#'){
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

int SDL_main(/*matriceDesCell labyrinth,char* m*/)
{

    SDL_Surface *ecran,*maze,*solved_maze;

    SDL_Rect position;

    int continuer = 1;
    int i;
    matriceDesCell labyrinth;
    char* m = NULL;

    ecran=SDL_SetVideoMode(size_colonne*cote, size_ligne*cote, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

    if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    int entre[2] = {0} ;
    int entre_copy[2] = {0};
    int sortie[2][2] = {0} ;

    position.x=position.y=0;
    while(continuer)
    {
        labyrinth = generate_maze();
        m = matrix2show(labyrinth);
        maze=create_surface(m);
        solved_maze = SDL_ConvertSurface(maze,maze->format,SDL_HWSURFACE);
        entre[0] = rand()%N;
        entre[1] = rand()%M;
        i = 0;
        while(i < 2)
        { 
            m = matrix2show(labyrinth);
            maze=create_surface(m);
            solved_maze = SDL_ConvertSurface(maze,maze->format,SDL_HWSURFACE);
            sortie[i][0] = rand()%N;
            sortie[i][1] = rand()%M;
            if( i == 1 && sortie[0] == sortie[1] )
                continue;
            SDL_Solution(labyrinth,solved_maze,entre,sortie);
            SDL_BlitSurface(maze,NULL,ecran,&position);
            SDL_Flip(ecran);

            entre_copy[0] = entre[0] ;
            entre_copy[1] = entre[1] ;
            play(&continuer,ecran,maze,solved_maze,labyrinth,m,entre_copy,sortie[i]);
            SDL_FreeSurface(solved_maze);
            SDL_FreeSurface(maze);
            free(m);
            i++;
        }
        
        
        free(labyrinth);
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}


void play(int* continuer,SDL_Surface *ecran,SDL_Surface *original_maze, SDL_Surface *solved_maze,matriceDesCell labyrinth ,char *matrice,int entre[2],int sortie[2])
{
    SDL_Surface *maze = original_maze;
    int solved = 0;
    SDL_Surface *maze_copy= NULL;
    //int continuer = 1;
    SDL_Event event;

    SDL_Rect positionObjet,positionMaze={positionMaze.x=0,positionMaze.y=0},positionTrophy;
    SDL_Surface *objet=IMG_Load("images/yellowball16.png");
    SDL_Surface *trophy=IMG_Load("images/Trophy16.png");
    SDL_EnableKeyRepeat(30, 30);
    int ligne=(3*entre[0])+1,colonne=(3*entre[1])+1;
    
    positionTrophy.y = ((3*sortie[0])+1)*cote;
    positionTrophy.x = ((3*sortie[1])+1)*cote;
    SDL_BlitSurface(trophy,NULL,original_maze,&positionTrophy);
    SDL_BlitSurface(trophy,NULL,solved_maze,&positionTrophy);
    maze_copy= SDL_ConvertSurface(maze,maze->format,SDL_HWSURFACE);

    positionObjet.x = colonne*cote ;
    positionObjet.y = ligne*cote ;

    SDL_BlitSurface(objet,NULL,maze_copy,&positionObjet);
    SDL_BlitSurface(maze_copy,NULL,ecran,&positionMaze);
    SDL_Flip(ecran);
    while (*continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                *continuer = 0;
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
                    case SDLK_SPACE:
                        SDL_EnableKeyRepeat(0, 30);
                        if(solved == 0)
                        {
                            maze = solved_maze;
                            solved = 1;
                        }
                        else
                        {
                            maze = original_maze;
                            solved = 0;
                        }
                        SDL_EnableKeyRepeat(30, 30);
                }
                
                entre[0] = positionObjet.y/cote/3 ;
                entre[1] = positionObjet.x/cote/3 ;
                SDL_FreeSurface(solved_maze);
                solved_maze = SDL_ConvertSurface(original_maze,original_maze->format,SDL_HWSURFACE);
                SDL_Solution(labyrinth,solved_maze,entre,sortie);
                SDL_BlitSurface(trophy,NULL,solved_maze,&positionTrophy);

                SDL_FreeSurface(maze_copy);
                maze_copy= SDL_ConvertSurface(maze,maze->format,SDL_HWSURFACE);
                SDL_BlitSurface(objet,NULL,maze_copy,&positionObjet);
                SDL_BlitSurface(maze_copy,NULL,ecran,&positionMaze);
                SDL_Flip(ecran);
                break;
        }
        if(positionTrophy.x == positionObjet.x && positionTrophy.y == positionObjet.y)
            break;
    }
}
