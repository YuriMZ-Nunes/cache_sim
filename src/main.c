#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "config/data.h"
#include "config/binary.h"
#include "calc.h"

int main(int argc, char *argv[])
{
	struct Data config;
	fillData(&config, argc, argv);

	struct Cache cache;
    for(int i=0; i < config.assoc; i++)
        initCache(&cache, config.nsets); 

    cache.offset = (int)log2(config.bsize);
    cache.index = (int)log2(config.nsets);
    cache.tag = 32 - cache.offset - cache.index;

	struct Out result;
	initOut(&result);

	if(readBinary(&config))
		printf("Arquivo lido com sucesso, possui %d enderecos\n", config.addressesCount);
	else
		perror("Problema ao ler arquivo");

	calcCache(&config, &cache, &result);

    return 0;
}
