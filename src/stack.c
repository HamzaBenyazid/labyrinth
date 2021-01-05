#include"stack.h"


void append(stack **s, int i, int j)
{
    stack *nouveau=Malloc(stack);
    nouveau->colonne = j;
    nouveau->ligne = i;
    nouveau->suivant=*(s);
    *(s)=nouveau;
}
/*void afficherStack(stack *s)
{
    printf("\n\n");
    while(s!=NULL){
        printf("%d\n",s->data);
        s=s->suivant;
    }
}*/
void pop(stack **s)
{
    if (!estVide(*s)) *s=(*s)->suivant;
}

int* top(stack *s) 
{
    int* coordonne = (int*)malloc(sizeof(int)*2);
    *coordonne = s->ligne;
    *(coordonne+1) = s->colonne;
    return coordonne;
}
int estVide(stack *s)
{
    return (s==NULL);
}
