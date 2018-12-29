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
    if(p->Tete == -1)
        addFrontList(&p, e);
    else {
        p->Tabliste[DIMMAX - (p->nbElt - p->Tete)] = e;
        p->nbElt++;
    }
}

void addFrontList(liste *p, Elementliste e) {
    if(fullList(*p))
        return;
    p->Tabliste[++p->Tete] = e;
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
    *e = p.Tabliste[p.Tete];
}

void tailList(liste p, Elementliste *e) {
    if(emptyList(p))
        return;
    return getTail(p);
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
    for(int w = getTail(p); w < DIMMAX; ++w)
        fprintf(fp, "%d ", p.Tabliste[w]);
    if(p.Tete!=-1) {
        for(int x=0; x<=p.Tete; ++x)
            fprintf(fp, "%d ", p.Tabliste[x]);
    }
    fprintf(fp, "\n");
}

void swapEltList(Elementliste *a, Elementliste *b) {
    Elementliste *temp;
    *temp = *a;
    *a = *b;
    *b = *temp;
}

void bubbleSortList(liste *p) {
    if(emptyList(*p))
        return;
    char* tab = indexTab(*p);
    bool swaped = true;
    int lenProcess = p->nbElt-1;
    while(swaped) {
        swaped = false;
        for(int x=0; x<lenProcess; ++x) {
            if(&p->Tabliste[tab[x]] < &p->Tabliste[tab[x+1]]) {
                swapEltList(&p->Tabliste[tab[x]], &p->Tabliste[tab[x+1]]);
                swaped = true;
            }
        }
        lenProcess--;
    }

}

void pickEltList(liste l, Elementliste *e, int index) {
    char* tab = indexTab(l);
    *e = l.Tabliste[tab[index]];
}

bool belongEltList(liste p, Elementliste e) {
    char* tab = indexTab(p);
    for(int x=0; x<p.nbElt; ++x) {
        if(e.dest == p.Tabliste[tab[x]].dest) {
            if(e.orig == p.Tabliste[tab[x]].orig) {
                if(e.poids == p.Tabliste[tab[x]].poids)
                return true;
            }
        }
    }
    return false;
}
