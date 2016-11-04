/* UQAM - Automne 2016 - INF3135 - Groupe 21 - TP2
 *
 * countries.h - Fichier interface contenant les declarations
 * des differentes fonctions du fichier 'countries.c'
 *
 * @Auteur      Chretien Alexis (CHRA25049209)
 * @Version     4 novembre 2016 
 */
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#define NBPAYS 248
#define DELIM "|"

//
// Structures de donnees
//
typedef struct Pays {
    char nom[100];
    char code[4];
    char capitale[100];
    char region[20];
    char langues[100];
    char frontieres[100];
} Pays;


//
// Prototypes
//
void afficherAide();
int chercherArgument(const char **p, const char *chaine, int nbArguments);
char * trim(char *chaine);
void genererFichierPays();
Pays *recupererDonneesPays();
//(char *)retournerChaine(const char **p, int position);
