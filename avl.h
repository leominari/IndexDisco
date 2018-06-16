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

int contaAVL(avl *prim);

void rotacaoEsq(avl ** prim);

void rotacaoDir(avl ** prim);

int balanceamento(avl **prim);

void criaNoLista(avl **prim, unsigned long chave, int i);

int insereAVL(avl ** prim, unsigned long chave, unsigned long naochave, int i);

int subAVL(avl **prim, avl *help);

int removeAVL(avl **prim, unsigned long chave, unsigned long naochave);
