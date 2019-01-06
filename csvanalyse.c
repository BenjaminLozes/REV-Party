#include "csvanalyse.h"

unsigned short int getNbRows(char* filename) {
    FILE* myfile = fopen(filename, "r");
    int ch, NbRows = 0;
    do {
        ch = fgetc(myfile);
        if(ch == '\n')
            NbRows++;
    } while (ch != EOF);
    fclose(myfile);
    return NbRows ;
}

unsigned char getNbCol(char* filename) {
    char str[256];
    int n=0;
    int nbCol = 1;
    FILE * fp = fopen(filename, "r");
    fgets(str, 256, fp);
    while(str[n]!='\n' && str[n]!='\r') {
        if('\t' == str[n])
            nbCol++;
        n++;
    }
    fclose(fp);
    return nbCol;
}

unsigned char getOffset(char* filename) {
    FILE * fp = fopen(filename, "r");
    char line[512];
    char *token;
    char sep[3] = "\t";
    fgets(line, 512, fp);
    token = strtok(line, sep);
    for(int k=0; k<getNbCol(filename); k++) {
        if(strcmp("Code vote", token) == 0)
            return k+1;
        token = strtok(NULL, sep);
    }
    fclose(fp);
    return 0;
}

void init_csv(t_mat_char_star_dyn *t_tabmots, char* filename, FILE* logfp) {
    fprintf(logfp, "-IN init t_csv \n");
    t_tabmots->nbRows = getNbRows(filename);
    t_tabmots->nbCol = getNbCol(filename);
    t_tabmots->offset = getOffset(filename);
    fprintf(logfp, "nb de colonne: %d \nnb de ligne: %d \n", t_tabmots->nbCol, t_tabmots->nbRows);
    creer_t_mat_char_dyn(t_tabmots);
    fprintf(logfp, "-OUT initialisatio t_csv. \n\n");
}

void init_duel(t_mat_char_star_dyn *t_tabmots, t_mat_int_dyn *t_duel, char* filename, FILE *logfp) {
    creer_t_mat_int_dyn(t_duel, t_tabmots->nbRows-1, t_tabmots->nbCol-t_tabmots->offset);
}

void afficher_csv_array(t_mat_char_star_dyn *t_tabmots, FILE* logfp) {
    fprintf(logfp, "-IN afficher_csvArray\n\nlignes : %d\ncolonnes: %d\noffset: %d\n\n", t_tabmots->nbRows, t_tabmots->nbCol, t_tabmots->offset);
    affiche_t_mat_char_star_dyn(*t_tabmots, logfp);
    fprintf(logfp, "\n\n-OUT afficher_csv \n\n");
}

void fillCsvStruct(t_mat_char_star_dyn *t_tabmots, char* filename, FILE* logfp) {
    fprintf(logfp, "-IN fillCsvStruct avec le fichier: %s \n", filename);
    FILE * fp = fopen(filename, "r");
    char line[512];
    char *token;
    int ligneCourante = 0;
    char sep[3] = "\t";
    fprintf(logfp, "\nTraitement du fichier ligne/ligne \n");
    while (fgets(line, 512, fp)) {
        fprintf(logfp, "%s\n", line);
        token = strtok(line, sep);
        for(int k=0; k<t_tabmots->nbCol; k++) {
            fprintf(logfp, "%s | ", token);
            strcpy(t_tabmots->tab[ligneCourante][k], token);
            token = strtok(NULL, sep);
        }
        ligneCourante++;
    }
    fclose(fp);
    fprintf(logfp, "\n\n-OUT fillCsvStruct \n\n");
}

void fillDuelStruct(t_mat_char_star_dyn *t_tabmots, char* filename, t_mat_int_dyn *t_duel, FILE* logfp) {
    unsigned int lign = 0;
    unsigned int col;
    for(int i=0; i<t_duel->nbRows; i++) {
        lign++;
        col = t_tabmots->offset;
        for(int j=0; j<t_duel->nbCol; j++) {
            t_duel->tab[i][j] = atoi(t_tabmots->tab[lign][col++]);
            fprintf(logfp, "t_duel->tab[%d][%d] = t_tabmots->tab[%d][%d] = %d \n",i, j, lign, col-1, t_duel->tab[i][j]);
        }
        fprintf(logfp, "\n");
    }
}


void analyseCsvFile(t_mat_char_star_dyn *t_tabmots, t_mat_int_dyn *t_duel, char* filename, FILE* logfp) {
    fprintf(logfp, "-IN analyseCsvFile avec le fichier: %s \n", filename);
    init_csv(t_tabmots, filename, logfp);
    fillCsvStruct(t_tabmots, filename, logfp);
    fprintf(logfp, "\n\n");
    init_duel(t_tabmots, t_duel, filename, logfp);
    fillDuelStruct(t_tabmots, filename, t_duel, logfp);
    affiche_t_mat_int_dyn(*t_duel, logfp);
    fprintf(logfp, "\n\n");
    afficher_csv_array(t_tabmots, logfp);
    fprintf(logfp, "-OUT analyseCsvFile \n\n");
}

