#include "command.h"

int main(int argc, char *argv[]) {
    t_command cmdArray;
    init_t_command(&cmdArray);
    FILE* logfp = checkLog(&cmdArray, argc, argv);
    if(analyseCommande(&cmdArray, argc, argv, logfp)==0) {
        fprintf(logfp, "ERREUR ENCULER\n");
        return 0;
    }
    afficher_t_command(&cmdArray, logfp);
    return 1;
}