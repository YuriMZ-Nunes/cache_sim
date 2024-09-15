#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "config/data.h"
#include "config/binary.h"
#include "controller/calc.h"

int main(int argc, char *argv[])
{
	struct Data config;
	fillData(&config, argc, argv);

	struct Cache *cache = (struct Cache *)malloc(config.assoc * sizeof(struct Cache));

    for(int i=0; i < config.assoc; i++) {
		initCache(&cache[i], config.nsets);
		cache[i].offset = (int)log2(config.bsize);
		cache[i].index = (int)log2(config.nsets);
		cache[i].tag = 32 - cache[i].offset - cache[i].index;
	}
        
	struct Out result;
	initOut(&result);

	if(!readBinary(&config)){
		perror("Problema ao ler arquivo\n");
		return 1;
	}

	getHitMiss(&config, cache, &result);

    return 0;
}
