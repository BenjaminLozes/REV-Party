#include "command.h"

int getNbLign(char* filename) {
    FILE* myfile = fopen(filename, "r");
    int ch, number_of_lines = 0;
    do {
        ch = fgetc(myfile);
        if(ch == '\n')
            number_of_lines++;
    } while (ch != EOF);
    if(ch != '\n' && number_of_lines != 0) 
        number_of_lines++;
    fclose(myfile);
    return number_of_lines;
}

void init_t_csv(t_csv* csvFile, char* name) {
    printf("IN init t_csv \n");
    csvFile->lign = getNbLign(name);
    csvFile->filename = name;
    csvFile->colonne = 1;
    FILE * fp = fopen(name, "r");
    char str[256];
    fgets(str, 256, fp);
    int n=0;
    while(str[n]!='\n' && str[n]!='\r') {
        if(str[n]=='\t')
            csvFile->colonne++;
        n++;
    }
    printf("cpt / nb de colonne: %d \n", csvFile->colonne);
    csvFile->csvArray = (char***) malloc(csvFile->lign * sizeof(char**));
    printf("csv lignes: %d \n", csvFile->lign);
    for(int a=0; a<csvFile->lign; a++) {
        csvFile->csvArray[a] = (char**) malloc(csvFile->colonne * sizeof(char*));
        for(int b=0; b<csvFile->colonne; b++)
            csvFile->csvArray[a][b] = (char*) malloc(64 * sizeof(char));
    }
    fclose(fp);
    printf("OK initialisatio t_csv. \n");
}

void afficher_csv_array(t_csv* csvFile) {
    printf("IN afficher_csvArray\n/*/*/*/*/*/\nlignes : %d\ncolonnes: %d\n", csvFile->lign, csvFile->colonne);
    for(int a=0; a<csvFile->lign; a++) {
        for(int b=0; b<csvFile->colonne; b++)
            printf("| %s |", csvFile->csvArray[a][b]);
        printf("\n");
    }
    printf("\n\nOK afficher_csv\n\n\n");

}

int fillCsvArray(t_csv* csvFile, char* filename) {
    printf("\n\n//////// ENTRY ANALYSECSV ////////// \n\n");
    init_t_csv(csvFile, filename);
    printf("csvArray->colonne = %d\n", csvFile->colonne);
    afficher_csv_array(csvFile);
    FILE * fp = fopen(filename, "r");
    char line[512];
    char *token;
    int ligneCourante = 0;
    const char s[2] = "\t";
    printf("csvArray->colonne = %d\n", csvFile->colonne);
    while (fgets(line, 512, fp)) {
        printf("%s", line);
        token = strtok(line, s);
        for(int k=0; k<csvFile->colonne; k++) {
            printf("%s | ", token);
                strcpy(csvFile->csvArray[ligneCourante][k], token);
            token = strtok(NULL, s);
            //printf("        ssTOKEN: %s\n", token);
            //printf("Field %d would be %s\n", k, token);
            //afficher_csv_array(csvFile);
        }
        ligneCourante++;
    }
    printf("\n\n");
    afficher_csv_array(csvFile);
    fclose(fp);
    return(1);
}

/*
int main(void)
{
    t_csv csvFile;
    fillCsvArray(&csvFile, "vote10.csv");
}
*/