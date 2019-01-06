#include "command.h"

int main(int argc, char *argv[]) {
    t_command cmdArray;
    init_t_command(&cmdArray);
    FILE* logfp = checkLog(&cmdArray, argc, argv);
    logfp = stdout;
    afficher_t_command(&cmdArray, logfp);
    if(analyseCommande(&cmdArray, argc, argv, logfp)==0) {
        fprintf(stdout, "exit(EXIT_FAILURE)");
        return 0;
    }
    fprintf(logfp, "\n------------- RETOUR DANS LAUNCHER.C -------------- \n\n");
    afficher_t_command(&cmdArray, logfp);

    return 1;
}