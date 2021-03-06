#include"Affichage_SDL.h"

int cotes[3]={32,16,8}; //cote d'une cellule de labyrinthe
char* sols[3]={"images/sol32.bmp","images/sol16.bmp","images/sol08.bmp"};
char* objets[3]={"images/yellowball32.png","images/yellowball16.png","images/yellowball08.png"};
char* trophies[3]={"images/Trophy32.png","images/Trophy16.png","images/Trophy08.png"};
int choix; //cette variable désigne la difficulté choisi
int continuer = 1; //cette variable désigne si le programme s'arrete ou continue

int SDL_main()
{
    SDL_Surface *ecran;
    SDL_Rect position = {0,0};
    SDL_Surface *background = IMG_Load("images/background.png");
    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("images/icon.jpg"), NULL);
    ecran = SDL_SetVideoMode(1200, 701, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Labyrinthe", NULL);
    SDL_BlitSurface(background,NULL,ecran,&position);
    
    while (continuer){
        switch(menu1(ecran)){//le menu 1 est afficher et la fonction retourne un int selon le bouton que l'utilisateur a cliqué
            case 1: switch(choix=menu2(ecran)) // le menu 2 est afficher qui contient les diffucltés
                {
                    case FACILE :
                        N=5;
                        M=10;
                        play(ecran);
                        break;
                    case MOYEN :
                        N=14;
                        M=24;
                        play(ecran);
                        break;
                    case DIFFICILE :
                        N=25;
                        M=40;
                        play(ecran);
                        break;
                    break;
                }
                break;
        }
    }
    SDL_FreeSurface(background);
    SDL_Quit();

    return EXIT_SUCCESS;
}

//cette fonction retourne la surface contenant le labyrinthe tracé
SDL_Surface* create_surface(matriceDesCell labyrinthe)
{
    int size_ligne=N*2+(N+1); 
    int size_colonne=M*2+(M+1);

    char* m=matrix2show(labyrinthe);

    SDL_Surface *maze=NULL,*wall=NULL;

    SDL_Rect position;

    int cote=cotes[choix]; // cette variable désigne le nombre de pixels avec lequel on va travailler (une cellule contient (2*cote * 2*cote) pixels)

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
    SDL_FreeSurface(wall);
    free(m);
    
    return maze;
}

// cette fonction fait colorer le chemin de resolution dans la surface du labyrinthe 
void SDL_Solution(matriceDesCell m, SDL_Surface* maze,int entre[2], int sortie[2])
{
    SDL_Surface* careau = NULL; // cette variable pour colorer chaque cellule qui appartient au chemin de solution
    SDL_Surface* rectangle_horiz = NULL; //cette variable et la variable suivante sont utile pour colorer l'espace entre deux cellules qui est normalement un mur ou un vide 
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


    while( path != NULL ) // tant qu'on n'a pas colorer tous les cellules de l'entrée vers la sortie
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
    
    SDL_FreeSurface(careau);
    SDL_FreeSurface(rectangle_horiz);
    SDL_FreeSurface(rectangle_verti);
    free_stack(path);

}

// cette fonction est la fonction qui affiche le labyrinthe et nous donne la possibité de déplacer l'objer jusqu'on arrive à la sortie 
int interact(SDL_Surface *ecran,SDL_Surface *original_maze,matriceDesCell labyrinth ,int entre[2],int sortie[2])
{

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
    
    // affichage du labyrinthe avec l'objet et le trophy dans la sortie
    SDL_EnableKeyRepeat(30, 30);
    maze_copy=SDL_ConvertSurface(maze,maze->format,SDL_HWSURFACE);
    SDL_BlitSurface(objet,NULL,maze_copy,&positionObjet);
    SDL_BlitSurface(trophy,NULL,maze_copy,&positionTrophy);
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
                    case SDLK_ESCAPE:
                        SDL_FreeSurface(maze_copy);
                        SDL_FreeSurface(objet);
                        SDL_FreeSurface(trophy);
                        free(matrice);
                        return 0;
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
                    case SDLK_SPACE: // si l'utilisateur clique sur espace le labyrinthe qui s'afficher doit être résolue si il clique une fois on retourne au labyrinthe original
                        SDL_EnableKeyRepeat(0, 30);
                        if(solved == 0)
                            solved = 1;
                        else
                            solved = 0;
                        SDL_EnableKeyRepeat(30, 30);
                }
                
                current_position[0]= positionObjet.y/cote/3 ;
                current_position[1]= positionObjet.x/cote/3 ;
                
                SDL_FreeSurface(maze_copy);
                maze_copy= SDL_ConvertSurface(maze,maze->format,SDL_HWSURFACE);

                //si solved = 1 alors on on met a jour le labyrinthe avec le résolution selon la position courante de l'objet
                if(solved)
                    SDL_Solution(labyrinth,maze_copy,current_position,sortie);
                
                SDL_BlitSurface(objet,NULL,maze_copy,&positionObjet);
                SDL_BlitSurface(trophy,NULL,maze_copy,&positionTrophy);
                SDL_BlitSurface(maze_copy,NULL,ecran,&positionMaze);
                SDL_Flip(ecran);
                break;
        }

        //ici si on arrive à la position de sortie on sort de la fonction
        if(positionTrophy.x == positionObjet.x && positionTrophy.y == positionObjet.y)
        {
            SDL_FreeSurface(maze_copy);
            SDL_FreeSurface(objet);
            SDL_FreeSurface(trophy);
            free(matrice);
            return 1;
        }
    }
}

//cette fonction permet d'afficher le jeu après que l'utilisateur clique sur le bouton "play"
void play(SDL_Surface *ecran)
{
    SDL_Surface *maze ;
    stack* solved_maze = NULL;
    matriceDesCell labyrinth;

    int i;
    int entre[2] ;
    int sortie[2][2] ;

    while(continuer)
    {
        // on genere à chaque fois un nouveau labyrinthe 
        labyrinth = generate_maze();
        maze=create_surface(labyrinth);

        //les position d'entre sont générere aléatoirement
        entre[0] = rand()%N; 
        entre[1] = rand()%M;
        
        // cette boucle va permettre d'afficher un labyrinthe et pour sortir in faut le résoudre avec la premier sortie et la deuxième sortie
        i = 0;
        while(i < 2)
        { 
            /*ici on assure que la deuxième position de sortie est différente de la première et que le labyrinthe à résoudre n'est pas 
              évident c'est pour cela on a mis la condition de lenght(solve_maze < (N+M)) */
            do
            {
                free_stack(solved_maze);
                sortie[i][0] = rand()%N;
                sortie[i][1] = rand()%M;
                solved_maze = solveMaze(labyrinth,entre,sortie[i]);

            } while ( length(solved_maze) < N+M || i*(sortie[0][0] == sortie[1][0] && sortie[0][1] == sortie[1][1]) );
            
            // interace retourne 0 lorsqu'on clique sur ESCAPE dans ce cas on sort de fonction play et on retourne au menu principale
            if (interact(ecran,maze,labyrinth,entre,sortie[i])==0){
                SDL_FreeSurface(maze);
                free(labyrinth);
                return;
            }
            i++;
        }
        SDL_FreeSurface(maze);
        free(labyrinth);
    }
}

//cette fonction afficher le menu principale qui s'affiche au début
int menu1(SDL_Surface *ecran)
{
    SDL_Surface* menu = NULL;
    SDL_Surface* start = NULL;
    SDL_Surface* quit = NULL;
    SDL_Surface* title = NULL;
    SDL_Surface *background = IMG_Load("images/background.png");
    SDL_Event event;
    SDL_Rect position_start, position_quit, position_title;
    SDL_Rect position_menu = {0,0};

    menu = SDL_CreateRGBSurface(SDL_HWSURFACE,ecran->w,ecran->h,32,0,0,0,0);

    title = IMG_Load("images/labyrinthe.png");

    start = IMG_Load("images/start.png");

    quit = IMG_Load("images/quit.png");

    SDL_BlitSurface(background,NULL,menu,&position_menu);

    position_title.x = ( ecran->w - title->w )/2;
    position_title.y = ( ecran->h - title->h )/8;
    SDL_BlitSurface(title,NULL,menu,&position_title);

    
    position_start.x = ( ecran->w - start->w )/2;
    position_start.y = 4*( ecran->h - start->h )/8;
    SDL_BlitSurface(start,NULL,menu,&position_start);


    position_quit.x = ( ecran->w - quit->w )/2;
    position_quit.y = 6*( ecran->h - quit->h )/8;
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
    SDL_FreeSurface(background);
    
    return 0;
}

//cette fonction afficher le menu qui donne à l'utilisateur la possibilité de choisir un niveau de difficulté
int menu2(SDL_Surface *ecran)
{
    SDL_Surface* menu = NULL;
    SDL_Surface* facile = NULL;
    SDL_Surface* moyen = NULL;
    SDL_Surface* difficile = NULL;
    SDL_Surface *background = NULL;
    SDL_Event event;
    SDL_Rect position_facile, position_moyen, position_difficile;
    SDL_Rect position_menu = {0,0};

    menu = SDL_CreateRGBSurface(SDL_HWSURFACE,ecran->w,ecran->h,32,0,0,0,0);

    background = IMG_Load("images/background.png");

    facile = IMG_Load("images/facile.png");
    
    moyen = IMG_Load("images/moyen.png"); 

    difficile = IMG_Load("images/difficile.png");

    SDL_BlitSurface(background,NULL,menu,&position_menu);

    position_facile.x = ( ecran->w - facile->w )/2;
    position_facile.y = 2*( ecran->h - facile->h )/8;
    SDL_BlitSurface(facile,NULL,menu,&position_facile);

    position_moyen.x = ( ecran->w - moyen->w )/2;
    position_moyen.y = 4*( ecran->h - moyen->h )/8;
    SDL_BlitSurface(moyen,NULL,menu,&position_moyen);

    position_difficile.x = ( ecran->w - difficile->w )/2;
    position_difficile.y = 6*( ecran->h - difficile->h )/8;
    SDL_BlitSurface(difficile,NULL,menu,&position_difficile);

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
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    return ESCAPE;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONUP :
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    if( event.button.x >= position_facile.x && event.button.x <= position_facile.x + facile->w && event.button.y >= position_facile.y && event.button.y <= position_facile.y + facile->h  )
                    {
                        SDL_BlitSurface(background,NULL,ecran,&position_menu);
                        return FACILE;
                    }
                    else if( event.button.x >= position_moyen.x && event.button.x <= position_moyen.x + moyen->w && event.button.y >= position_moyen.y && event.button.y <= position_moyen.y + moyen->h  )
                    {
                        SDL_BlitSurface(background,NULL,ecran,&position_menu);
                        return MOYEN;
                    }
                    else if( event.button.x >= position_difficile.x && event.button.x <= position_difficile.x + difficile->w && event.button.y >= position_difficile.y && event.button.y <= position_difficile.y + difficile->h  )
                    {
                        SDL_BlitSurface(background,NULL,ecran,&position_menu);
                        return DIFFICILE;
                    }
                    break;
                }
                break;
                
        }
    }
    SDL_FreeSurface(menu);
    SDL_FreeSurface(facile);
    SDL_FreeSurface(moyen);
    SDL_FreeSurface(difficile);
    SDL_FreeSurface(background);
    return 0;

}
