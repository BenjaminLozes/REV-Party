#ifndef UTILS_SCRUTIN_H
#define UTILS_SCRUTIN_H

#include "utils_sd.h"

typedef struct s_resultats {
    int prctScore;
    int nbVtants;
    int nbCand;
    char* candidat;
} s_resultats;

bool isDoublon(t_tab_int_dyn *comptes, int indMax);
void init_int_tab(t_tab_int_dyn *lst, FILE* logfp);
void get_max_index(t_tab_int_dyn *comptes, t_tab_int_dyn *index, FILE* logfp);
void afficher_decompte(t_tab_int_dyn *comptes, FILE* logfp);
void redistribution(t_mat_int_dyn* t_duel, int colElim, FILE* logfp);
void comptVotes(t_mat_int_dyn *t_duel, t_tab_int_dyn *comptes, FILE* logfp);
bool uninominal(t_command* cmdArray, int nbTour, s_resultats *res_panel, FILE* logfp);
bool alternatif(t_command* cmdArray, s_resultats *res_panel, FILE* logfp);
    

#endif