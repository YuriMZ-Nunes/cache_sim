#ifndef DATA_H
#define DATA_H

struct Data {
	int nsets;
	int bsize;
	int assoc;
	char *subst;
	int flagOut;
	char *arquivoEntrada;
};

void fillData(struct Data *config, int argc, char *argv[]);

#endif