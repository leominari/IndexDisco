#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
  unsigned long chave;
  int bloco;
  struct lista * prox;
}rep;

rep *alocaRep(unsigned long chave, int bloco);

void insereRep(rep **prim, unsigned long chave, int bloco);

void imprimeRep(rep *prim);

void listaRep(rep* prim);

int buscaBloco(rep* prim, unsigned long chave);
