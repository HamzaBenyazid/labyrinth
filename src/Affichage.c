#include "Affichage.h"

char* matrix2show(matriceDesCell m)
{
    int size=N*2+(N+1);
    char* matrix_2_show=(char*)malloc(size*size);
    int i,j=0,k,n=0;
    for(i=0;i<size*size;i++){
        *(matrix_2_show+i)=' ';
    }
    for (i=0;i<size;i++){
        *(matrix_2_show+i)='#';                 //initialization de 1er ligne
        *(matrix_2_show+size*(size-1)+i)='#';   //initialization de dernier ligne
        *(matrix_2_show+size*i)='#';            //initialization de 1er colone
        *(matrix_2_show+size*i+size-1)='#';     //initialization de 1er ligne
    }
    for (k=0,n=3;k<N && n<size;k++,n+=3){
        for (i=0,j=3;i<N && j<size;i++,j+=3){
            if ((m+i+k*N)->right==0){
                *(matrix_2_show+(n-3)*size+j)='#';
                *(matrix_2_show+(n-2)*size+j)='#';
                *(matrix_2_show+(n-1)*size+j)='#';
                *(matrix_2_show+n*size+j)='#';

            }
            if ((m+i+k*N)->down==0){
                *(matrix_2_show+n*size+j-3)='#';
                *(matrix_2_show+n*size+j-2)='#';
                *(matrix_2_show+n*size+j-1)='#';
                *(matrix_2_show+n*size+j)='#';

            }
        }
    }
    return matrix_2_show;
}
void affichage(char* matrix_2_show)
{
    int size=N*2+(N+1);
    int i,j;
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            printf("%c",*(matrix_2_show+i*size+j));
        }
        printf("\n");
    }
}
void fill(cell* m,int i,int j,int up, int right, int down, int left)
{
    (m+N*i+j)->up = up;
    (m+N*i+j)->right = right;
    (m+N*i+j)->down = down;
    (m+N*i+j)->left = left;
}
