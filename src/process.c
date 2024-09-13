#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <arpa/inet.h>

#include "config/data.h"

void calcCache(struct Data *config) {
    struct Cache cache[config->assoc];

    for(int i=0; i < config->assoc; i++)
        initCache(&cache[0], config->nsets);

    int offset = (int)log2(config->bsize);
    int index = (int)log2(config->nsets);
    int tag = 32 - offset - index;

    int miss = 0, comp = 0, cap = 0, conf = 0, hit = 0;
    float fmiss, fcomp, fcap, fconf, fhit;

    for(int i = 0; i < config->addressesCount; i++) {
        uint32_t t = config->addresses[i] >> (offset + index);
        uint32_t id = (config->addresses[i] >> offset) & ((1 << index) - 1);

        if (cache->val[id] == 0){
            miss++;
            cache->val[id] = 1;
            cache->tag[id] = t;
        } else if (cache->tag[id] == t){
            hit++;
        } else {
            cache->tag[id] = t;
            cache->val[id] = 1;
            miss++;
        }
    }

    return;
}