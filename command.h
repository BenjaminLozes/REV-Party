#ifndef COMMAND_H
#define COMMAND_H

#include "csvReading.h"

#define ARGMAX 10
#define LINKMAX 2

typedef struct command_options {
    int* argOccur;
    char** fileNames; // [CSV , TXT]
    t_csv csvFile;
} t_command;

void afficher_t_command(t_command* arrCmd);
void init_t_command(t_command* arrCmd);
int checkArgValid(t_command* arrCmd, int argc, char *argv[]);
int get_arg_index(char *arg);
int verifFollowing(char *argv[], int index, int indiceArg, t_command* arrCmd);
int parameterNeeded(int indice);
int analyseCommande(t_command cmdArray, int argc, char *argv[]);

#endif