#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "data.h"

void initOut(struct Result *result) {
    result->totalAccess = 0;
    result->hitRatio = 0.0;
    result->missRatio = 0.0;
    result->compulsoryMissRatio = 0.0;
    result->capacityMissRatio = 0.0;
    result->conflictMissRatio = 0.0;
}

void restartStack(struct Stack *stack, int nsets, int assoc) {
    for (int i=0; i<nsets; i++) {
        for (int j=0; j<assoc; j++) {
            stack->fifo[i][j] = -1;
            stack->lru[i][j] = -1;
        }
    }
}

void restartCache(struct Cache *cache, int nsets) {
    for(int j=0; j<nsets; j++) {
        cache->tags[j] = -1;
        cache->vals[j] = 0;
    }

    cache->index = 0;
    cache->offset = 0;
    cache->index = 0;
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
}

void initStack(struct Stack *stack, int nsets, int assoc) {
    stack->fifo = (uint32_t **)malloc(nsets * sizeof(uint32_t *));
    stack->lru = (uint32_t **)malloc(nsets * sizeof(uint32_t *));

    for (int i=0; i<nsets; i++){
        stack->fifo[i] = (uint32_t *)malloc(assoc * sizeof(uint32_t));
        stack->lru[i] = (uint32_t *)malloc(assoc * sizeof(uint32_t));
    }

    for (int i=0; i<nsets; i++) {
        for (int j=0; j<assoc; j++) {
            stack->fifo[i][j] = -1;
            stack->lru[i][j] = -1;
        }
    }
}

void addToStack(struct Stack *stack, uint32_t cacheIndex, uint32_t index, int assoc) {
    int i = 0;
    int j = 0;

    for (i; i < assoc; i++){
        if(stack->fifo[index][i] == -1)
            break;
    }

    for (j; j < assoc; j++){
        if(stack->lru[index][j] == -1)
            break;
    }

    stack->fifo[index][i] = cacheIndex; 
    stack->lru[index][j] = cacheIndex; 
}

void updateLRUpriority(struct Stack *stack, int hitCache, uint32_t index, int assoc) {
    uint32_t cacheIndex = stack->lru[index][hitCache];
    int endIndex = 0;
    int findIndex;

    for (endIndex; endIndex < assoc; endIndex++){
        if (stack->lru[index][endIndex] == cacheIndex)
            findIndex = endIndex;
        if (stack->lru[index][endIndex] == -1)
            break;
    }


    for (int i = findIndex; i < endIndex - 1; i++) {
        stack->lru[index][i] = stack->lru[index][i + 1];
    }

    stack->lru[index][endIndex - 1] = cacheIndex;
}

uint32_t getStackFIFO(struct Stack *stack, uint32_t index, int assoc) {
    uint32_t cacheIndex = stack->fifo[index][0];

    int i = 0;
    for (i; i < assoc - 1; i++) {
        stack->fifo[index][i] = stack->fifo[index][i + 1];
    }

    stack->fifo[index][i] = cacheIndex;
    return cacheIndex;
}

uint32_t getStackLRU(struct Stack *stack, uint32_t index, int assoc) {
    uint32_t cacheIndex = stack->lru[index][0];

    int i = 0;
    for (i; i < assoc - 1; i++) {
        stack->lru[index][i] = stack->lru[index][i + 1];
    }

    stack->lru[index][i] = cacheIndex;
    return cacheIndex;
}