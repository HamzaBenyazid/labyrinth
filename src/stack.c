#include"stack.h"


void append(stack **s,int data)
{
    stack *nouveau=Malloc(stack);
    nouveau->data=data;
    nouveau->suivant=*(s);
    *(s)=nouveau;
}
void afficherStack(stack *s)
{
    printf("\n\n");
    while(s!=NULL){
        printf("%d\n",s->data);
        s=s->suivant;
    }
}
void pop(stack **s)
{
    if (!estVide(*s)) *s=(*s)->suivant;
}
int top(stack *s)
{
    return s->data;
}
int estVide(stack *s)
{
    return (s==NULL);
}
