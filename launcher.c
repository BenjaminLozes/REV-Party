#include "utils_scrutin.h"

int main(int argc, char *argv[]) {
    t_command cmdArray;
    init_t_command(&cmdArray);
    FILE* logfp = checkLog(&cmdArray, argc, argv);
    if(analyseCommande(&cmdArray, argc, argv, logfp)==0) {
        afficher_t_command(&cmdArray, logfp);
        fprintf(stderr, "exit(EXIT_FAILURE)");
        return 0;
    }
    init_candidats(&cmdArray, logfp); 
    afficher_t_command(&cmdArray, logfp);
    fprintf(logfp, "OK----------\n");
    s_resultats res_panel;
    res_panel.candidat = "Candidat X";
    res_panel.nbCand = cmdArray.candidats.dim;
    res_panel.nbVtants  = cmdArray.t_duel.nbRows;
    bool voteBool;
    fprintf(logfp, "------------------ IN SIMULATION --------------\n");
    switch(cmdArray.methodNb) {
        case 9:
            voteBool = uninominal(&cmdArray, 2, &res_panel, logfp);
            if(voteBool)
                fprintf(stdout, "Mode de scrutin : uninominal à deux tours, %d candidats, %d votants, vainqueur = %s, score = %d \n", res_panel.nbCand, res_panel.nbVtants, res_panel.candidat, res_panel.prctScore);
            else
                fprintf(stderr, "exit(EXIT_FAILURE)");
            break;
        case 8:
            voteBool = uninominal(&cmdArray, 1, &res_panel, logfp);
            if(voteBool)
                fprintf(stdout, "Mode de scrutin : uninominal à un tour, %d candidats, %d votants, vainqueur = %s, score = %d \n", res_panel.nbCand, res_panel.nbVtants, res_panel.candidat, res_panel.prctScore);
            else
                fprintf(stderr, "exit(EXIT_FAILURE)");
            break;
        case 7:  // VOTE ALTERNATIF
            voteBool = alternatif(&cmdArray, &res_panel, logfp);
            if(voteBool)
                fprintf(stdout, "Mode de scrutin : vote alternatif, %d candidats, %d votants, vainqueur = %s \n", res_panel.nbCand, res_panel.nbVtants, res_panel.candidat);
            else
                fprintf(stderr, "exit(EXIT_FAILURE)");
            break;
        case 5:
            fprintf(stdout, "CONDORCET NON CODÉ \n");
            break;
        case 4:
            fprintf(stdout, "CONDORCET NON CODÉ \n");
            break;
        case 3:
            fprintf(stdout, "CONDORCET NON CODÉ \n");
            break;
        case 0:
            if(cmdArray.argOccur[1]>0) {
                voteBool = uninominal(&cmdArray, 2, &res_panel, logfp);
                if(voteBool)
                    fprintf(stdout, "Mode de scrutin : uninominal à deux tours, %d candidats, %d votants, vainqueur = %s, score = %d %%\n", res_panel.nbCand, res_panel.nbVtants, res_panel.candidat, res_panel.prctScore);
                else
                    fprintf(stderr, "exit(EXIT_FAILURE)");
                voteBool = uninominal(&cmdArray, 1, &res_panel, logfp);
                if(voteBool)
                    fprintf(stdout, "Mode de scrutin : uninominal à un tour, %d candidats, %d votants, vainqueur = %s, score = %d %%\n", res_panel.nbCand, res_panel.nbVtants, res_panel.candidat, res_panel.prctScore);
                else
                    fprintf(stderr, "exit(EXIT_FAILURE)");
                voteBool = alternatif(&cmdArray, &res_panel, logfp);
                if(voteBool)
                    fprintf(stdout, "Mode de scrutin : vote alternatif, %d candidats, %d votants, vainqueur = %s \n", res_panel.nbCand, res_panel.nbVtants, res_panel.candidat);
                else
                    fprintf(stderr, "exit(EXIT_FAILURE)");
                break;    
            }
            else
                fprintf(stdout, "CONDORCETS NON CODÉS \n");

        default:

            break;
    }
    return 1;
}