#include "avl.h"

avl * criaNoAVL(unsigned long naochave){
  avl *prim = malloc(sizeof(avl)); //aloca dinamicamente
  prim->rep_chave = NULL;
  prim->naochave = naochave;
  prim->dir = NULL; //evita erros futuros colocando NULL
  prim->esq = NULL; //evita erros futuros colocando NULL
  prim->fb = 0; //todo novo nó tem fb = 0
  return prim;
}



void contaAVL(avl *prim){
  if(prim != NULL){ //verifica se existe a arvore
    contaAVL(prim->dir); //soma 1 para cada nó recursivamente
    printf("CHAVE:%lu FB:%d\n", prim->naochave, prim->fb);
    contaAVL(prim->esq);
    return;
  }
  printf("NULL\n");
  return ; //retorna 0 se nao existir a arvore
}


void rotacaoEsq(avl ** prim){
  if((*prim) == NULL) return;
  avl * temp = (*prim)->dir;
  (*prim)->dir = temp->esq;
  temp->esq = *prim;

  if ((*prim)->fb == 2){//Verifica se é uma rotação simples
        if (temp->fb == 2){
            (*prim)->fb = -1;
            temp->fb = 0;
        }else if (temp->fb == 1){ //Pós tipo simples de rotação, todos os campos alterados ficaram 0
            (*prim)->fb = 0;
            temp->fb = 0;
        }else{
            (*prim)->fb = 1;
            temp->fb = -1;
        }
    }else{ //se for uma rotação dupla
        if (temp->fb == -1){
            (*prim)->fb = 0;
            temp->fb = -2;
        }else if (temp->fb == 1){
            (*prim)->fb = -1;
            temp->fb = -1;
        }else{  //temp->fb == 0
            (*prim)->fb = 0;
            temp->fb = -1;
        }
    }
    (*prim) = temp;
}

void rotacaoDir(avl ** prim){
  if((*prim) == NULL) return;
  avl * temp = (*prim)->esq;
  (*prim)->esq = temp->dir;
  temp->dir = *prim;
  if ((*prim)->fb == -2){ //Verifica se é uma rotação simples
        if (temp->fb == -2){
            (*prim)->fb = 1;
            temp->fb = 0;
        }else if (temp->fb == -1){//Pós tipo simples de rotação, todos os campos alterados ficaram 0
            (*prim)->fb = 0;
            temp->fb = 0;
        }else{
            (*prim)->fb = -1;
            temp->fb = 1;
        }
    }else{
        //rotação dupla
        if (temp->fb == 1){
            (*prim)->fb = 0;
            temp->fb = 2;
        }else if (temp->fb == -1){
            (*prim)->fb = 1;
            temp->fb = 1;
        }else{  //temp->fb == 0
            (*prim)->fb = 0;
            temp->fb = 1;
        }
    }
    (*prim) = temp;
}


int balanceamento(avl **prim){
  if((*prim)->fb == 2){ //Verifica se esta pesada para direita
  if(((*prim)->dir)->fb == -1){ //Verifica se necessita de rotação dupla
      rotacaoDir(&((*prim)->dir));//Se necessario faz a rotação para a direita no filho direito
    }
    rotacaoEsq(prim); //Independente de dupla ou simples faz a rotação
  }
  else
    if((*prim)->fb == -2){ //Verifica se esta pesada para esquerda
      if(((*prim)->esq)->fb > 0) //Verifica se necessita de rotação dupla
        rotacaoEsq(&((*prim)->esq));//Se necessario faz a rotação para a esquerda no filho esquerdo
      rotacaoDir(prim); //Independente de dupla ou simples faz a rotação
    }
    else
      if((*prim)->fb != 0)
        return 1;
  return 0;
}


int insereAVL(avl ** prim, unsigned long chave, unsigned long naochave, int i){
  if((*prim) == NULL){ //verifica se a arvore é vazia para a criação do novo nó
    *prim = criaNoAVL(naochave); //chama a função de criar nó para criar o nó
    insereRep(&((*prim)->rep_chave), chave, i);
    return 1; //retorna 1 para informar que o nó cresceu.
  }
  int temp = 0; //Variavel auxiliar para ajudar no balanceamento
  if(naochave == ((*prim)->naochave))
    insereRep(&((*prim)->rep_chave), chave, i);
  if(naochave < (*prim)->naochave) //Se chave for menor, rescursivo para a esquerda
    temp -= insereAVL(&((*prim)->esq), chave, naochave, i); //calculo FB = AD-AE
  else
    if(naochave > (*prim)->naochave) //Se a chave for maior, recursivo para a direita
      temp = insereAVL(&((*prim)->dir), chave, naochave, i); //calculo  FB = AD-AE
    else
      return 0; //Se for igual, retorna 0
  if(temp){ //Se nada deu errado entra aqui
    (*prim)->fb += temp; //Atualiza o campo fb
    return balanceamento(prim); //Chama a função de balanceamento
  }
  return 0;
}


int subAVL(avl **prim, avl *help){
  int temp = 0; //variavel auxiliar
  if((*prim)->esq == NULL){
    help->naochave = (*prim)->naochave;
    avl **rem = prim;
    (*prim) = (*prim)->dir;
    free((*rem));
    return 1;
  }
  else
    temp -= subAVL(&((*prim)->esq), help);
  if(temp){
    (*prim)->fb -= temp;
    balanceamento(prim);
    if((*prim)->fb == 0)
      return 1;
  }
  return 0;

}

int removeAVL(avl **prim, unsigned long chave, unsigned long naochave){
  if((*prim) == NULL) return 0; //verifica a existencia da arvore
  int temp = 0;  //variavel auxiliar
  if((*prim)->naochave == naochave){
    if((*prim)->esq && (*prim)->dir)
      temp = subAVL(&((*prim)->dir), (*prim));
    else{
      avl **aux = prim;
      if((*prim)->esq == NULL)
        (*prim) = (*prim)->dir;
      else
        (*prim) = (*prim)->esq;
      free(*aux);
      return 1;
    }
  }
  else
    if((*prim)->naochave > naochave)
      temp -= removeAVL(&((*prim)->esq),chave, naochave);
    else
      temp = removeAVL(&((*prim)->dir),chave, naochave);
  if(temp){
    (*prim)->fb -= temp;
    balanceamento(prim);
    if((*prim)->fb == 0)
      return 1;
  }
  return 0;
}
