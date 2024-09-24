#include <stdio.h>
#include <stdlib.h>

#include "../config/data.h"

void generateResult(struct Out *result, int flag) {
    if(flag == 0) {
		char pyComand[256];

		sprintf(pyComand, "python3 src/scripts/graphic.py %d %.2f %.2f %.2f %.2f %.2f\n",
				result->totalAccess,
				result->hitRatio,
				result->missRatio,
				result->compulsoryMissRatio,
				result->capacityMissRatio,
				result->conflictMissRatio);
		
		if(system(pyComand) == -1){
			printf("Erro ao rodar o script\n");
		} 
	} else {
		printf("%d %.4f %.4f %.4f %.4f %.4f", 
                result->totalAccess, 
                result->hitRatio, 
                result->missRatio, 
                result->compulsoryMissRatio, 
                result->capacityMissRatio, 
                result->conflictMissRatio);
		fflush(stdout);
	}
}