#include <stdio.h>
#include <stdlib.h>

#include "config/data.h"

extern void processar_dados(struct Data *config);

int main(int argc, char *argv[])
{
	struct Data config;

	fillData(&config, argc, argv);

	process(&config);

	

    return 0;
}
