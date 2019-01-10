#include "liste.h"

int getTail(liste lst) {
    int temp = lst.Tete+1-lst.nbElt;
    if(temp < 0)
        return DIMMAX+temp;
    return temp;
}

char* indexTab(liste lst) {
    char* tabInd = (char*) malloc(lst.nbElt * sizeof(char));
    char index = getTail(lst);
    for(int x=0; x<lst.nbElt; ++x) {
        tabInd[x] = index;
        index = (index+1)%DIMMAX;
    }
    return tabInd;
}

int nbEltList(liste lst) {
    return lst.nbElt;
}

void createList(liste *p) {
    p->Tete = VIDE;
    p->nbElt = 0;
}

void addTailList(liste *p, Elementliste e) {
    if(fullList(*p))
        return;
    if(p->Tete == -1 || getTail(*p)==0) {
    printf("ta mere---------------------------------\n");
        addFrontList(p, e);}
    else {
        p->Tabliste[DIMMAX - (p->nbElt - p->Tete)] = e;
        p->nbElt++;
    }
}

void addFrontList(liste *p, Elementliste e) {
    if(fullList(*p))
        return;
    copie_element(&p->Tabliste[++p->Tete], e);
    p->nbElt++;
}

void delTailList(liste *p) {
    if(emptyList(*p))
        return;
    printf("avan: %d // apres: ", getTail(*p));
    p->nbElt--;
    printf("%d \n", getTail(*p));
}

void delFrontList(liste *p) {
    if(emptyList(*p))
        return;
    p->Tete--;
    printf("avan: %d // apres: ", getTail(*p));
    p->nbElt--;
    printf("%d \n", getTail(*p));
}

void headList(liste p, Elementliste *e) {
    if(emptyList(p))
        return;
    copie_element(e, p.Tabliste[p.Tete]);
}

void tailList(liste p, Elementliste *e) {
    if(emptyList(p))
        return;
    copie_element(e, p.Tabliste[getTail(p)]);
}

bool emptyList(liste p) {
    if(p.nbElt == 0)
        return true;
    return false;
}

bool fullList(liste p) {
    if(p.nbElt == DIMMAX)
        return true;
    return false;
}

void dumpList(liste p, FILE *fp) {
    if(emptyList(p))
        return;
    if(getTail(p)>p.Tete){
        for(int w = getTail(p); w < DIMMAX; ++w)
            afficher_element(p.Tabliste[w], fp);
    }
    if(p.Tete!=-1) {
        for(int x=0; x<=p.Tete; ++x)
            afficher_element(p.Tabliste[x], fp);
    }
    fprintf(fp, "\n");
}

void swapEltList(Elementliste *a, Elementliste *b) {
    printf("-----PRE: \n");
    afficher_element(*a, stdout);
    afficher_element(*b, stdout);
    Elementliste temp;
    copie_element(&temp, *a);
    copie_element(a, *b);
    copie_element(b, temp);
    printf("----POST: \n");
    afficher_element(*a, stdout);
    afficher_element(*b, stdout);
}

void bubbleSortList(liste *p) {
    if(emptyList(*p))
        return;
    bool swaped = true;
    int lenProcess = p->nbElt-1;
    while(swaped || lenProcess==0) {
        swaped = false;
        for(int x=0; x<lenProcess; ++x) {
            if(p->Tabliste[x].poids > p->Tabliste[x+1].poids) {
                swapEltList(&p->Tabliste[x], &p->Tabliste[x+1]);
                swaped = true;
            }
        }
        lenProcess--;
    }
}

void pickEltList(liste l, Elementliste *e, int index) {
    copie_element(e, l.Tabliste[index]);
}

bool belongEltList(liste p, Elementliste e) {
    for(int x=0; x<p.nbElt; ++x) {
        if(cmp_elements(e, p.Tabliste[x])) {
                return true;
        }
    }
    return false;
}
