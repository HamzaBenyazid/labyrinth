#include"maze_generator.h"
#include"stack.h"
#include"Affichage.h"


int main()
{
    srand(time(0));
    matriceDesCell m;
    char* matrix_2_show;
    m = generate_maze();
    /*m=(cell*)malloc(N*N*sizeof(cell));
    init(&m);
    fill(m,0,0,-1,1,0,-1);
    fill(m,0,1,-1,0,1,1);
    fill(m,0,2,-1,1,0,0);
    fill(m,0,3,-1,-1,1,1);
    fill(m,1,0,0,0,1,-1);
    fill(m,1,1,1,1,0,0);
    fill(m,1,2,0,1,0,1);
    fill(m,1,3,1,-1,1,1);
    fill(m,2,0,1,1,1,-1);
    fill(m,2,1,0,1,0,1);
    fill(m,2,2,0,0,0,1);
    fill(m,2,3,1,-1,1,0);
    fill(m,3,0,1,1,-1,-1);
    fill(m,3,1,0,1,-1,1);
    fill(m,3,2,0,1,-1,1);
    fill(m,3,3,1,-1,-1,1);*/
    matrix_2_show=matrix2show(m);
    affichage(matrix_2_show);
    return 0;
}