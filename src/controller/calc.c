#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "../config/data.h"

int getEmpty(struct Cache *cache, int assoc, uint32_t index);
int findValue (struct Cache *cache, int assoc, uint32_t tag, uint32_t index);
int capacity (struct Cache *cache, int assoc, int nsets);

void getHitMiss(struct Data *config, struct Cache *cache, struct Stack *stack,struct Result *result) {
    srand(time(NULL));
    for(int i = 0; i < config->addressesCount; i++) {
        uint32_t tag = config->addresses[i] >> (cache->offset + cache->index);
        uint32_t index = (config->addresses[i] >> cache->offset) & ((1 << cache->index) - 1);

        int changeIndex;
        int find = findValue(cache, config->assoc, tag, index);
        int empty = getEmpty(cache, config->assoc, index);

        if (find >= 0) {
            result->hitRatio++;
            updateLRUpriority(stack, find, index, config->assoc);
        } else if (config->assoc == 1) {
            if (cache[0].vals[index] == 0)
                result->compulsoryMissRatio++;
            else
                result->conflictMissRatio++;

            cache[0].vals[index] = 1;
            cache[0].tags[index] = tag;
            result->missRatio++;
        } else if (empty < 0){
            
            if (strcmp(config->subst, "R") == 0)
                changeIndex = rand() % config->assoc;
            else if (strcmp(config->subst, "F") == 0)
                changeIndex = getStackFIFO(stack, index, config->assoc);
            else if (strcmp(config->subst, "L") == 0)
                changeIndex = getStackLRU(stack, index, config->assoc);

            if (capacity(cache, config->assoc, config->nsets))
                result->conflictMissRatio++;
            else
                result->capacityMissRatio++;

            cache[changeIndex].tags[index] = tag;
            cache[changeIndex].vals[index] = 1;
            result->missRatio++;
        } else {

            addToStack(stack, empty, index, config->assoc);

            cache[empty].tags[index] = tag;
            cache[empty].vals[index] = 1;

            result->compulsoryMissRatio++;
            result->missRatio++;
        }
    }
    result->totalAccess = config->addressesCount;
    result->capacityMissRatio = result->capacityMissRatio / result->missRatio;
    result->compulsoryMissRatio = result->compulsoryMissRatio / result->missRatio;
    result->conflictMissRatio = result->conflictMissRatio / result->missRatio;

    result->hitRatio = result->hitRatio / config->addressesCount;
    result->missRatio = 1 - result->hitRatio;
}

int getEmpty(struct Cache *cache, int assoc, uint32_t index) {
    for(int i=0; i < assoc; i++) {
        if (cache[i].vals[index] == 0)
            return i;
    }
    return -1;
}

int findValue (struct Cache *cache, int assoc, uint32_t tag, uint32_t index) {
    for (int i=0; i < assoc; i++) {
        if (cache[i].tags[index] == tag && cache[i].vals[index] == 1)
            return i;
    }
    return -1;
}

int capacity (struct Cache *cache, int assoc, int nsets) {
    for (int i=0; i < assoc; i++) {
        for (int index=0; index < nsets; index++){
            if (cache[i].vals[index] == 0)
                return 1;
        }
    }
    return 0;
}