#ifndef UTILS_H
#define UTILS_H

#include "csvanalyse.h"

#define ARGMAX 10
#define LINKMAX 2

/**
 * @brief Tous les outils d'analyse et de test pour:
 *  - Traiter la commande bash
 *  - Traiter les logs si besoin
 *  - Traiter et traduire le csv
 *  - Creer une matrice de duel pour les simulations
 */

typedef struct tab_char_dyn {
    char** tab;
    int dim;
} tab_candidats;

typedef struct command_options {  // STRUCTURE DE STOCKAGE DES ELEMENT PERMETTANT LA PREPARATION DE LA SIMULATION
    // {"-m", "-i", "-l", "-d", "cm", "cp", "cs", "va", "uni1", "uni2"};
    bool* argOccur; // Occurence de chaque balise connue
    char** fileNames; // [CSV , TXT]
    tab_candidats candidats; // Nom des candidats
    t_mat_char_star_dyn csvFile; // Traduction du csv en une matrice de phrases
    t_mat_int_dyn t_duel; // table regroupant l'ensemble des votes (colonne <=> candidat)
    bool log; // log activé ?
    unsigned short int methodNb; // indice dans argOccur de la methode à employer, si 0 appliquer selon -d/-i
} t_command;

void init_candidats(t_command* arrCmd, FILE* logfp);  // initialise la liste des candidats de la struct
bool verifMethod(char* arg);  // renvoie l'indice de la méthode en question dans argOccur
bool correct_file(char* filename, FILE* logfp); // verifie la cohérence du fichier demandé
void afficher_t_command(t_command* arrCmd, FILE* logfp); // affiche notre structure t_command de façon remarquable
void init_t_command(t_command* arrCmd);  // initialise t_command
int get_arg_index(char *arg);  // renvoie l'indice dans argOccur si présent
bool verifFile(char *argv[], int index, int indiceArg, t_command* arrCmd, FILE* logfp); // vérification spécifique au .csv
unsigned char parameterNeeded(int indice);  // permet de savoir si notre balise requiert d'etre complété par un fichier par exemple
FILE* checkLog(t_command* cmdArray, int argc, char *argv[]);  // verification spécifique pour les LOG si demandés sinon -> stdout
/**
 * @brief Sous-main permettant l'analyse complète argument par argument 
 *        testant tout traitement nouveau et permettant donc un arret complet 
 *        si une erreur est trouvée plutto que d'attendre d'avoir tout traité.
 * 
 * logfp = stdout (défini avant dans launcher.c si aucun log requis par la commande bash)
 */
bool analyseCommande(t_command* cmdArray, int argc, char *argv[], FILE* logfp); 

#endif