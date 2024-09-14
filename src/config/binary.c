#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "data.h"

/**
 * Acessa o arquivo binario e armazena os endereços nas configurações da cache
 * @param config Ponteiro das configurações da cache (struct Data)
 * @return Retorna 1 caso não aconteça erros na leitura e armazenamento dos dados do arquivo binario, retorna 0 caso ocorra algum erro
 */
int readBinary(struct Data *config) {
    char* path = "assets/";
    char* file = config->fileName;
    char* fullPath = (char *)malloc(strlen(path) + strlen(file) + 1);
    strcpy(fullPath, path);
    strcat(fullPath, file);

    FILE *binary;
    uint32_t line;
    
    binary = fopen(fullPath, "rb");

    if (binary == NULL)
        return 0;

    while ((fread(&line, sizeof(uint32_t), 1, binary)) != 0) {
        uint32_t value = ntohl(line);
        addAddress(config, value);
    }

    return 1;
}