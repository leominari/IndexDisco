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
  if((*prim) == NULL){
    *prim = alocaRep(chave, bloco);
    return;
  }
  return insereRep(&((*prim)->prox), chave, bloco);
}

// void removeInicio(rep **prim)
// {
//   if ((*prim) == NULL) return;
//   rep *aux = (*prim);
//   (*prim)=(*prim)->prox;
//   free(aux);
// }

void imprimeRep(rep *prim){
  if(prim->prox == NULL) return;
  printf("%d", prim->chave);
  printf("|%d\n", prim->bloco);
  imprimeRep(prim->prox);
}
