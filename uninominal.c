#include "utils_scrutin.h"

bool uninominal(t_command* cmdArray, int nbTour, s_resultats *res_panel, FILE* logfp) {
    afficher_t_command(cmdArray, logfp);
    fprintf(logfp, "INSIDE UNINOMINAL \n");
    t_tab_int_dyn index;
    index.dim = 2;
    init_int_tab(&index, logfp);
    fprintf(logfp, "\nINDEX:\n");
    affiche_t_tab_int_dyn(index, logfp);
    t_tab_int_dyn comptes;
    comptes.dim = cmdArray->t_duel.nbCol;
    init_int_tab(&comptes, logfp);
    fprintf(logfp, "\nCOMPTES:\n");
    affiche_t_tab_int_dyn(comptes, logfp);
    fprintf(logfp, "\nDans duel col : %d \nDans duel lign: %d \n", cmdArray->t_duel.nbCol, cmdArray->t_duel.nbRows);
    fprintf(logfp, "\nDUELS:\n");
    affiche_t_mat_int_dyn(cmdArray->t_duel, logfp);
    comptVotes(&cmdArray->t_duel, &comptes, logfp);
    fprintf(logfp, "\nCOMPTES:\n");
    affiche_t_tab_int_dyn(comptes, logfp);
    fprintf(logfp, "\n");
    get_max_index(&comptes, &index, logfp);
    if(isDoublon(&comptes, index.tab[0]) || isDoublon(&comptes, index.tab[1])) { // Verification que les max renvoyés sont uniques
        fprintf(logfp, "DOUBLON !\n");
        return 0;
    }
    fprintf(logfp, "INDEX << : [ %d , %d ] \n", index.tab[0], index.tab[1]);
    fprintf(logfp, "\n");
    //for(int w=0; w<cmdArray->candidats.dim; w++)
    //    fprintf(logfp, "--> %s \n", cmdArray->candidats.tab[w]);
    if(nbTour == 2) {
        int colNumber = cmdArray->t_duel.nbCol;
        for(int candidat=0; candidat < colNumber; candidat++) {
            if(candidat != index.tab[0] && candidat != index.tab[1])
                redistribution(&cmdArray->t_duel, candidat, logfp);
        }
        affiche_t_mat_int_dyn(cmdArray->t_duel, logfp);
        return(uninominal(cmdArray, 1, res_panel, logfp));
    }
    double score = (double) comptes.tab[index.tab[0]];
    score /= comptes.tab[index.tab[0]]+comptes.tab[index.tab[1]];
    score *=100;
    score+=1;
    res_panel->prctScore = (int) score;
    res_panel->candidat = cmdArray->candidats.tab[index.tab[0]];
    return 1;
}