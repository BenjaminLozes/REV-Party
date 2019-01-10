#include "csvanalyse.h"

int * creer_tab_int(int dim) {
    int* tabCree = (int*) malloc(dim*sizeof(int));
    for(int k=0; k<dim; k++)
        tabCree[k] = 0;
    return tabCree;
}

int ** creer_mat_int(int nbRows, int nbCol) {
    int** matCree = (int**) malloc(nbRows*sizeof(int*));
    for(unsigned int x=0; x<nbRows; x++)
        matCree[x] = creer_tab_int(nbCol);
    return matCree;
}

void affiche_tab_int(int *tab, int dim, FILE *logfp){
    for(unsigned int x=0; x<dim; x++)
        fprintf(logfp, "%d", tab[x]);
    fprintf(logfp, "\n");
}

void creer_t_mat_int_dyn(t_mat_int_dyn *stTab, int nbRows, int nbCol) {
    stTab->nbRows = nbRows;
    stTab->nbCol = nbCol;
    stTab->tab = (int**) malloc(nbRows*sizeof(int*));
    stTab->tab = creer_mat_int(nbRows, nbCol);
}

void creer_t_tab_int_dyn(t_tab_int_dyn *stTab, int dim) { // LIEN AVEC LA N-1, REATTRIBUTION DES NBs OU GET ?
    stTab->dim = dim;
    stTab->tab = (int*) malloc(stTab->dim*sizeof(int));
    stTab->tab = creer_tab_int(stTab->dim);
}

void creer_t_mat_char_dyn(t_mat_char_star_dyn * s_tabmots) { // GROS DOUTE PQ PAS D'ARG ??
    s_tabmots->tab = (char***) malloc(s_tabmots->nbRows*sizeof(char**));
    for(int x=0; x<s_tabmots->nbRows; ++x) {
        s_tabmots->tab[x] = (char**) malloc(s_tabmots->nbCol * sizeof(char*));
        for(int y=0; y<s_tabmots->nbCol; y++)
            s_tabmots->tab[x][y] = (char*) malloc(64 * sizeof(char));
    }
}

void affiche_t_tab_int_dyn(t_tab_int_dyn t_tab, FILE *logfp) {
    for(int x=0; x<t_tab.dim; ++x)
        fprintf(logfp, "%d ", t_tab.tab[x]);
    fprintf(logfp, "\n");
}

void affiche_t_mat_char_star_dyn(t_mat_char_star_dyn t_tabmots, FILE *logfp) {
    for(int x=0; x<t_tabmots.nbRows; ++x) {
        for(int y=0; y<t_tabmots.nbCol; ++y)
            fprintf(logfp, "%s ", t_tabmots.tab[x][y]);
    }
}

void affiche_t_mat_int_dyn(t_mat_int_dyn t_tab, FILE *logfp) {
    for(int x=0; x<t_tab.nbRows; ++x) {
        for(int y=0; y<t_tab.nbCol; ++y)
            fprintf(logfp, "%d ", t_tab.tab[x][y]);
        fprintf(logfp, "\n");
    }
}

void affiche_mat_int(int **duels_mat, int nbRows, int nbCol, FILE *logfp) {
    for(int x=0; x<nbRows; ++x) {
        for(int y=0; y<nbCol; ++y)
            fprintf(logfp, "%d ", duels_mat[x][y]);
        fprintf(logfp, "\n");
    }
}

void init_tab_int(int *tab, int dim, int valeur) {
    for(int x=0; x<dim; ++x)
        tab[x] = valeur;
}

void init_mat_int(int **mat, int nbRows, int nbCol, int valeur) {
    for(int x=0; x<nbRows; ++x) {
        for(int y=0; y<nbCol; ++y)
            mat[x][y] = valeur;
    }
}