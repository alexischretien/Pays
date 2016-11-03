/* UQAM - Automne 2016 - INF3135 - Groupe 21 - TP2
 *
 * countries.c - Fichier source C contenant l'implementation
 * des fonctions declarees dans le fichier 'countries.h'
 *
 * @Auteur      Chretien Alexis (CHRA25049209)
 * @Version     3 novembre 2016
 */
#include<stdlib.h>
#include<stdio.h>
#include "countries.h"

/**
 * Affiche les informations d'aide lorsque l'argument --help est presemt
 *
 * @return
 */
void afficherAide(){
    printf("Usage: bin/tp2 [--help] [--output-format FORMAT] [--output-filename FILENAME]\n");
    printf(" [--show-languages] [--show-capital] [--show-borders] [--show-flag]\n");
    printf(" [--country COUNTRY] [--region REGION]\n\n");
    printf("Displays information about countries.\n\n");
    printf("Optional arguments:\n");
    printf("  --help                     Show this help message and exit.\n");
    printf("  --output-format FORMAT     Selects the output format (either \"test\", \"dot\" or \"png\").\n");
    printf("                             The \"dot\" format is the one recognized by Graphviz.\n");
    printf("                             The default format is \"text\".\n");
    printf("  --output-filename FILENAME The name of the output filename. This argument is\n");
    printf("                             mandatory for the \"png\" format. For the \"text\" and \"dot\"\n");
    printf("                             format, the result is printed on stdout if no output\n");
    printf("                             filename is given.\n");
    printf("  --show-languages           The offficial languages of each country are displayed.\n");
    printf("  --show-capital             The capital of each country is displayed.\n");
    printf("  --show-borders             The borders of each country are displayed.\n");
    printf("  --show-flag                The flag of each country is displayed\n");
    printf("                             (only for \"dot\" and \"png\" format).\n");
    printf("  --country COUNTRY          The country code (e.g. \"can\", \"usa\") to be displayed.\n");
    printf("  --region REGION            the supported regions are \"africa\", \"americas\",\n");
    printf("                             \"asia\", \"europe\" and \"oceania\".\n");
} 

/**
 * Fonction qui verifie si la commande d'execution contient le chaine de 
 * caracteres desiree.
 *
 * @param       **p - pointeur de pointeurs de caracteres, pointant au debut
 *              du tableau de chaine de caracteres argv
 * @param       *chaine - chaine recherchee
 * @param       nombre de chaine contenues dans la commande d'execution (argc)              
 * @return      vrai si la la chaine est presente dans la ligne de commande,
 *              faux sinon.
 */
bool chercherArgument(const char **p, const char *chaine, int nbArguments) {

    int i;
    
    if(nbArguments == 1) {
        return false;
    }
    for (i = 1 ; i < nbArguments ; i++) {
        if (*p[i] == *chaine) {
            return true;
        }
    }
}

//int main(int argc, char *argv[]){
//    return 0;
//}

