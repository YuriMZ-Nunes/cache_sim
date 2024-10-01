#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "config/data.h"
#include "config/binary.h"
#include "controller/calc.h"
#include "controller/result.h"

int main(int argc, char *argv[]){

	char *subs[] = {"R", "L", "F"};
	remove("src/scripts/results.csv");

	struct Data config;
	fillData(&config, argc, argv);

	struct Cache *cache = (struct Cache *)malloc(config.assoc * sizeof(struct Cache));
	struct Stack stack;

	struct Result result;
	initOut(&result);

	if(!readBinary(&config)){
		perror("Problema ao ler arquivo\n");
		return 1;
	}

	if (strcmp(config.subst, "M") == 0){
		for (int i=0; i < 3; i++) {
			config.subst = subs[i];
			initStack(&stack, config.nsets, config.assoc);

			for(int j=0; j < config.assoc; j++) {
				initCache(&cache[j], config.nsets);
				cache[j].offset = (int)log2(config.bsize);
				cache[j].index = (int)log2(config.nsets);
				cache[j].tag = 32 - cache[j].offset - cache[j].index;
			}

			getHitMiss(&config, cache, &stack, &result);

			insertCSV(&result);

			restartStack(&stack, config.nsets, config.assoc);

			for(int j=0; j < config.assoc; j++) {
				restartCache(&cache[j], config.nsets);
			}
		}
		config.subst = "M";
	} else {
		initStack(&stack, config.nsets, config.assoc);

		for(int i=0; i < config.assoc; i++) {
			initCache(&cache[i], config.nsets);
			cache[i].offset = (int)log2(config.bsize);
			cache[i].index = (int)log2(config.nsets);
			cache[i].tag = 32 - cache[i].offset - cache[i].index;
		}

		getHitMiss(&config, cache, &stack, &result);

		insertCSV(&result);
	}

	if (config.flagOut == 0) {
		onlyPrint(&result);
	} else {
		callPython(&result, config.subst);
	}

    return 0;
}
