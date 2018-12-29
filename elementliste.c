#include "elementliste.h"

void saisie_element(Elementliste *e) {
    scanf("%d", &e->orig);
    scanf("%d", &e->orig);
    scanf("%d", &e->orig);
}

void copie_element(Elementliste *cible, Elementliste source) {
    cible->orig = source.orig;
    cible->dest = source.dest;
    cible->poids = source.poids;
}

void afficher_element(Elementliste e,FILE *fp) {
    printf("Element:\n- Orig: %d\n- Dest: %d\n- Poids: %d\n", e.orig, e.dest, e.poids);
}

bool cmp_elements(Elementliste e1,Elementliste e2) {
    if((e1.dest == e2.dest) && (e1.orig == e2.orig) && (e1.poids == e2.poids)) 
        return true;
    return false;
}