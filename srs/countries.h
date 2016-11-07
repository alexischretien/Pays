/* UQAM - Automne 2016 - INF3135 - Groupe 21 - TP2
 *
 * countries.h - Fichier interface contenant les declarations
 * des differentes fonctions du fichier 'countries.c'
 *
 * @Auteur      Chretien Alexis (CHRA25049209)
 * @Version     6 novembre 2016 
 */
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<jansson.h>
#define NBPAYS 249

//
// Structure
//
typedef struct {
    const char *nom;
    const char *code;
    const char *capitale;
    const char *region;
    const char *langues;
    const char *frontieres;
} Pays;
//
//
// Prototypes
//
void afficherAide();
int chercherArgument(const char **p, const char *chaine, int nbArguments);
Pays * recupererDonneesPays(const char *cle, bool doitAffPays, 
        bool doitAffReg);
void afficherFormatTexte(Pays *pays, bool doitAffLan,bool doitAffCap, 
        bool doitAffFro);
void genererFichierFormatTexte(Pays *pays, const char *nomFichier,
        bool doitAffLan, bool doitAffCap, bool doitAffFro);
void afficherFormatDot(Pays *pays, bool doitAffLan, bool doitAffCap, 
        bool doitAffFro, bool doitAffDra);
