#include "utils_scrutin.h"

bool isDoublon(t_tab_int_dyn *comptes, int indMax) { // Renvoie TRUE si au moins deux elements identiques dans une liste
    for(int k=0; k<comptes->dim; k++) {
        if(k!=indMax) {
            if(comptes->tab[k] == comptes->tab[indMax])
                return 1;
        }
    }
    return 0;
}

void init_int_tab(t_tab_int_dyn *lst, FILE* logfp) {
    lst->tab = (int*) malloc(lst->dim * sizeof(int));
    for(int k=0; k<lst->dim; k++)
        lst->tab[k] = 0;
}

void get_max_index(t_tab_int_dyn *comptes, t_tab_int_dyn *index, FILE* logfp) {  // Renvoie les deux indexs des deux valeurs maximales atteintes dans tab
    fprintf(logfp, "IN get_max_index \n");
    int temp = 0;
    index->tab[0] = 0;
    index->tab[1] = comptes->dim-1;
    //for(int _=0; _<comptes->dim; _++)
        //fprintf(logfp, "// comptes->tab[%d] = %d \n", _, comptes->tab[_]);
    int tempMax;
    for(int k=0; k<2; k++) {  // un tour par index max
        tempMax=0;
        temp = 0;
        for(int x=0; x<comptes->dim; x++) {
            //fprintf(logfp, "index[0] = %d     index[1] = %d \n", index[0], index[1]);
            //fprintf(logfp, "MAX(comptes->tab[%d] = %d, comptes->tab[%d] = %d) = %d et comptes->tab[index[1]] = %d\n", x, comptes->tab[x], index->tab[0], comptes->tab[index->tab[0]], MAX(comptes->tab[x], comptes->tab[index->tab[0]]), comptes->tab[index->tab[1]]);
            if((k==1 && x!= index->tab[0]) || k==0) {
                if(MAX(comptes->tab[x], temp) > temp) {
                    temp = comptes->tab[x];
                    tempMax = x;
                }
            }
        }
        if(k==1)
            index->tab[1] = tempMax;
        else
            index->tab[0] = tempMax;
    }
    fprintf(logfp, "OK get_max_index \n\n");
}

void afficher_decompte(t_tab_int_dyn *comptes, FILE* logfp) {
    affiche_t_tab_int_dyn(*comptes, logfp);
    fprintf(logfp, "[%d", comptes->tab[0]);
    for(int a=1; a<comptes->dim; a++)
        fprintf(logfp, ", %d", comptes->tab[a]);
    fprintf(logfp, "]\n\n");
}


void comptVotes(t_mat_int_dyn *t_duel, t_tab_int_dyn *comptes, FILE* logfp) {
    for(int x=0; x<t_duel->nbRows; x++) {
        for(int y=0; y<t_duel->nbCol; y++) {
            comptes->tab[y] += t_duel->tab[x][y];
        }
    }
}

void redistribution(t_mat_int_dyn* t_duel, int colElim, FILE* logfp) {
    //affiche_t_mat_int_dyn(*t_duel, logfp);
    //printf("\n");
    // ON SAUVEGARDE LES VOTES DE LA COLONNE SUPPRIMÉE DANS UNE LISTE DelCol.
    t_tab_int_dyn delCol;
    creer_t_tab_int_dyn(&delCol, t_duel->nbRows);
    for(int lign=0; lign<t_duel->nbRows; lign++)
        delCol.tab[lign] = t_duel->tab[lign][colElim];
    //affiche_t_tab_int_dyn(delCol, logfp);
    //printf("\n");

    t_tab_int_dyn totalLign;
    creer_t_tab_int_dyn(&totalLign, t_duel->nbRows);
    double prct;
    for(int x=0; x<totalLign.dim; x++) {
        // ON CALCULE LE NOMBRE DE VOTE TOTAL PAR VOTANT SANS COMPTER LE VOTE POUR LE CANDIDAT ELIMINÉ
        for(int y=0; y<t_duel->nbCol; y++) {
            if(y != colElim)
                totalLign.tab[x] += t_duel->tab[x][y];
        }
        t_duel->tab[x][colElim] = 0;

        // ON REDISTRIBUE LES VOIX EN TANT COMPTE DU POURCENTAGE D'APPRÉCIATION
        for(int y=0; y<t_duel->nbCol; y++) {
            prct = (double) t_duel->tab[x][y]/totalLign.tab[x];
            prct*=delCol.tab[x];
            //fprintf(logfp, "prct*delcol = %d \n", (int) prct);
            t_duel->tab[x][y] += (int) prct;
        }
        //affiche_t_mat_int_dyn(t_newDuel, logfp);
        //printf("\n");
    }
    affiche_t_mat_int_dyn(*t_duel, logfp);
}