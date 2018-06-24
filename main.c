#include "trabalho.h"
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
	if(est != 1 && est != 0){
		printf("Esta estrutura não existe.\n");
		exit(0);
	}
	printf("Criando a arvore...\n");
	if(est == 0){

		while(!feof(arquivo)){
			fread(registros, sizeof(reg), 4, arquivo);
			while(i < 4){
				//printf("%lu, %lu\n",registros[i].chave, registros[i].naochave);
				insereAVL(&arvore_avl, registros[i].chave, registros[i].naochave, h);
				i++;
			}
			h++;
			i=0;
			x++;
		}
	}

	if(est == 1){

		while(!feof(arquivo)){
			fread(registros, sizeof(reg), 4, arquivo);
			while(i < 4){
				//printf("%lu, %lu\n",registros[i].chave, registros[i].naochave);
				arvore_red = insert(arvore_red, registros[i].naochave, registros[i].chave, h);
				i++;
			}
			h++;
			i=0;
			x++;
		}
	}
	printf("Arvore Carregada!\n\n");
	printf("Digite o valor a ser buscado:\n");
	scanf("%lu", &val);
	if(est == 0){
		chaves = searchAVL(arvore_avl, val);
		if(chaves == NULL){
			printf("Não existe esse valor.\n");
			exit(0);
		}
	}
	if(est == 1){
		chaves = search(arvore_red, val);
		if(chaves == NULL){
			printf("Não existe esse valor.\n");
			exit(0);
		}
	}
	listaRep(chaves);
	printf("Qual das Chaves deseja ver?\n");
	scanf("%lu",&chave_ler);
	x = buscaBloco(chaves, chave_ler);
	if(x == -1){
		printf("Não existe essa chave.\n");
		exit(0);
	}
	fseek(arquivo, sizeof(reg), 0);

	for(i=0; i<=x; i++){
		fread(registros, sizeof(reg), 4, arquivo);
	}

	for(i=0; i<4; i++){
		if(registros[i].chave == chave_ler)
			x = i;
	}

	printf("Aqui estão os 1008 outros:\n\n");

	for(i=0; i<1008; i++){
		printf("%c",registros[x].outros[i]);
	}

	printf("\n");
	fclose(arquivo);

}
