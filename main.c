#include <stdlib.h>
#include <stdio.h>
#include "redblack.c"
#include "avl.c"


typedef struct registro{
	unsigned long chave;//Campo chave Valor nao se repete.
	unsigned long naochave;//Campo qualquer. Valor pode repetir.
	unsigned char outros[1008];//outros campos: 1008 bytes (dados)
}reg;

int h; //Contagem dos blocos

int main(){
	reg registros[4];
	int i = 0;
	int x = 0;
	int est;
	rep* chaves;
	unsigned long val, chave_ler;
	FILE *arquivo;
	Tree* arvore_red = NULL;
	avl* arvore_avl = NULL;
	arquivo = fopen("base.bin", "r+");
	printf("Qual estrutura deve ser utilizada: \n 0 - Arvore AVL \n 1 - Arvore Red-Black \n");
	scanf("%d", &est);
	printf("Criando a arvore...\n");
	if(est == 0){

		while(x < 4){
			fread(registros, sizeof(reg), 4, arquivo);
			while(i < 4){
				insereAVL(&arvore_avl, registros[i].chave, registros[i].naochave, h);
				printf("%lu,%lu, %d \n", registros[i].chave, registros[i].naochave, h);
				i++;
			}
			h++;
			i=0;
			x++;
		}
	}

	if(est == 1){

		while(x < 4){
			fread(registros, sizeof(reg), 4, arquivo);
			while(i < 4){
				arvore_red = insert(arvore_red, registros[i].naochave, registros[i].chave, h);
				i++;
			}
			print(arvore_red, 0);
			h++;
			i=0;
			x++;
		}
	}

	printf("Digite o valor a ser buscado:\n");
	scanf("%lu", &val);
	if(est == 0){
		chaves = searchAVL(arvore_avl, val);
	}
	else{
		chaves = search(arvore_red, val);
	}
	printf("Qual das Chaves deseja ver?\n");
	listaRep(chaves);
	scanf("%lu",&chave_ler);
	printf("BUSCOU\n");
	buscaBloco(chaves, chave_ler);
	//fseek(registros, sizeof(reg), SEEK_SET);
	//i = 0;
	//while(i)
	fclose(arquivo);

}
