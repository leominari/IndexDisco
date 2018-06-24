#include <stdlib.h>
#include <stdio.h>
#include "redblack.c"
#include "avl.c"

typedef struct registro{
	unsigned long chave;//Campo chave Valor nao se repete.
	unsigned long naochave;//Campo qualquer. Valor pode repetir.
	unsigned char outros[1008];//outros campos: 1008 bytes (dados)
}reg;
