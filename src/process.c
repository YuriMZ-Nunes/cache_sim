#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <arpa/inet.h>

#include "config/data.h"

void calcCache(struct Data *config, struct Cache *cache, struct Out *out) {
    for(int i = 0; i < config->addressesCount; i++) {
        uint32_t t = config->addresses[i] >> (cache->offset + cache->index);
        uint32_t id = (config->addresses[i] >> cache->offset) & ((1 << cache->index) - 1);

        if (cache->vals[id] == 0){
            out->totalMissRatio++;
            cache->vals[id] = 1;
            cache->tags[id] = t;
        } else if (cache->tags[id] == t){
            out->hitRatio++;
        } else {
            cache->tags[id] = t;
            cache->vals[id] = 1;
            out->totalMissRatio++;
        }
    }
}

void initCalc(struct Data *config) {
    struct Out out;
    initOut(&out);

    struct Cache cache;
    for(int i=0; i < config->assoc; i++)
        initCache(&cache, config->nsets);

    cache.offset = (int)log2(config->bsize);
    cache.index = (int)log2(config->nsets);
    cache.tag = 32 - cache.offset - cache.index;

    calcCache(config, &cache, &out);
    return;
}