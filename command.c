#include "command.h"

void afficher_t_command(t_command* arrCmd) {
    static char argPossible[ARGMAX][5] = {"-m", "-i", "-l", "-d", "cm", "cp", "cs", "va", "uni1", "uni2"};
    printf("\n /./././././ AFFICHAGE STRUCT COMMAND /./././././ \n");
    printf("arguments: [");
    for(int k=0; k<ARGMAX; ++k)
        printf("%s, ", argPossible[k]);
    printf("]\nargOccur:  [");
    for(int k=0; k<ARGMAX; ++k)
        printf("%d , ", arrCmd->argOccur[k]);
    printf("]\nfileNames: [%s, %s]\n\n", arrCmd->fileNames[0], arrCmd->fileNames[1]);
    //afficher_csv_array(&arrCmd->csvFile);
}

void init_t_command(t_command* arrCmd) {
    arrCmd->argOccur = (int *) malloc(ARGMAX*sizeof(int));
    memset(arrCmd->argOccur, 0, ARGMAX * sizeof(int));
    arrCmd->fileNames = (char**) malloc(LINKMAX*sizeof(char*));
    arrCmd->fileNames[0] = "no .csv file";
    arrCmd->fileNames[1] = "no .txt file";
}

int checkArgValid(t_command* arrCmd, int argc, char *argv[]) {
    printf("\ncheckArgValid ENTRY \n");
    if(arrCmd->argOccur[0] > 0) {    // SI -m ALORS ON DOIT AVOIR AU MOINS UN PARMIS: cm, cp, cs, va, uni1, uni2.
        int condArg_M = 0;
        int a = 9;
        while(a >= 4 && condArg_M < 1) {
            if(arrCmd->argOccur[a] > 0)
                condArg_M++;
            a--;
        }
        if(condArg_M == 0) {
            printf("Manque specification du -m ! \n"); 
            return 0;
        }
    }
    if(arrCmd->argOccur[3] > 0) {  // SI -d alors
        printf("-d présent\n");
        if(arrCmd->argOccur[1] > 0) {  // SI -i alors CONFLIT CAR -d ET -i SIMULTANES
            printf("ERROR: -i et -d en simultanés ! \n");
            return 0;
        }
        arrCmd->argOccur[9] = 0;
        arrCmd->argOccur[8] = 0;
        arrCmd->argOccur[7] = 0;
    }
    else if(arrCmd->argOccur[1] == 0) { // SI -i alors (sachant que pas de -d car testé au dessus)
        printf("ERROR: absence de -i ou -d ! \n");
        return 0;
    }
    printf("RETURN checkInvalidError: Good \n");
    return 1;
}

int get_arg_index(char *arg) {
    static char argPossible[ARGMAX][5] = {"-m", "-i", "-l", "-d", "cm", "cp", "cs", "va", "uni1", "uni2"};
    for(int indice=0; indice<ARGMAX; indice++) {
        if(strcmp(arg,argPossible[indice])==0)
            return indice;
    }
    return -1;
}

int verifFile(char *argv[], int index, int indiceArg, t_command* arrCmd) {
    int filetype = -1; // 0 = CSV       // 1 = TXT
    printf("\n ENTRY verifFollowing with argument: %s , indice: %d\n", argv[index], indiceArg);
    char* nextArg = argv[index+1];
    printf("nextArg: %s \n", nextArg);
    int indiceFollowing = get_arg_index(nextArg);
    if(indiceArg == 0) { // CORRESPOND AU -m
        if(indiceFollowing >= 4 && indiceFollowing <= 9)
            return 1;
        return 0;
    }
    else {     //SINON pour -d / -i / -l , on attend un FICHIER
        char* extension = strrchr(nextArg, '.');
        printf("extension: %s\n", extension);
        if(extension == NULL) { // SI n'est pas un fichier
            printf("ERREUR FICHIER ARGUMENT DU FICHIER INCORRECT \n");
            return 0;
        }
        else if(indiceArg == 2) {  // SI -l
            if(strcmp(".txt", extension) != 0) {
                printf("ERREUR FICHIER TXT ATTENDU AU LIEU DE : %s \n", extension);
                return 0;
            }
            filetype = 1;
        }
        else if(indiceArg==1 || indiceArg==3) {  // SI -d / -i
            printf("strcomp: %d\n", strcmp(".csv", extension));
            if(strcmp(".csv", extension) != 0) {
                printf("ERREUR FICHIER CSV ATTENDU AU LIEU DE : %s \n", extension);
                return 0;
            }
            filetype = 0;
        }
        FILE *pFile;
        pFile = fopen(nextArg, "r");
        printf("file opened \n");
        if(pFile == NULL) {
            printf("INCORRECT FILE\n");
            return 0;
        }
        //strcpy(arrCmd->fileNames[filetype], nextArg);
        arrCmd->fileNames[filetype] = nextArg;
        printf("CORRECT FILE \n");
        fclose(pFile);
        if(filetype == 0) {
            printf("FILL CSV ! \n\n");
            fillCsvArray(&arrCmd->csvFile, nextArg);
        }
        return 1;
    }
}

int parameterNeeded(int indice) {
    if(indice<=3 && indice >=0)
        return 1;
    return 0;
}

int analyseCommande(t_command cmdArray, int argc, char *argv[]) {
    printf("argc: %d\n", argc);
    int indiceBuff = 0;
    for(int k=1; k<argc; ++k) {
        //afficher_t_command(&cmdArray);
        printf("get_arg_index(%s) \n", argv[k]);
        indiceBuff = get_arg_index(argv[k]);
        if(indiceBuff != -1) {
            printf("argument valable trouvé (%s)\n", argv[k]);
            cmdArray.argOccur[indiceBuff]=1;
            if(parameterNeeded(indiceBuff) == 1) {
                if(k!=argc-1) {  // SI IL EXISTE UN ARGUMENT SUIVANT ET QUE L'ARGUMENT ETUDIÉ NECESSITE UN PARAMETRE
                    printf("entree if 1E \n");
                    if(verifFile(argv, k, indiceBuff, &cmdArray) == 0) { // SI LE PARAMETRE ET INCORRECT  
                        printf("Mauvais argument suivant le %s ! \n", argv[k]);
                        return 0;
                    }
                }
                else {
                    printf("Un argument est nécessaire après %s !\n", argv[k]);
                    return 0;
                }
            }   
        }
        
    }
    if(checkArgValid(&cmdArray, argc, argv))
        return 1;
    else {
        printf("ERROR\n");
        return 0;
    }
}