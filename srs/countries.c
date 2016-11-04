/* UQAM - Automne 2016 - INF3135 - Groupe 21 - TP2
 *
 * countries.c - Fichier source C contenant l'implementation
 * des fonctions declarees dans le fichier 'countries.h'
 *
 * @Auteur      Chretien Alexis (CHRA25049209)
 * @Version     4 novembre 2016
 */
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "countries.h"

/**
 * Affiche les informations d'aide lorsque l'argument --help est present
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
 * caracteres desiree et qui retourne la position de la chaine dans la
 * commande.
 *
 * @param       **p - pointeur de pointeurs de caracteres, pointant au debut
 *              du tableau de chaine de caracteres argv
 * @param       *chaine - chaine recherchee
 * @param       nombre de chaine contenues dans la commande d'execution (argc)              
 * @return      La position de la chaine dans la commande, 0 si la chaine est
 *              absente.
 */
int chercherArgument(const char **p, const char *chaine, int nbArguments) {

    int i;
        
    for (i = 1 ; i < nbArguments ; i++) {
        if (*p[i] == *chaine) {
            return i;
        }
    }
    return 0;
}

/**
 * Prend un tableau de caracteres et renvoie la meme chaine en ignorant les
 * virgules, les guillemets et les crochets.
 *
 * @param chaine    la chaine de caracteres a traiter
 * @return          la chaine de caracteres traitee
 */
char * trim(char chaine[]) {
    
    int i = 0;
    int j = 0;
    char *chaineRetour = malloc(strlen(chaine) + 1); 

    *chaineRetour = *chaineRetour - strlen(chaine) - 1; 

    while(chaine[i] != '\0') {
        if (chaine[i] != ',' && chaine[i] != '\"' &&
                chaine[i] != '[' && chaine[i] != ']') {
            chaineRetour[j] = chaine[i];
            j++;
        }
        i++;
        
        
    }   
    chaineRetour[j] = '\0';
    return chaineRetour;
}

/**
 * Genere un fichier text a partir des informations contenues dans le fichier
 * passe en argument (countries.json). Chaque ligne du fichier a pour format
 * NOM_COMMON_PLAY|CODE_PAYS|CAPITALES|LANGAGE(S)|PAY(S) FRONTALIER(S)|
 *
 * @param f     le fichier a lire (../data/countries/countries.json)
 * @return
 */
void genererFichierPays() {
    
    FILE *f = fopen("../data/countries/countries.json", "r");
    FILE *w = fopen("../data/countries.txt", "w");   
    char ligne[512];
    char chaine1[256];
    char chaine2[256];

    while(fgets(ligne,512,f)) {         
         sscanf(ligne,"%s %[^\n]", chaine1, chaine2);

         if(strcmp(chaine1,"\"common\":") == 0) {         
             fprintf(w,"%s|", trim(chaine2));

             while(fgets(ligne,512,f)) {
                sscanf(ligne, "%s %[^\n]", chaine1, chaine2);

                if(strcmp(chaine1, "\"cca3\":") == 0 ||
                        strcmp(chaine1, "\"capital\":") == 0 ||
                        strcmp(chaine1, "\"region\":") == 0 ){
                    fprintf(w, "%s|", trim(chaine2));
                }
                else if(strcmp(chaine1, "\"languages\":") == 0) {

                    if(strcmp(chaine2, "{") != 0 ) {
                        fprintf(w, "|");
                        continue;
                    }   
                    fgets(ligne, 512, f);
                    sscanf(ligne, "%s %[^\n]", chaine1, chaine2);
                    fprintf(w, "%s", trim(chaine2));
                    while(fgets(ligne,128,f)) { 
                       sscanf(ligne, "%s %[^\n]", chaine1, chaine2);
                        
                       if(strcmp(chaine1, "},") == 0) {
                           break;
                       }
                       fprintf(w, ", %s", trim(chaine2));   
                    }
                    fprintf(w,"|");
                }
                else if(strcmp(chaine1,"\"borders\":") == 0) {
                    fprintf(w, "%s|\n", trim(chaine2));
                    break;
                }
                
             }
         }
    }
    fclose(f);
    fclose(w);
}
/**
 * Fonctions qui traite les donnees contenues dans le fichier 'countries.txt' 
 * et qui retourne un pointeur de structures Pays contenant toutes les 
 * informations de tous les pays
 *
 * @return      le pointeur de Pays contenant toutes les informations sur
 *              tous les pays
 */   
Pays *recupererDonneesPays() {
    
    FILE *f = fopen("../data/countries.txt", "r");
    char *pt;
    char ligne[512];
    int i = 0; 
    Pays *monde;
    printf("sizeof(Pays) : %d\n",sizeof(Pays));

    monde = malloc((NBPAYS) * sizeof(Pays));
 
    while(fgets(ligne,512,f)) {

          pt = malloc(strlen(ligne)+1);
          pt[0] = '\0';
          strcpy(pt,ligne);
          strcpy(monde[i].nom, strsep(&pt,DELIM));
          strcpy(monde[i].code, strsep(&pt, DELIM));
          strcpy(monde[i].capitale, strsep(&pt, DELIM));
          strcpy(monde[i].region, strsep(&pt, DELIM));
          strcpy(monde[i].langues, strsep(&pt, DELIM));
          strcpy(monde[i].frontieres, strsep(&pt,DELIM));
        ++i;
    }
    return monde;
}
                   

          

                 

