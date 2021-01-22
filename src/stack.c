#include"stack.h"


void append(stack **s, int i, int j)
{
    stack *nouveau=Malloc(stack);
    nouveau->colonne = j;
    nouveau->ligne = i;
    nouveau->suivant=*(s);
    *(s)=nouveau;
}
void afficherStack(stack *s)
{
    printf("\n\n");
    while(s!=NULL){
        printf("%d %d\n",s->ligne,s->colonne);
        s=s->suivant;
    }
}
void pop(stack **s)
{
    stack* previous;
    if (!estVide(*s)) 
    {
        previous = *s;
        *s=(*s)->suivant;
        free(previous);
    }
}

int* top(stack *s) 
{
    int* coordonne = (int*)malloc(sizeof(int)*2);
    if (estVide(s)){
        *coordonne = -1;
        *(coordonne+1) = -1;
        return coordonne;
    }
    *coordonne = s->ligne;
    *(coordonne+1) = s->colonne;
    return coordonne;
}
int estVide(stack *s)
{
    return (s==NULL);
}
int length(stack *s)
{
    int count=0;
    while(s!=NULL){
        s=s->suivant;
        count++;
    }
    return count;
}

void free_stack(stack *s)
{
    stack* previous;

    while(s != NULL)
    {
        previous = s;
        s = s->suivant;
        free(previous);
    }
}
