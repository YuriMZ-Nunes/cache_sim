#include <stdio.h>
#include "data.h" 

void process(struct Data *config) {
    printf("Processando dados da struct:\n");
    printf("nsets: %d\n", config->nsets);
    printf("bsize: %d\n", config->bsize);
    printf("assoc: %d\n", config->assoc);
    printf("Substituição: %s\n", config->subst);
    printf("Flag de saída: %d\n", config->flagOut);
    printf("Arquivo de entrada: %s\n", config->arquivoEntrada);
}