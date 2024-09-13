#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "data.h"

void initOut(struct Out *results) {
    results->totalAccess = 0;
    results->hitRatio = 0.0;
    results->totalMissRatio = 0.0;
    results->compulsoryMissRate = 0.0;
    results->capacityMissRate = 0.0;
    results->conflictMissRate = 0.0;
}

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
	config->fileName = argv[6];
	config->addresses = NULL;
	config->addressesCount = 0;
}

void addAddress(struct Data *config, uint32_t value) {
    if(!config->addressesCount){
        config->addressesCount++;
        config->addresses = (uint32_t *)malloc(config->addressesCount * sizeof(uint32_t));
        
        if (config->addresses == NULL){
            perror("Erro ao alocar memoria");
            exit(1);
        }
        
        config->addresses[config->addressesCount - 1] = value;
    } else {
        config->addressesCount++;
        config->addresses = (uint32_t *)realloc(config->addresses, config->addressesCount * sizeof(uint32_t));
        
        if (config->addresses == NULL){
            perror("Erro ao realocar memoria");
            exit(1);
        
        }
        config->addresses[config->addressesCount - 1] = value;
    }
}

void initCache(struct Cache *cache, int nsets) {
    cache->tags = (uint32_t *)malloc(nsets * sizeof(uint32_t));
    cache->vals = (uint32_t *)malloc(nsets * sizeof(uint32_t));

    for(int i=0; i<nsets; i++) {
        cache->tags[i] = -1;
        cache->vals[i] = 0;
    }

    return;
}