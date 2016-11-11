/* UQAM - Automne2016 - INF3135 - Groupe 21 - TP2
 *
 * tp2.c - Fichier source C de l'executable
 *
 * @Auteur      Chretien Alexis (CHRA25049209)
 * @Version     10 novembre 2016
 */

#include "countries.c"
#include<stdio.h>
#include<stdlib.h>
#include<jansson.h>

/**
 * Main
 */
int main(int argc, char *argv[]) {
 
    int position = 0;     // position des arguments recherchees
    char *cle;
    char *formatSortie = FORMATPARDEFAUT;
    char *nomFichier;
    char *nomFichierDot;
    bool doitAffLan = false;   // Determine si on doit afficher les langues
                               // officiels
    bool doitAffCap = false;   // Determine si on doit afficher la capitale
    bool doitAffFro = false;   // Determine si on doit afficher les frontaliers
    bool doitAffDra = false;   // Determine si on doit afficher le drapeau
    bool doitAffPays = false;   // Determine si on doit afficher un pays en
                               // particulier
    bool doitAffReg = false;   // Determine si on doit afficher tous les pays
                               // d'une region donnee 
    Pays *pays;
    
    if(chercherArgument((const char **)argv,"--help\0",argc) != 0) {
        printf("%d\n",position);
        afficherAide();
        return 0;
    }
    position = chercherArgument((const char**)argv,"--output-format\0", argc);  
    if(position != 0) {
        formatSortie = argv[position + 1];
    }
    position = chercherArgument((const char**)argv,"--output-filename\0",argc);
    if(position != 0) {
        nomFichier = argv[position + 1];
    }
    else {
        nomFichier = "\0";
    }  
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
    position = chercherArgument((const char **)argv,"--country\0",argc);
    if(position != 0) {
        cle = argv[position + 1];
        doitAffPays = true;
    }
    else {
        position = chercherArgument((const char **)argv, "--region\0",argc);
        if(position != 0) {
            cle = argv[position + 1]; 
            doitAffReg = true;        
        }   
    }
  
    pays = recupererDonneesPays(cle, doitAffPays, doitAffReg);

    if (strcmp(formatSortie, "text\0") == 0) {
        traiterFormatTexte(pays, nomFichier, doitAffLan, doitAffCap, 
                doitAffFro); 
    }
    else if(strcmp(formatSortie, "dot\0") == 0) {

       traiterFormatDot(pays, nomFichier, doitAffLan, doitAffCap,
              doitAffFro, doitAffDra);
    }
    else if (strcmp(formatSortie, "png\0") == 0 ) {
        
        if(strcmp(nomFichier, "\0") == 0) {
            printf("Erreur: Le format de sortie 'png' requiere un nom de fichier");
            return 0;
        }
        else {
            nomFichierDot = malloc(strlen(nomFichier) + 4);
            //strcpy(nomFichierDot, strtok(nomFicher, ".");
            strcat(nomFichierDot, nomFichier);
            strcat(nomFichierDot, ".dot\0");

            traiterFormatDot(pays, nomFichierDot, doitAffLan, doitAffCap, 
                    doitAffFro, doitAffDra);
            traiterFormatPng(nomFichier, nomFichierDot);
        }
    }
    return 0;
}

