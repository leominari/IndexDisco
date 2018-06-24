#include "redblack.h"

Tree* newNode(Tree *parent, unsigned long x){

    Tree* tree = (Tree*)malloc(sizeof(Tree));
    if (tree == NULL) {
        puts("Erro de alocacao");
    }
    total++;
    tree->color = RED;
    tree->naochave = x;
    tree->parent = parent;
    tree->left = tree->right = NULL;
    return tree;
}

Tree *mySibling(Tree *tree){
    if (tree->parent->left == tree) return tree->parent->right;
    return tree->parent->left;
}

Tree* myAvo(Tree *tree){
    if(tree != NULL && tree->parent != NULL) return tree->parent->parent;
    return NULL;
}

Tree* myUncle(Tree *avo, Tree *tree){
    if (avo->left == tree->parent) return avo->right;
    return avo->left;
}

Tree* updateRoot(Tree *tree){
    if (tree == NULL) return NULL;
    while(tree->parent != NULL) tree = tree->parent;
    return tree;
}

rep* search(Tree *tree, unsigned long x){
    if(tree == NULL) return NULL;
    if (x == tree->naochave)
      return tree->rep_chave;
    if (x < tree->naochave)
      search(tree->left, x);
    else
      search(tree->right, x);
}


void rotate_left(Tree *tree){
    if (tree->parent != NULL)
        if (tree == tree->parent->left)
            tree->parent->left = tree->right;
        else
            tree->parent->right = tree->right;

    tree->right->parent = tree->parent;
    tree->parent = tree->right;
    tree->right = tree->right->left;
    tree->parent->left = tree;
    if (tree->right) tree->right->parent = tree;
}

void rotate_right(Tree *tree){
    if (tree->parent != NULL)
        if (tree == tree->parent->left)
            tree->parent->left = tree->left;
        else
            tree->parent->right = tree->left;

    tree->left->parent = tree->parent;
    tree->parent = tree->left;
    tree->left = tree->left->right;
    tree->parent->right = tree;
    if (tree->left) tree->left->parent = tree;
}

void treat_inclusion(Tree *tree){
    if (tree->parent == NULL){
        tree->color = BLACK;
        return;
    }

    if (tree->parent->color == BLACK) return;

    Tree *avo = myAvo(tree);
    Tree *uncle = myUncle(avo, tree);
    if (uncle != NULL && uncle->color == RED){
        uncle->color = tree->parent->color = BLACK;
        avo->color = RED;
        treat_inclusion(avo);
        return;
    }

    if (tree == tree->parent->right && tree->parent == avo->left){
        rotate_left(tree->parent);
        tree = tree->left;
    }

    else
      if (tree == tree->parent->left && tree->parent == avo->right){
        rotate_right(tree->parent);
        tree = tree->right;
    }

    tree->parent->color = BLACK;
    avo->color = RED;
    if (tree == tree->parent->left)
      rotate_right(avo);
    else
      rotate_left(avo);
}

Tree* insert(Tree *tree, unsigned long x, unsigned long chave, int bloco){

    if (tree == NULL) {
        tree = newNode(NULL, x);
        tree->color = BLACK;
        return tree;
    }

    Tree *head = tree;
    while(tree->naochave != x){
        if (x < tree->naochave){
            if (tree->left != NULL)
              tree = tree->left;
            else {
              tree->left = newNode(tree, x);
              insereRep(&(tree->rep_chave), chave, bloco);
              break;
            }
        }else{
          if(x == tree->naochave){
            insereRep(&(tree->rep_chave), chave, bloco);
          }
          else{
            if (tree->right != NULL)
              tree = tree->right;
            else {
              tree->right = newNode(tree, x);
              insereRep(&(tree->rep_chave), chave, bloco);
              break;
            }
          }
        }
    }
    if (tree->naochave == x) return head;    //means that the element already inserted and nothing was do

    if (tree->left != NULL && tree->left->naochave == x)
      treat_inclusion(tree->left);
    else
      treat_inclusion(tree->right);

    return updateRoot(head);
}


void print(Tree *tree, int height){

    if (tree == NULL) return;

    print(tree->left, height+1);
    printf("Chave: %lu - Cor: ", tree->naochave);
    if(tree->color == RED)
      printf("VERMELHO - Altura: %d\n", height);
    else
      printf("PRETO - Altura: %d\n", height);
    print(tree->right, height+1);
}

int check(Tree *tree, int color){

    if (tree == NULL) return 0;

    total--;
    if (color && tree->color){
        printf("Consecutive red in %d and %d\n", tree->color, tree->parent->color);
        return -1;
    }

    int l, r;
    l = check(tree->left, tree->color);
    if (last >= tree->naochave){
        printf("Err in %d and %d\n", last, tree->naochave);
    }
    last = tree->naochave;
    r = check(tree->right, tree->color);

    if (l != r){
        if (l != -1 && r != -1)
            printf("Err in quantity of black childs, starting the parent %d\n", tree->naochave);
        return -1;
    }

    if (tree->color == BLACK) l++;
    return l;
}
