#include"maze_generator.h"
#include"stack.h"
#include"Affichage.h"
#include"maze_solver.h"
#include"Affichage_SDL.h"

int main()
{
    srand(time(0));
    matriceDesCell m;
    char* matrix_2_show=NULL;
    m = generate_maze();
    matrix_2_show=matrix2show(m);
    /*affichage(matrix_2_show);
    int entre[2]={0,0};
    int sortie[2]={N-1,N-1};
    stack *s=NULL;
    s=solveMaze(m,entre,sortie);
    afficherStack(s);*/
    SDL_main(m,matrix_2_show);
    
    return 0;
}