#include <stdio.h>
#include <stdlib.h>

#include "config/data.h"
#include "config/binary.h"
#include "process.h"

int main(int argc, char *argv[])
{
	struct Data config;
	fillData(&config, argc, argv);

	struct Out result;
	initOut(&result);

	if(readBinary(&config))
		printf("Arquivo lido com sucesso, possui %d enderecos\n", config.addressesCount);
	else
		perror("Problema ao ler arquivo");

	calcCache(&config);

    return 0;
}
