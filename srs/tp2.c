/* UQAM - Automne2016 - INF3135 - Groupe 21 - TP2
 *
 * tp2.c - Fichier source C de l'executable
 *
 */

#include "countries.c"
#include<stdio.h>
#include<stdlib.h>
/**
 * Main
 */
int main(int argc, char *argv[]){
 
    if(chercherArgument((const char **)argv,"--help\0",argc)){
        afficherAide();
        return 0; 
    }
    
    return 0;
}

