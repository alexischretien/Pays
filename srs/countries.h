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

void afficherAide();
int chercherArgument(const char **p, const char *chaine, int nbArguments);
char * trim(char *chaine);
void genererFichierPays(FILE *f);
//(char *)retournerChaine(const char **p, int position);
