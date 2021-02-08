#include"maze_generator.h"

//cette fonction génére le labyrinthe sous forme d'une matrice de cellules
matriceDesCell generate_maze()
{
    stack* maze_stack=NULL;
    matriceDesCell maze = (cell*)malloc(N*M*sizeof(cell));
    int* visited = (int*)malloc(N*M*sizeof(int));
    int way;
    int i, j, count = 1;

    init(&maze);

    // Initialisé la matrice des cellules visitées
    for(i=0;i<N*M;i++)
    {
        *(visited+i) = 0;
    }

    // Ci-dessous l'algorithme de "Randomized DFS" 
    i = 0;
    j = 0;
    while(count < N*M) // tant qu'on n'a pas visité tous les cellules
    {
        way = randomPath(maze, i, j,visited); // on choisis  la cellule qu'on va visité(haute,droite...) aléatoirement 
        *(visited+i*M+j) = 1;
        //on affecte 1 au coté de la cellule où nous avons passez pour dire  qu'il n'a pas de mur dans ce coté
        switch(way)
        {
            case up : 
                    (maze+i*M+j)->up = 1;
                    (maze+(i-1)*M+j)->down = 1;
                    append(&maze_stack, i, j);
                    count++;
                    i--;
                    break;
            case down :
                    (maze+i*M+j)->down = 1;
                    (maze+(i+1)*M+j)->up = 1;
                    append(&maze_stack, i, j);
                    count++;
                    i++;
                    break;
            case right :
                    (maze+i*M+j)->right = 1;
                    (maze+i*M+(j+1))->left = 1;
                    append(&maze_stack, i, j);
                    count++;
                    j++;
                    break;
            case left :
                    (maze+i*M+j)->left = 1;
                    (maze+i*M+(j-1))->right = 1;
                    append(&maze_stack, i, j);
                    count++;
                    j--;
                    break;
            case -1 :
                    pop(&maze_stack);
                    i = *top(maze_stack);
                    j = *(top(maze_stack)+1);
                    break;
        }
    }
    free_stack(maze_stack);
    free(visited);
    return maze;
}


// cette fonction initialise les cotées des  cellules qui sont dans les bornes à -1 pour savoir qu'il un mur là-bas et les autres à 0
void init(matriceDesCell *m)
{
    int i=0;
    for (i=0;i<N*M;i++){
        (*m+i)->up=0;
        (*m+i)->down=0;
        (*m+i)->left=0;
        (*m+i)->right=0;
    }
    for (i=0;i<M;i++){
        (*m+i)->up=-1;
        (*m+i+N*M-M)->down=-1;
    }
    for (i=0;i<N;i++){
        (*m+i*M)->left=-1;
        (*m+M-1+i*M)->right=-1;
    }
}

// cette fonction retourne le coté (haut,droit,..) du cellule qu'on va visiter aléatoirement en assurant qu'elle  n'est pas encore visité
int randomPath(matriceDesCell m,int line,int col,int* visited)
{
    cell in=*(m+M*line+col);
    int tab[4];
    int count=0;
    if (in.up==0 &&*(visited+(line-1)*M+col)==0) {
        tab[count]=up;
        count++;
    }
    if (in.right==0 &&*(visited+line*M+col+1)==0) {
        tab[count]=right;
        count++;
    }
    if (in.down==0 &&*(visited+(line+1)*M+col)==0) {
        tab[count]=down;
        count++;
    }
    if (in.left==0 &&*(visited+line*M+col-1)==0) {
        tab[count]=left;
        count++;
    }
    if (count==0) return -1;
    else {
        return tab[rand()%count];
    }
}



