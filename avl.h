#include <stdio.h>
#include <stdlib.h>

typedef struct tAVL{
  unsigned long naochave;
  rep* rep_chave;
  struct tAVL * dir;
  struct tAVL * esq;
  int fb;
}avl;


avl * criaNoAVL(unsigned long naochave);

void contaAVL(avl *prim);

void rotacaoEsq(avl ** prim);

void rotacaoDir(avl ** prim);

int balanceamento(avl **prim);

int insereAVL(avl ** prim, unsigned long chave, unsigned long naochave, int i);

int subAVL(avl **prim, avl *help);

int removeAVL(avl **prim, unsigned long chave, unsigned long naochave);

rep* searchAVL(avl *tree, unsigned long x);
