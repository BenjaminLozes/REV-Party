#ifndef CSVA_H
#define CSVA_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "squelette.h"

unsigned short int getNbRows(char* filename);
unsigned char getNbCol(char* filename);
unsigned char getOffset(char* filename);
void init_csv(t_mat_char_star_dyn *t_tabmots, char* filename, FILE *logfp);
void init_duel(t_mat_char_star_dyn *t_tabmots, t_mat_int_dyn *t_duel, char* filename, FILE *logfp);
void afficher_csv_array(t_mat_char_star_dyn *t_tabmots, FILE *logfp);
void fillCsvStruct(t_mat_char_star_dyn *t_tabmots, char* filename, FILE *logfp);
void fillDuelStruct(t_mat_char_star_dyn *t_tabmots, char* filename, t_mat_int_dyn *t_duel, FILE* logfp);
void analyseCsvFile(t_mat_char_star_dyn *t_tabmots, t_mat_int_dyn *t_duel, char* filename, FILE *logfp);

#endif