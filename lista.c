#include "lista.h"

rep *alocaRep(unsigned long chave, int bloco)
{
 rep *rep = malloc(sizeof(rep));
 if (rep == NULL) return NULL;
 rep->chave = chave;
 rep->bloco = bloco;
 rep->prox = NULL;
 return rep;
}

void insereRep(rep **prim, unsigned long chave, int bloco)
{
  if((*prim) == NULL)
    *prim = alocaRep(chave, bloco);
  else
    insereRep(&((*prim)->prox), chave, bloco);
}

void imprimeRep(rep *prim){
  if(prim == NULL) return;
  printf("%lu|%d", prim->chave, prim->bloco );
  imprimeRep(prim->prox);
}

void listaRep(rep* prim){
  printf("Chave: %lu\n", prim->chave);
  listaRep(prim->prox);
}

int buscaBloco(rep* prim, unsigned long chave){
  if(prim == NULL) return -1;
  if(prim->chave == chave)
    return prim->bloco;
  return buscaBloco(prim->prox, chave);

}
