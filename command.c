#include "command.h"

void init_t_command(*t_command arrCmd) {
    arrCmd->argOccur = (int *) malloc(10*sizeof(int));
    memset(arrCmd->argOccur, 0, 10 * sizeof(int));
    arrCmd->filesLink = (FILE*) malloc(2*sizeof(FILE));
}

int checkArgValid(*t_command arrCmd, int argc, char *argv[]) {
    printf("\ncheckArgValid ENTRY \n");
    if(arrCmd->argTab[0] > 0) {    // SI -m ALORS ON DOIT AVOIR AU MOINS UN PARMIS: cm, cp, cs, va, uni1, uni2.
        int condArg_M = 0;
        int a = 9;
        while(a >= 4 && condArg_M < 1) {
            if(arrCmd->argTab[a] > 0)
                condArg_M++;
            a--;
        }
        if(condArg_M == 0) {
            printf("Manque specification du -m ! \n"); 
            return 0;
        }
    }
    if(arrCmd->argTab[3] > 0) {  // SI -d alors
        if(arrCmd->argTab[1] > 0) {  // SI -i alors CONFLIT CAR -d ET -i SIMULTANES
            printf("ERROR: -i et -d en simultanés ! \n");
            return 0;
        }
        arrCmd->argTab[9] = 0;
        arrCmd->argTab[8] = 0;
        arrCmd->argTab[7] = 0;
    }
    else if(arrCmd->argTab[1] == 0) { // SI -i alors (sachant que pas de -d car testé au dessus)
        printf("ERROR: absence de -i ou -d ! \n");
        return 0;
    }
    printf("RETURN checkInvalidError: 1 \n");
    return 1;
}

int get_arg_index(char *arg) {
    static char argPossible[10][5] = {"-m", "-i", "-l", "-d", "cm", "cp", "cs", "va", "uni1", "uni2"};
    for(int indice=0; indice<10; indice++) {
        if(strcmp(arg,argPossible[indice])==0)
            return indice;
    }
    return -1;
}

int verifFollowing(char *argv[], int index, int indiceArg, *t_command arrCmd) {
    int filetype;
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
        if(indiceArg == 2) {  // SI -l
            if(strcmp(".txt", extension) != 0)
                return 0;
            filetype = 1;
        }
        else if(indiceArg==1 || indiceArg==3) {  // SI -d / -i
        printf("strcomp: %d\n", strcmp(".csv", extension));
            if(strcmp(".csv", extension) != 0)
                return 0;
            filetype = 0;
        }
        FILE *pFile;
        pFile = fopen(nextArg, "r");
        printf("file opened \n");
        if(pFile != NULL) {
            arrCmd->filesLink[filetype] = nextArg;
            fclose(pFile);
            return 1;
        }
        fclose(pFile);
        return 0;
    }
}

int parameterNeeded(int indice) {
    if(indice<=3 && indice >=0)
        return 1;
    return 0;
}

t_command analyseCommande(int argc, char *argv[]) {
    t_command cmdArray;
    init_t_command(&cmdArray);
    static char argPossible[10][5] = {"-m", "-i", "-l", "-d", "cm", "cp", "cs", "va", "uni1", "uni2"};
    int indiceBuff = 0;
    for(int k=0; k<argc; ++k) {
        printf("get_arg_index(%s) \n", argv[k]);
        indiceBuff = get_arg_index(argv[k]);
        printf("indice: %s \n", argv[k]);
        if(indiceBuff != -1) {
            cmdArray.argOccur[indiceBuff]=1;
            printf("k:%d et argc-1:%d et indice:%d\n", k, argc-1, indiceBuff);
            if(k!=argc-1 && parameterNeeded(indiceBuff) == 1) {  // SI IL EXISTE UN ARGUMENT SUIVANT ET QUE L'ARGUMENT ETUDIÉ NECESSITE UN PARAMETRE
                if(verifFollowing(argv, k, indiceBuff) == 0)  // SI LE PARAMETRE ET INCORRECT  
                    return 0;
            }
        }
        
    }
    for(int _=0; _< 10; ++_)
        printf("argOccur '%s': %d \n", argPossible[_], cmdArray.argOccur[_]);
    return checkArgValid(cmdArray.argOccur, argc, argv);
}