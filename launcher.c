#include "command.h"

int main(int argc, char *argv[]) {
    t_command cmdArray;
    init_t_command(&cmdArray);
    int valid = analyseCommande(cmdArray, argc, argv);
    if(valid==0)
        return 0;
    if(valid==1)
        afficher_t_command(&cmdArray);
}