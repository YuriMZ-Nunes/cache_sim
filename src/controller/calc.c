#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#include "../config/data.h"
#include "result.h"

int getEmpty(struct Cache *cache, int assoc, uint32_t index);
int findValue (struct Cache *cache, int assoc, uint32_t tag, uint32_t index);
int capacity (struct Cache *cache, int assoc, int nsets);

/**
 * Percorre a cache e obtem os valores de hit e miss, classificando os tipos de miss
 * @param config Ponteiro das configurações da cache (struct Data)
 * @param cache Ponteiro da cache (struct Cache)
 * @param result Ponteiro dos resultados da cache (struct Out)
 */
void getHitMiss(struct Data *config, struct Cache *cache, struct Out *result) {
    srand(time(NULL));
    for(int i = 0; i < config->addressesCount; i++) {
        uint32_t tag = config->addresses[i] >> (cache->offset + cache->index);
        uint32_t index = (config->addresses[i] >> cache->offset) & ((1 << cache->index) - 1);
        int changeIndex;
        int find = findValue(cache, config->assoc, tag, index);
        int empty = getEmpty(cache, config->assoc, index);

        if (find >= 0) {
            result->hitRatio++;
        } else if (config->assoc == 1) {
            if (cache[0].vals[index] == 0)
                result->compulsoryMissRate++;
            else
                result->conflictMissRate++;

            cache[0].vals[index] = 1;
            cache[0].tags[index] = tag;
            result->totalMissRatio++;
        } else if (empty < 0){
            changeIndex = rand() % config->assoc;

            if (capacity(cache, config->assoc, config->nsets))
                result->conflictMissRate++;
            else
                result->capacityMissRate++;

            cache[changeIndex].tags[index] = tag;
            cache[changeIndex].vals[index] = 1;
            result->totalMissRatio++;
        } else {
            cache[empty].tags[index] = tag;
            cache[empty].vals[index] = 1;

            result->compulsoryMissRate++;
            result->totalMissRatio++;
        }
    }
    result->totalAccess = config->addressesCount;
    result->capacityMissRate = result->capacityMissRate / result->totalMissRatio;
    result->compulsoryMissRate = result->compulsoryMissRate / result->totalMissRatio;
    result->conflictMissRate = result->conflictMissRate / result->totalMissRatio;

    result->hitRatio = result->hitRatio / config->addressesCount;
    result->totalMissRatio = 1 - result->hitRatio;

    generateResult(result, config->flagOut);
}


/**
 * Verifica se o conjunto possui uma posição vazia
 * @param cache Ponteiro da cache (struct Cache)
 * @param assoc Associatividade da cache
 * @param index Valor índice
 * @return Retorna o conjunto caso que possui uma posição vazia, caso não tenha posição vazia, retorna -1
 */
int getEmpty(struct Cache *cache, int assoc, uint32_t index) {
    for(int i=0; i < assoc; i++) {
        if (cache[i].vals[index] == 0)
            return i;
    }
    return -1;
}

/**
 * Procura no indice calcula se há o valor tag
 * @param cache Ponteiro da cache (struct Cache)
 * @param assoc Associatividade da cache
 * @param tag Valor tag
 * @param index Valor índice
 * @return Retorna o conjunto caso que foi encontrado a tag, caso não encontre retorna -1
 */
int findValue (struct Cache *cache, int assoc, uint32_t tag, uint32_t index) {
    for (int i=0; i < assoc; i++) {
        if (cache[i].tags[index] == tag && cache[i].vals[index] == 1)
            return i;
    }
    return -1;
}

/**
 * Verifica se há alguma posição vazia na cache para classificar o miss de capacidade
 * @param cache Ponteiro da cache (struct Cache)
 * @param assoc Associatividade da cache
 * @param nsets Numero de sets da cache
 * @return Retorna 1 caso encontre alguma posição vazia, e 0 caso não encontre 
 */
int capacity (struct Cache *cache, int assoc, int nsets) {
    for (int i=0; i < assoc; i++) {
        for (int index=0; index < nsets; index++){
            if (cache[i].vals[index] == 0)
                return 1;
        }
    }
    return 0;
}