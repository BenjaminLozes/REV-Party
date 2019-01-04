#ifndef CSV_H
#define CSV_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct csv_file {
    char* filename;
    unsigned int lign;
    unsigned int colonne;
    char*** csvArray;
} t_csv;

void afficher_csv_array(t_csv* csvFile);
void init_t_csv(t_csv* csvFile, char* name);
int fillCsvArray(t_csv* csvFile, char* filename);

#endif