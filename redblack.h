#include <stdio.h>
#include <stdlib.h>
#include "lista.c"

#define N (1 << 24)
#define BLACK 0
#define RED 1

int last, total;

typedef struct Tree{
    unsigned short int color;
    unsigned long naochave;
    rep* rep_chave;
    struct Tree *left, *right, *parent;
}Tree;

Tree* newNode(Tree *parent, unsigned long x);
Tree *mySibling(Tree *tree);
Tree* myAvo(Tree *tree);
Tree* myUncle(Tree *avo, Tree *tree);
Tree* updateRoot(Tree *tree);
rep* search(Tree *tree, unsigned long x);
void rotate_left(Tree *tree);
void rotate_right(Tree *tree);
void treat_inclusion(Tree *tree);
Tree* insert(Tree *tree, unsigned long x, unsigned long chave, int bloco);
void print(Tree *tree, int height);
int check(Tree *tree, int color);
