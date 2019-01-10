#include "utils_scrutin.h"

bool alternatif(t_command* cmdArray, s_resultats *res_panel, FILE* logfp) {
    t_tab_int_dyn index;
    index.dim = 2;
    init_int_tab(&index, logfp);
    affiche_t_tab_int_dyn(index, logfp);
    fprintf(logfp, "INSIDE \n");
    t_tab_int_dyn comptes;
    comptes.dim = cmdArray->t_duel.nbCol;
    init_int_tab(&comptes, logfp);
    affiche_t_tab_int_dyn(comptes, logfp);
    fprintf(logfp, "col : %d \nlign: %d \n", cmdArray->t_duel.nbCol, cmdArray->t_duel.nbRows);
    affiche_t_mat_int_dyn(cmdArray->t_duel, logfp);
    comptVotes(&cmdArray->t_duel, &comptes, logfp);
    affiche_t_tab_int_dyn(comptes, logfp);
    get_max_index(&comptes, &index, logfp);
    if(isDoublon(&comptes, index.tab[0])) { // Verification que les max renvoyés sont uniques
        fprintf(logfp, "DOUBLON !\n");
        return 0;
    }
    fprintf(logfp, "INDEX << : compte[ %d ] \n", index.tab[0]);
    fprintf(logfp, "\n");
    if(res_panel->nbCand==1) { // condition d'arret <=> 1 seul candidat restant
        res_panel->candidat = cmdArray->candidats.tab[index.tab[0]];
        return 1;
    }
    for(int w=0; w<cmdArray->candidats.dim; w++)
        fprintf(logfp, "--> %s \n", cmdArray->candidats.tab[w]);
    redistribution(&cmdArray->t_duel, index.tab[0], logfp);
    res_panel->nbCand--;
    return alternatif(cmdArray, res_panel, logfp);
}
