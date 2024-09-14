#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "data.h"

/**
 * Inicializa a struct de resultados com 0
 * @param result Ponteiro dos resultados da cache (struct Out)
 */
void initOut(struct Out *result) {
    result->totalAccess = 0;
    result->hitRatio = 0.0;
    result->totalMissRatio = 0.0;
    result->compulsoryMissRate = 0.0;
    result->capacityMissRate = 0.0;
    result->conflictMissRate = 0.0;
}

/**
 * Insere os argumentos passados via linha de comando na struct de configuração da cache
 * @param config Ponteiro das configurações da cache (struct Data)
 * @param argc Quantidade de argumentos passados
 * @param argv Vetor de strings (char* []) com os argumentos
 */
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

/**
 * Aloca espaço na memória para o endereço e insere nas configurações da cache
 * @param config Ponteiro das configurações da cache (struct Data)
 * @param value Endereço de memória
 */
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

/**
 * Inicializa os cache alocando espaço para as tags e bits de validade, 
 * preenchendo as tags com o valor maximo do tipo uint32_t (4294967295) e
 * preenchendo os bits de validade com 0
 * @param cache Ponteiro da cache (struct Cache)
 * @param nsets Numeros de sets da cache
 */
void initCache(struct Cache *cache, int nsets) {
    cache->tags = (uint32_t *)malloc(nsets * sizeof(uint32_t)); 
    cache->vals = (uint32_t *)malloc(nsets * sizeof(uint32_t));

    for(int i=0; i<nsets; i++) {
        cache->tags[i] = -1; // max
        cache->vals[i] = 0;
    }
}