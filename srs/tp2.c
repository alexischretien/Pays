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
#include<jansson.h>

/**
 * Main
 */
int main(int argc, char *argv[]){
 
    int position = 0;     // position des arguments recherchees
    char *paysOuRegion;
    bool doitAffLan = false;   // Determine si on doit afficher les langues
                               // officiels
    bool doitAffCap = false;   // Determine si on doit afficher la capitale
    bool doitAffFro = false;   // Determine si on doit afficher les frontaliers
    bool doitAffDra = false;   // Determine si on doit afficher le drapeau
    bool doitAffPay = false;   // Determine si on doit afficher un pays en
                               // particulier
    bool doitAffReg = false;   // Determine si on doit afficher tous les pays
                               // d'une region donnee   
    
    if(chercherArgument((const char **)argv,"--help\0",argc) != 0) {
        printf("%d\n",position);
        afficherAide();
        return 0;
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
        paysOuRegion = malloc(strlen(argv[position+1]));
        paysOuRegion[0] = '\0';
        strcpy(paysOuRegion,argv[position+1]);
        doitAffPay = true;
    }
    else {
        position = chercherArgument((const char **)argv, "--region\0",argc);
        if(position != 0) {
            paysOuRegion = malloc(strlen(argv[position+1]));
            paysOuRegion[0] = '\0';
            strcpy(paysOuRegion,argv[position+1]);  
            doitAffReg = true;        
        }   
    }
    afficherInfoTexte(paysOuRegion, doitAffLan, doitAffCap, doitAffFro, 
                        doitAffPay, doitAffReg);
    return 0;
}

