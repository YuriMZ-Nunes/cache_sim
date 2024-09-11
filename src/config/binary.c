#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <endian.h>

#include "data.h"

int readBinary(struct Data *config) {
    char* file = config->arquivoEntrada;
    FILE *binary;
    unsigned char buffer[4];
    int num = 0;
    char local[100];

    snprintf(local, sizeof(local), "assets/%s", file);

    binary = fopen(local, "rb");

    if (binary == NULL)
        return 0;

    while ((fread(&buffer, sizeof(uint32_t), 1, binary)) != 0) {
        int value = (int)buffer[3] | (int)buffer[2]<<8 | (int)buffer[1]<<16 | (int)buffer[0]<<24;
        addAddress(config, value);
    }

    return 1;
}