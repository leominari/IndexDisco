#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define RED 1
#define BLACK 0

typedef struct AVL{
  int chave;
  int cor;
  struct AVL *dir, *esq, *pai;
}AVL;



AVL *novoNo(AVL **avl, int chave);
AVL *meuIrmao(AVL **avl);
AVL *meuAvo(AVL **avl);
AVL *meuTio(AVL **avo, AVL **avl);
AVL *atualizarRaiz(AVL **avl);
AVL *buscarAVL(AVL *avl, int chave);
AVL *insercao(AVL **avl, int chave);

void rotacaoESQ(AVL **avl);
void rotacaoDIR(AVL **avl);
void inclusao(AVL **avl);
void travessia(AVL *avl);

int main(){

    AVL *avl = NULL;
<<<<<<< Updated upstream
    insercao(&avl, 5);
    insercao(&avl, 3);
    insercao(&avl, 1);
    insercao(&avl, 4);
    insercao(&avl, 6);
    insercao(&avl, 7);
    insercao(&avl, 9);
    travessia(avl);
=======
    insercao(&avl, 1);
    insercao(&avl, 4);
    insercao(&avl, 2);
    insercao(&avl, 5);
    //insercao(&avl, 3);
    //insercao(&avl, 7);
    //insercao(&avl, 9);

>>>>>>> Stashed changes
}


AVL *novoNo(AVL **avl, int chave){

    AVL *novo = (AVL *)malloc(sizeof(AVL));
    if (novo == NULL) return NULL;
    novo->cor = RED;
    novo->chave = chave;
    novo->pai = *avl;
    novo->esq = novo->dir = NULL;
    return novo;
}

AVL *meuIrmao(AVL **avl){
    assert(avl); //assert((avl)->pai);
    if (((*avl)->pai)->esq == *avl) return ((*avl)->pai)->dir;
    return ((*avl)->pai)->esq;
}

AVL *meuAvo(AVL **avl){
    if(*avl != NULL && (*avl)->pai != NULL) return ((*avl)->pai)->pai;
    return NULL;
}

AVL* meuTio(AVL **avo, AVL **avl){
    assert(*avl); assert(*avo);
    if ((*avo)->esq == (*avl)->pai) return (*avo)->dir;
    return (*avo)->esq;
}

AVL *atualizarRaiz(AVL **avl){
    if ((*avl) == NULL) return NULL;
    while((*avl)->pai != NULL) *avl = (*avl)->pai;
    return *avl;
}

AVL* buscarAVL(AVL *avl, int chave){

    while(avl != NULL){
        if (chave == avl->chave) return avl;
        if (chave < avl->chave) avl = avl->esq;
        else avl = avl->dir;
    }
    return NULL;
}


void rotacaoESQ(AVL **avl){
    assert(avl);
    if ((*avl)->pai != NULL)
        if (*avl == ((*avl)->pai)->esq)
            ((*avl)->pai)->esq = (*avl)->dir;
        else
            ((*avl)->pai)->dir = (*avl)->dir;

    ((*avl)->dir)->pai = (*avl)->pai;
    (*avl)->pai = (*avl)->dir;
    (*avl)->dir = ((*avl)->dir)->esq;
    ((*avl)->pai)->esq = *avl;
    if ((*avl)->dir) ((*avl)->dir)->pai = *avl;
}

void rotacaoDIR(AVL **avl){
    assert(avl);
    if ((*avl)->pai != NULL)
        if ((*avl) == ((*avl)->pai)->esq)
            ((*avl)->pai)->esq = (*avl)->esq;
        else
            ((*avl)->pai)->dir = (*avl)->esq;

    ((*avl)->esq)->pai = (*avl)->pai;
    (*avl)->pai = (*avl)->esq;
    (*avl)->esq = ((*avl)->esq)->dir;
    ((*avl)->pai)->dir = (*avl);
    if ((*avl)->esq) ((*avl)->esq)->pai = (*avl);
}

void inclusao(AVL **avl){
    assert(avl);
    if ((*avl)->pai == NULL){
        (*avl)->cor = BLACK;
        return;
    }
    if (((*avl)->pai)->cor == BLACK) return;
//    printf("teste\n" );
    AVL *avo = meuAvo(&(*avl));
    AVL *tio = meuTio(&avo, &(*avl));
    if (tio != NULL && tio->cor == RED){
        tio->cor = ((*avl)->pai)->cor = BLACK;
        avo->cor = RED;
        inclusao(&avo);
        return;
    }

    if ((*avl) == ((*avl)->pai)->dir && (*avl)->pai == avo->esq){
        rotacaoESQ(&(*avl)->pai);
        (*avl) = (*avl)->esq;
    }else if ((*avl) == ((*avl)->pai)->esq && (*avl)->pai == avo->dir){
        rotacaoDIR(&(*avl)->pai);
        (*avl) = (*avl)->dir;
    }

    ((*avl)->pai)->cor = BLACK;
    avo->cor = RED;
    if ((*avl) == ((*avl)->pai)->esq) rotacaoDIR(&avo);
    else rotacaoESQ(&avo);
}

AVL* insercao(AVL **avl, int chave){

    if (*avl == NULL) {
        *avl = novoNo(&(*avl), chave);
        printf("TESTE  %d\n", (*avl)->chave);
        (*avl)->cor = BLACK;
        return *avl;
    }

    AVL *raiz = *avl;
    while((*avl)->chave != chave){
        if (chave < (*avl)->chave){
            if ((*avl)->esq != NULL) *avl = (*avl)->esq;
            else {
                (*avl)->esq = novoNo(&(*avl), chave);
                printf("TESTE  %d\n", ((*avl)->esq)->chave);
                break;
            }
        }else{
            if ((*avl)->dir != NULL) *avl = (*avl)->dir;
            else {
                (*avl)->dir = novoNo(&(*avl), chave);
                printf("TESTE  %d\n", ((*avl)->dir)->chave);
                break;
            }
        }
    }
    if ((*avl)->chave == chave) return NULL; //implementação da lista
    if ((*avl)->esq != NULL && ((*avl)->esq)->chave == chave) inclusao(&(*avl)->esq);
    else inclusao(&(*avl)->dir);
    return atualizarRaiz(&raiz);
}


void travessia(AVL *avl){
<<<<<<< Updated upstream
  while (avl != NULL) {
    printf("%d\n", avl->chave);
    travessia(avl->esq);
=======
  while (avl !=NULL) {
    travessia(avl->esq);
    printf("%d\n", avl->chave);
>>>>>>> Stashed changes
    travessia(avl->dir);
  }
}
