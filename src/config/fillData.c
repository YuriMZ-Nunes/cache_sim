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
}