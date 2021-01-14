#include "Affichage.h"



char* matrix2show(matriceDesCell m)
{
    int size_ligne=N*2+(N+1);
    int size_colone=M*2+(M+1);

    char* matrix_2_show=(char*)malloc(size_ligne*size_colone);
    int i,j=0,k,n=0;
    for(i=0;i<size_ligne*size_colone;i++){
        *(matrix_2_show+i)=' ';
    }
    for (i=0;i<size_colone;i++){
        *(matrix_2_show+i)='#';                 //initialization de 1er ligne
        *(matrix_2_show+size_colone*(size_ligne-1)+i)='#';   //initialization de dernier ligne
    }
    for (i=0;i<size_ligne;i++){
        *(matrix_2_show+size_colone*i)='#';            //initialization de 1er colone
        *(matrix_2_show+size_colone*i+size_colone-1)='#';     //initialization de dernier colone
    }
    for (k=0,n=3;k<N && n<size_ligne;k++,n+=3){
        for (i=0,j=3;i<M && j<size_colone;i++,j+=3){
            if ((m+i+k*M)->right==0){
                *(matrix_2_show+(n-3)*size_colone+j)='#';
                *(matrix_2_show+(n-2)*size_colone+j)='#';
                *(matrix_2_show+(n-1)*size_colone+j)='#';
                *(matrix_2_show+n*size_colone+j)='#';

            }
            if ((m+i+k*M)->down==0){
                *(matrix_2_show+n*size_colone+j-3)='#';
                *(matrix_2_show+n*size_colone+j-2)='#';
                *(matrix_2_show+n*size_colone+j-1)='#';
                *(matrix_2_show+n*size_colone+j)='#';

            }
        }
    }
    return matrix_2_show;
}
void affichage(char* matrix_2_show)
{
    int size_ligne=N*2+(N+1);
    int size_colone=M*2+(M+1);
    int i,j;
    for(i=0;i<size_ligne;i++){
        for(j=0;j<size_colone;j++){
            printf("%c",*(matrix_2_show+i*size_colone+j));
        }
        printf("\n");
    }
}