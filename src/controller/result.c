#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../config/data.h"

void callPython(struct Result *result, char* subst) {

	char pyComand[256];

	sprintf(pyComand, "python3 src/scripts/graphic.py %s", subst);

	if(system(pyComand) == -1){
		printf("Erro ao rodar o script\n");
	} 
}

void onlyPrint(struct Result *result) {
	printf("%d %.4f %.4f %.4f %.4f %.4f", 
			result->totalAccess, 
			result->hitRatio, 
			result->missRatio, 
			result->compulsoryMissRatio, 
			result->capacityMissRatio, 
			result->conflictMissRatio);
		fflush(stdout);
}

void insertCSV(struct Result *result) {
	FILE *file;

	file = fopen("src/scripts/results.csv", "a");

	fprintf(file, "%d %.4f %.4f %.4f %.4f %.4f\n",
				result->totalAccess, 
                result->hitRatio, 
                result->missRatio, 
                result->compulsoryMissRatio, 
                result->capacityMissRatio, 
                result->conflictMissRatio);

	fclose(file);
}