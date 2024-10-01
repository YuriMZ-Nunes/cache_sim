#ifndef RESULT_H
#define RESULT_H
#include "../config/data.h"

void callPython(struct Result *result, char* subst);

void onlyPrint(struct Result *result);

void insertCSV(struct Result *result);

#endif