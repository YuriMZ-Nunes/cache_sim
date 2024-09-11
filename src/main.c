#include <stdio.h>
#include <stdlib.h>

#include "config/data.h"
#include "config/binary.h"

int main(int argc, char *argv[])
{
	struct Data config;

	fillData(&config, argc, argv);

	if(readBinary(&config))
		printf("Arquivo lido com sucesso, possui %d enderecos\n", config.qtdEnderecos);
	else
		perror("Problema ao ler arquivo");

    return 0;
}
