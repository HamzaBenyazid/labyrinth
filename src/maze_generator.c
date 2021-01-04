#include"maze_generator.h"

void init(matriceDesCell *m)
{
    int i=0;
    for (i=0;i<N*N;i++){
        (*m+i)->up=0;
        (*m+i)->down=0;
        (*m+i)->left=0;
        (*m+i)->right=0;
    }
    for (i=0;i<N;i++){
        (*m+i)->up=-1;
        (*m+i+(N-1)*N)->down=-1;
        (*m+i*N)->left=-1;
        (*m+N-1+i*N)->right=-1;
    }
    
    
}
int randomPath(matriceDesCell m,int line,int col,int* visited)
{
    cell in=*(m+N*line+col);
    int tab[4];
    int count=0;
    if (in.up==0 &&*(visited+(line-1)*N+col)==0) {
        tab[count]=up;
        count++;
    }
    if (in.right==0 &&*(visited+line*N+col+1)==0) {
        tab[count]=right;
        count++;
    }
    if (in.down==0 &&*(visited+(line+1)*N+col)==0) {
        tab[count]=down;
        count++;
    }
    if (in.left==0 &&*(visited+line*N+col-1)==0) {
        tab[count]=left;
        count++;
    }
    if (count==0) return -1;
    else {
        return tab[rand()%count];
    }
}
/*void main()
{
    int visited[3][3]={{0}};
    visited[1][0]=1;
    visited[0][1]=1;
    srand(time(0));
    matriceDesCell m=(cell*)malloc(N*N*sizeof(cell));
    init(&m);
    //printf("%d",m->right);
    int x=randomPath(m,0,0,visited);
    printf("%d",x);
    
}*/
