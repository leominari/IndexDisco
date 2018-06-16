#include <stdlib.h>
#include <stdio.h>
#include "avl.c"

typedef struct registro{
	unsigned long chave;//Campo chave Valor nao se repete.
	unsigned long naochave;//Campo qualquer. Valor pode repetir.
	unsigned char outros[1008];//outros campos: 1008 bytes (dados)
}reg;

int h;

int main(){
	reg registros[4];
	int i,x;
	i=0;
	avl* arvore_um = NULL;
	FILE *arquivo;
	arquivo = fopen("base.bin", "rb");
	for(x=0;x<3;x++){
		fread(registros, sizeof(reg), 4, arquivo);
		fseek(arquivo, sizeof(reg), SEEK_CUR); //atual
		h++;
		while(i<4){
			insereAVL(&arvore_um, registros[i].chave, registros[i].naochave, h);
			printf("%lu,%lu, %d \n", registros[i].chave, registros[i].naochave, h);
			i++;
		}
		i=0;
	}
	contaAVL(arvore_um);
	// fread(registros, sizeof(reg),4, arquivo);

	fclose(arquivo);

	return 0;


}
