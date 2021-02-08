#include"stack.h"

//cette fonction fait l'empilement
void append(stack **s, int i, int j)
{
    stack *nouveau=Malloc(stack);
    nouveau->colonne = j;
    nouveau->ligne = i;
    nouveau->suivant=*(s);
    *(s)=nouveau;
}

//cette fonction affiche la pile (nous avons eu besoins de cette fonction dans le debug)
void afficherStack(stack *s)
{
    printf("\n\n");
    while(s!=NULL){
        printf("%d %d\n",s->ligne,s->colonne);
        s=s->suivant;
    }
}

//cette fonction fait le dépilement
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

// cette fonction retourne les coordonne de la cellule qui est dans la tête de la pile
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

//fonction qui retourne si la pile est vide ou non
int estVide(stack *s)
{
    return (s==NULL);
}

//fonction qui retourne la longueur de la pile
int length(stack *s)
{
    int count=0;
    
    while(s!=NULL){
        s=s->suivant;
        count++;
    }
    return count;
}

//fonction qui libére la pile de la mémoire
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
