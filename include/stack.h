#ifndef STACK
#define STACK

#include<stdio.h>
#include<stdlib.h>

#define Malloc(type) (type*)malloc(sizeof(type))

typedef struct _stack
{
    int colonne;
    int ligne;
    struct _stack *suivant;
    
}stack;

void append(stack **s,int i,int j);
//void afficherStack(stack *s);
void pop(stack **s);
int* top(stack *s);
int estVide(stack *s);

#endif