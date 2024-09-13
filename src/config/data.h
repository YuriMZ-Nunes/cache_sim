#ifndef DATA_H
#define DATA_H

#include <stdint.h>
struct Data {
	int nsets;
	int bsize;
	int assoc;
	char* subst;
	int flagOut;
	char* fileName;
	uint32_t* addresses;
	int addressesCount;
};

struct Cache {
	uint32_t* tag;
	uint32_t* val;
};

struct Out {
	int totalAccess;
	float hitRatio;
	float totalMissRatio;
	float compulsoryMissRate;
	float capacityMissRate;
	float conflictMissRate;
};

void fillData(struct Data *config, int argc, char *argv[]);

void addAddress(struct Data *config, uint32_t value);

void initCache(struct Cache *cache, int nsets);

void initOut(struct Out *results);

#endif