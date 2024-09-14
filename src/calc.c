#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <arpa/inet.h>

#include "config/data.h"


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

void calcCache(struct Data *config, struct Cache *cache, struct Out *out) {
    srand(time(NULL));
    for(int i = 0; i < config->addressesCount; i++) {
        uint32_t tag = config->addresses[i] >> (cache->offset + cache->index);
        uint32_t index = (config->addresses[i] >> cache->offset) & ((1 << cache->index) - 1);
        int changeIndex;
        int find = findValue(cache, config->assoc, tag, index);
        int empty = getEmpty(cache, config->assoc, index);

        //TODO: aplicar tipos de miss
        if (find >= 0) {
            out->hitRatio++;
        } else if (config->assoc == 1) {
            cache[0].vals[index] = 1;
            cache[0].tags[index] = tag;
            out->totalMissRatio++;
        } else if (empty < 0){
            changeIndex = rand() % config->assoc;
            cache[changeIndex].tags[index] = tag;
            cache[changeIndex].vals[index] = 1;
            out->totalMissRatio++;
        } else {
            cache[empty].tags[index] = tag;
            cache[empty].vals[index] = 1;
            out->totalMissRatio++;
        }
    }

    return;
}