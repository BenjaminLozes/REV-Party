#include "command.h"

void init_tab_char_dyn(tab_candidats *t_tabchar) {
    int dim = getNbRows("candidats.txt")+1;
    t_tabchar->tab = (char**) malloc(dim*sizeof(char*));
    for(int i=0; i<dim; i++)
        t_tabchar->tab[i] = "Candidat X";
    FILE * fp = fopen("candidats.txt", "r");
    char line[512];
    char *token;                   
    int k=0;
    while (fgets(line, 512, fp)) {
        token = strtok(line, "\n");
        strcpy(&t_tabchar->tab[k++],token);
    }
    fclose(fp);
}

bool verifMethod(char* arg) {
    if(get_arg_index(arg) > 3)
        return 1;
    return 0;
}

bool correct_file(char* filename, FILE* logfp) {
    fprintf(logfp, "-IN correct_file \n");
    FILE *pFile;
    pFile = fopen(filename, "r+");
    if(pFile == NULL) {
        fprintf(logfp, "INCORRECT FILE\n");
        return 0;
    }
    fprintf(logfp, "CORRECT FILE \n");
    fclose(pFile);
    return 1;
}

void afficher_t_command(t_command* arrCmd, FILE* logfp) {
    fprintf(logfp, "-IN afficher_t_command \n");
    static char argPossible[ARGMAX][5] = {"-m", "-i", "-l", "-d", "cm", "cp", "cs", "va", "uni1", "uni2"};
    fprintf(logfp, "\n /./././././ AFFICHAGE STRUCT COMMAND /./././././ \n");
    fprintf(logfp, "arguments: [");
    for(int k=0; k<ARGMAX; ++k)
        fprintf(logfp, "%s, ", argPossible[k]);
    fprintf(logfp, "]\nargOccur:  [");
    for(int k=0; k<ARGMAX; ++k)
        fprintf(logfp, "%d , ", arrCmd->argOccur[k]);
    fprintf(logfp, "]\nfileNames: [%s, %s] \nLog requis: %d \nMethode: %s\n\n", arrCmd->fileNames[0], arrCmd->fileNames[1], arrCmd->log, argPossible[arrCmd->methodNb]);
    fprintf(logfp, "-OUT afficher_t_command \n\n");
}

void init_t_command(t_command* arrCmd) {
    arrCmd->argOccur = (bool *) malloc(ARGMAX*sizeof(bool));
    //memset(arrCmd->argOccur, 0, ARGMAX * sizeof(int));
    arrCmd->fileNames = (char**) malloc(LINKMAX*sizeof(char*));
    arrCmd->fileNames[0] = "CSV file";
    arrCmd->fileNames[1] = "TXT file";
    init_tab_char_dyn(&arrCmd->candidats);
    arrCmd->log = 0;
    arrCmd->methodNb = 0;
}

int get_arg_index(char *arg) {
    static char argPossible[ARGMAX][5] = {"-m", "-i", "-l", "-d", "cm", "cp", "cs", "va", "uni1", "uni2"};
    for(int indice=0; indice<ARGMAX; indice++) {
        if(strcmp(arg,argPossible[indice])==0)
            return indice;
    }
    return -1;
}

bool verifFile(char *argv[], int index, int indiceArg, t_command* arrCmd, FILE* logfp) { //POUR -d / -i / -l , on attend un FICHIER
    fprintf(logfp, "\n-IN verifFile with argument: %s , indice: %d\n", argv[index], indiceArg);
    char* nextArg = argv[index+1];
    fprintf(logfp, "nextArg: %s \n", nextArg);
    //int indiceFollowing = get_arg_index(nextArg);
    char* extension = strrchr(nextArg, '.');
    fprintf(logfp, "extension: %s\n", extension);
    if(extension == NULL || indiceArg == 2) { // SI n'est pas un fichier
        fprintf(logfp, "ERREUR FICHIER ARGUMENT DU FICHIER INCORRECT \n");
        return 0;
    }
    // SI csv car txt traité dans launcher.c
    fprintf(logfp, "strcomp: %d\n", strcmp(".csv", extension));
    if(strcmp(".csv", extension) != 0) {
        fprintf(logfp, "ERREUR FICHIER CSV ATTENDU AU LIEU DE : %s \n", extension);
        return 0;
    }
    if(correct_file(nextArg, logfp) == 0)
        return 0;
    analyseCsvFile(&arrCmd->csvFile, &arrCmd->t_duel, nextArg, logfp);
    arrCmd->fileNames[0]=nextArg;
    fprintf(logfp, "-OUT verifFile \n");
    return 1;
}


unsigned char parameterNeeded(int indice) {
    if(indice==3 || indice ==1)
        return 1;
    else if(indice == 0)
        return 2;
    return 0;
}

FILE* checkLog(t_command* cmdArray, int argc, char *argv[]) {
    FILE* logfp = stdout;
    cmdArray->fileNames = (char**) malloc(LINKMAX*sizeof(char*));
    cmdArray->log = 0;
    unsigned char k=1;
    while(k<argc-1) {
        if(get_arg_index(argv[k])==2) {
            char* extension = strrchr(argv[k+1], '.');
            if(extension == NULL || strcmp(".txt", extension) != 0) { // SI n'est pas un fichier ou pas un txt
                fprintf(stdout, "ERREUR FICHIER ARGUMENT DU FICHIER INCORRECT \n");
                return logfp;
            }
            cmdArray->log = 1;
            cmdArray->fileNames[1] = argv[k+1];
            logfp = fopen(argv[k+1], "ab+");
            //fclose(logfp);
            k = argc;
            fprintf(logfp, "\n\n---------- Fichier de log attribué en %s --------------\n\n\n", argv[k+1]);
        }
        ++k;
    }
    return logfp;
}

bool analyseCommande(t_command* cmdArray, int argc, char *argv[], FILE* logfp) {
    fprintf(logfp, "-IN analyseCommande \n");
    if(argc < 3)
        return 0;    
    fprintf(logfp, "argc: %d\n", argc);
    int indiceBuff = 0;
    bool csvBool = 0;
    for(unsigned char k=1; k<argc; ++k) {
        //afficher_t_command(&cmdArray);
        indiceBuff = get_arg_index(argv[k]);
        fprintf(logfp, "get_arg_index(%s) = %d\n", argv[k], indiceBuff);
        if(indiceBuff != -1) {
            fprintf(logfp, "argument valable trouvé (%s)\n", argv[k]);
            cmdArray->argOccur[indiceBuff]=1;
            if(k!=argc-1) {  // SI IL EXISTE UN ARGUMENT SUIVANT ET QUE L'ARGUMENT ETUDIÉ NECESSITE UN PARAMETRE
                if(parameterNeeded(indiceBuff) == 1) { // file needed
                    if(csvBool)
                        return 0;
                    if(verifFile(argv, k, indiceBuff, cmdArray, logfp) == 0) { // SI LE PARAMETRE ET INCORRECT  
                        fprintf(logfp, "Mauvais argument suivant le %s ! \n", argv[k]);
                        return 0;
                    }
                    fprintf(logfp, "CSVBOOL %d \n", csvBool);
                    csvBool=1;
                }
                else if(parameterNeeded(indiceBuff) == 2) { // Method needed
                    if(verifMethod(argv[k+1]) == 0) {
                        fprintf(logfp, "méthode donnée après -m incorrecte ! \n");
                        return 0;
                    }
                    cmdArray->methodNb = get_arg_index(argv[k+1]);
                }
                else
                    fprintf(logfp, "Aucun argument nécessaire après %s !\n", argv[k]);
            }   
        }
        
    }
    if(!csvBool)
        return 0;
    fprintf(logfp, "\n-OUT analyseCommande \n");
    return 1;
}