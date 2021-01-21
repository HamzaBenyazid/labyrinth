#include"Affichage_SDL.h"

int cotes[3]={32,16,8}; //cote d'une cellule de labyrinthe
char* sols[3]={"images/sol32.bmp","images/sol16.bmp","images/sol08.bmp"};
char* objets[3]={"images/yellowball32.png","images/yellowball16.png","images/yellowball08.png"};
char* trophies[3]={"images/Trophy32.png","images/Trophy16.png","images/Trophy08.png"};
int choix;
int continuer = 1;

int SDL_main()
{
    SDL_Surface *ecran;
    SDL_Rect position = {0,0};
    SDL_Surface *background = IMG_Load("images/background.jpg");
    SDL_Init(SDL_INIT_VIDEO);
    
    N = 15;
    M = 25;

    ecran = SDL_SetVideoMode(1390, 847, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_BlitSurface(background,NULL,ecran,&position);

    choix=MOYEN;

    if( Menu(ecran) == 1 )
        play(ecran);

    SDL_Quit();

    return EXIT_SUCCESS;
}

SDL_Surface* create_surface(matriceDesCell labyrinthe)
{
    int size_ligne=N*2+(N+1);
    int size_colonne=M*2+(M+1);

    char* m=matrix2show(labyrinthe);

    SDL_Surface *maze=NULL,*wall=NULL;

    SDL_Rect position;

    int cote=cotes[choix];

    maze = SDL_CreateRGBSurface(SDL_HWSURFACE,size_colonne*cote,size_ligne*cote, 32, 0, 0, 0, 0);

    SDL_FillRect(maze, NULL, SDL_MapRGB(maze->format, 255, 255, 255));

    wall=IMG_Load(sols[choix]);

    for(int i=0;i<size_ligne;i++){
        for(int j=0;j<size_colonne;j++){
            if (*(m+i*size_colonne+j)=='#'){
                position.x=cote*j;
                position.y=cote*i;
                SDL_BlitSurface(wall,NULL,maze,&position);
            }
        }
    }
    free(m);
    return maze;
}
SDL_Surface* SDL_Solution(matriceDesCell m, SDL_Surface* maze,int entre[2], int sortie[2])
{
    SDL_Surface* careau = NULL;
    SDL_Surface* rectangle_horiz = NULL;
    SDL_Surface* rectangle_verti = NULL;
    SDL_Rect position, position_rectangle;
    int cote=cotes[choix];
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
void interact(SDL_Surface *ecran,SDL_Surface *original_maze, SDL_Surface *solved_maze,matriceDesCell labyrinth ,int entre[2],int sortie[2])
{
    int size_ligne=N*2+(N+1);
    int size_colonne=M*2+(M+1);
    
    //Les surfaces utilisees
    SDL_Surface *maze = original_maze;
    SDL_Surface *maze_copy= NULL;
    SDL_Surface *objet=IMG_Load(objets[choix]);
    SDL_Surface *trophy=IMG_Load(trophies[choix]);
    int cote=cotes[choix];

    //les variables utilisees
    int solved = 0;
    int ligne=(3*entre[0])+1,colonne=(3*entre[1])+1;
    int current_position[2]={entre[0],entre[1]};
    char *matrice=matrix2show(labyrinth);

    //les positions utilisees
    SDL_Rect positionObjet={ colonne*cote , ligne*cote };
    SDL_Rect positionMaze={ (ecran->w-maze->w)/2 , (ecran->h-maze->h)/2  }; //le centre de l'ecran
    SDL_Rect positionTrophy={ (3*sortie[1]+1)*cote , (3*sortie[0]+1)*cote };

    //event 
    SDL_Event event;
    

    SDL_EnableKeyRepeat(30, 30);
    SDL_BlitSurface(trophy,NULL,original_maze,&positionTrophy);
    SDL_BlitSurface(trophy,NULL,solved_maze,&positionTrophy);
    SDL_BlitSurface(trophy,NULL,original_maze,&positionTrophy);
    maze_copy=SDL_ConvertSurface(maze,maze->format,SDL_HWSURFACE);
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
                
                current_position[0]= positionObjet.y/cote/3 ;
                current_position[1]= positionObjet.x/cote/3 ;
                SDL_FreeSurface(solved_maze);
                solved_maze = SDL_ConvertSurface(original_maze,original_maze->format,SDL_HWSURFACE);
                SDL_Solution(labyrinth,solved_maze,current_position,sortie);
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
void play(SDL_Surface *ecran)
{
    SDL_Surface *maze,*solved_maze;

    SDL_Rect position;

    matriceDesCell labyrinth;

    int i;
    int entre[2] = {0} ;
    int sortie[2][2] = {0} ;
    char* m = NULL;

    while(continuer)
    {
        labyrinth = generate_maze();
        maze=create_surface(labyrinth);
        entre[0] = rand()%N;
        entre[1] = rand()%M;
        i = 0;
        while(i < 2)
        { 
            maze=create_surface(labyrinth);
            SDL_FreeSurface(solved_maze);
            solved_maze = SDL_ConvertSurface(maze,maze->format,SDL_HWSURFACE);
            sortie[i][0] = rand()%N;
            sortie[i][1] = rand()%M;
            if( i == 1 && sortie[0][0] == sortie[1][0] && sortie[0][1] == sortie[1][1] )
                continue;
            SDL_Solution(labyrinth,solved_maze,entre,sortie[i]);

            //centrer la labyrinthe
            position.x=(ecran->w-maze->w)/2;
            position.y=(ecran->h-maze->h)/2;


            SDL_BlitSurface(maze,NULL,ecran,&position);
            SDL_Flip(ecran);

            interact(ecran,maze,solved_maze,labyrinth,entre,sortie[i]);
            SDL_FreeSurface(solved_maze);
            SDL_FreeSurface(maze);
            i++;
        }
        free(m);
        free(labyrinth);
    }
}

int Menu(SDL_Surface *ecran)
{
    SDL_Surface* menu = NULL;
    SDL_Surface* start = NULL;
    SDL_Surface* controls = NULL;
    SDL_Surface* quit = NULL;
    SDL_Surface *background = IMG_Load("images/background.jpg");
    SDL_Event event;
    SDL_Rect position_start, position_controls, position_quit;
    SDL_Rect position_menu = {0,0};

    menu = SDL_CreateRGBSurface(SDL_HWSURFACE,ecran->w,ecran->h,32,0,0,0,0);

    start = IMG_Load("images/start.png");
    
    controls = IMG_Load("images/controls.png"); 

    quit = IMG_Load("images/quit.png");

    SDL_BlitSurface(background,NULL,menu,&position_menu);

    position_start.x = ( ecran->w - start->w )/2;
    position_start.y = 3.5*( ecran->h - start->h )/8;
    SDL_BlitSurface(start,NULL,menu,&position_start);

    position_controls.x = ( ecran->w - controls->w )/2;
    position_controls.y = 5.5*( ecran->h - controls->h )/8;
    SDL_BlitSurface(controls,NULL,menu,&position_controls);

    position_quit.x = ( ecran->w - quit->w )/2;
    position_quit.y = 7.5*( ecran->h - quit->h )/8;
    SDL_BlitSurface(quit,NULL,menu,&position_quit);
    
    
    SDL_BlitSurface(menu,NULL,ecran,&position_menu);
    SDL_Flip(ecran);

    while(continuer)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                    continuer = 0;
                    break;    
            case SDL_MOUSEBUTTONUP :
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    if( event.button.x >= position_start.x && event.button.x <= position_start.x + start->w && event.button.y >= position_start.y && event.button.y <= position_start.y + start->h  )
                    {
                        SDL_BlitSurface(background,NULL,ecran,&position_menu);
                        return 1;
                    }
                    else if( event.button.x >= position_controls.x && event.button.x <= position_controls.x + controls->w && event.button.y >= position_controls.y && event.button.y <= position_controls.y + controls->h  )
                    {
                        return 2;
                    }
                    else if( event.button.x >= position_quit.x && event.button.x <= position_quit.x + quit->w && event.button.y >= position_quit.y && event.button.y <= position_quit.y + quit->h  )
                    {
                        continuer = 0;
                    }
                    break;
                }
                break;
        }
    }
    SDL_FreeSurface(menu);
    SDL_FreeSurface(start);
    return 0;


}