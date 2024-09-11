#ifndef DATA_H
#define DATA_H

struct Data {
	int nsets;
	int bsize;
	int assoc;
	char *subst;
	int flagOut;
	char *arquivoEntrada;
	int* enderecos;
	int qtdEnderecos;
};



void fillData(struct Data *config, int argc, char *argv[]);

void addAddress(struct Data *config, int value);

#endif