#include"maze_solver.h"



int randomPath_Sol(matriceDesCell m,int line,int col,int* visited)
{
    cell in=*(m+N*line+col);
    int tab[4];
    int count=0;
    if (in.up==1 &&*(visited+(line-1)*N+col)==0) {
        tab[count]=up;
        count++;
    }
    if (in.right==1 &&*(visited+line*N+col+1)==0) {
        tab[count]=right;
        count++;
    }
    if (in.down==1 &&*(visited+(line+1)*N+col)==0) {
        tab[count]=down;
        count++;
    }
    if (in.left==1 &&*(visited+line*N+col-1)==0) {
        tab[count]=left;
        count++;
    }
    if (count==0) return -1;
    else {
        return tab[rand()%count];
    }
}
stack* solveMaze(matriceDesCell maze,int entre[2],int sortie[2])
{
    stack* solution=NULL;
    int* visited = (int*)malloc(N*N*sizeof(int));
    int way;
    int i, j;

    // Initialisé la matrice des cellules visitées
    for(i=0;i<N*N;i++)
    {
        *(visited+i) = 0;
    }
    
    i = entre[0];
    j = entre[1];
    append(&solution, i, j);
    while(i!=sortie[0] || j!=sortie[1])
    {
        way = randomPath_Sol(maze, i, j,visited);
        *(visited+i*N+j) = 1;
        switch(way)
        {
            case up : 
                    i--;
                    append(&solution, i, j);
                    break;
            case down :
                    i++;
                    append(&solution, i, j);
                    break;
            case right :
                    j++;
                    append(&solution, i, j);
                    break;
            case left :
                    j--;
                    append(&solution, i, j);
                    break;
            case -1 :
                    pop(&solution);
                    i = *top(solution);
                    j = *(top(solution)+1);
                    break;
        }
    }
    free(visited);
    return solution;
}

