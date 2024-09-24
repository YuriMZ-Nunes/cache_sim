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

struct Stack{
	uint32_t** fifo;
	uint32_t** lru;
};

struct Cache {
	int offset;
	int index;
	int tag;
	uint32_t* tags;
	uint32_t* vals;
};


struct Out {
	int totalAccess;
	float hitRatio;
	float missRatio;
	float compulsoryMissRatio;
	float capacityMissRatio;
	float conflictMissRatio;
};

void fillData(struct Data *config, int argc, char *argv[]);

void addAddress(struct Data *config, uint32_t value);

void initCache(struct Cache *cache, int nsets);

void initOut(struct Out *results);

void addToStack(struct Stack *stack, uint32_t cacheIndex, uint32_t index, int assoc);

void initStack(struct Stack *stack, int nsets, int assoc);

uint32_t getStack(struct Stack *stack, uint32_t index, int assoc);

#endif