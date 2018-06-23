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
