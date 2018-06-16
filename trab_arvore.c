#include <stdlib.h>
#include <stdio.h>
#include "avl.c"

typedef struct registro{
	unsigned long chave;//Campo chave Valor nao se repete.
	unsigned long naochave;//Campo qualquer. Valor pode repetir.
	unsigned char outros[1008];//outros campos: 1008 bytes (dados)
}reg;


int main(){
	reg registros[4];
	int i,x;
	i=0;
	FILE *arquivo;
	arquivo = fopen("base.bin", "rb");
	for(x=0;x<1000000;x++){
		fread(registros, sizeof(reg), 4, arquivo);
		fseek(arquivo, sizeof(reg), SEEK_CUR); //atual
		while(i<4 && !feof(arquivo)){
			printf("%lu,%lu \n", registros[i].chave, registros[i].naochave);
			i++;
		}
		i=0;
	}

	// fread(registros, sizeof(reg),4, arquivo);

	fclose(arquivo);

	return 0;


}
