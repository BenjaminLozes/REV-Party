#ifndef COMMAND_H
#define COMMAND_H

#include "csvanalyse.h"

#define ARGMAX 10
#define LINKMAX 2

typedef struct command_options {
    bool* argOccur;
    char** fileNames; // [CSV , TXT]
    t_mat_char_star_dyn csvFile;
    t_mat_int_dyn t_duel;
    bool log;
    unsigned short int methodNb;
} t_command;

bool verifMethod(char* arg);
bool correct_file(char* filename, FILE* logfp);
void afficher_t_command(t_command* arrCmd, FILE* logfp);
void init_t_command(t_command* arrCmd);
int get_arg_index(char *arg);
bool verifFile(char *argv[], int index, int indiceArg, t_command* arrCmd, FILE* logfp);
unsigned char parameterNeeded(int indice);
FILE* checkLog(t_command* cmdArray, int argc, char *argv[]);
bool analyseCommande(t_command* cmdArray, int argc, char *argv[], FILE* logfp);

#endif