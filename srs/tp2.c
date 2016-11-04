/* UQAM - Automne2016 - INF3135 - Groupe 21 - TP2
 *
 * tp2.c - Fichier source C de l'executable
 *
 * @Auteur      Chretien Alexis (CHRA25049209)
 * @Version     4 novembre 2016
 */

#include "countries.c"
#include<stdio.h>
#include<stdlib.h>
/**
 * Main
 */
int main(int argc, char *argv[]){
 
    int position;     // position des arguments recherchees
    char *info;     // donnees a afficher des pays recherchees
    bool doitAffLan = false;   // Determine si on doit afficher les langues officiels
    bool doitAffCap = false;   // Determine si on doit afficher la capitale
    bool doitAffFro = false;   // Determine si on doit afficher les frontaliers
    bool doitAffDra = false;   // Determine si on doit afficher le drapeau

    printf("test01\n");
    FILE *f = fopen("../data/countries/countries.json","r");
    printf("test02\n");
    genererFichierPays(f);
    fclose(f);

    if(chercherArgument((const char **)argv,"--show-languages\0",argc) != 0) {
        doitAffLan = true;
    }
    if(chercherArgument((const char **)argv,"--show-capital\0",argc) != 0) {
        doitAffCap = true;
    }
    if(chercherArgument((const char **)argv,"--show-borders\0",argc) != 0) {
        doitAffFro = true;
    }
    if(chercherArgument((const char **)argv,"--show-flag\0",argc) != 0) {
        doitAffDra = true;
    }
    if(chercherArgument((const char **)argv,"--help\0",argc) != 0 ){
        afficherAide();
        return 0; 
    }
    position = chercherArgument((const char **)argv,"--country\0",argc);
    if(position != 0) {
      //  info = recupererInformationPays(argv[position + 1]);    
    }
    else {
        position = chercherArgument((const char **)argv, "--region\0",argc);
        if(position != 0) {
            
        }   
    }
    return 0;
}

