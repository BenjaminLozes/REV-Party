#ifndef COMMAND_H
#define COMMAND_H
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct command_options {
    int* argOccur;
    FILE* filesLink;
} t_command;

#endif