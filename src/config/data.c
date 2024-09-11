#include <stdio.h>
#include <stdlib.h>

#include "data.h"

void fillData(struct Data *config, int argc, char *argv[]) {
	if (argc != 7) {
		printf("Numero de argumentos incorreto. Utilize:\n");
		printf("./cache_simulator <nsets> <bsize> <assoc> <substituição> <flag_saida> arquivo_de_entrada\n");
		exit(EXIT_FAILURE);
	}

	config->nsets = atoi(argv[1]);
	config->bsize = atoi(argv[2]);
	config->assoc = atoi(argv[3]);
	config->subst = argv[4];
	config->flagOut = atoi(argv[5]);
	config->arquivoEntrada = argv[6];
	config->enderecos = NULL;
	config->qtdEnderecos = 0;
}

void addAddress(struct Data *config, int value) {
    if(!config->qtdEnderecos){
        config->qtdEnderecos++;
        config->enderecos = (int *)malloc(config->qtdEnderecos * sizeof(int));
        
        if (config->enderecos == NULL){
            perror("Erro ao alocar memoria");
            exit(1);
        }
        
        config->enderecos[config->qtdEnderecos - 1] = value;
    } else {
        config->qtdEnderecos++;
        config->enderecos = (int *)realloc(config->enderecos, config->qtdEnderecos * sizeof(int));
        
        if (config->enderecos == NULL){
            perror("Erro ao realocar memoria");
            exit(1);
        
        }
        config->enderecos[config->qtdEnderecos - 1] = value;
    }
}