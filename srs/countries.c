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
#include<jansson.h>
#include "countries.h"

/**
 * Affiche les informations d'aide lorsque l'argument '--help' est present.
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
 * @param p       Pointeur de pointeurs de caracteres, pointant au debut
 *                du tableau de chaine de caracteres argv
 * @param chaine  Chaine recherchee
 * @param         Nombre de chaine contenues dans la commande d'execution (argc)
 * @return        La position de la chaine dans la commande, 0 si la chaine est
 *                absente.
 */
int chercherArgument(const char **p, const char *chaine, int nbArguments) {

    int i;
        
    for (i = 1 ; i < nbArguments ; i++) {
        if (strcmp(p[i],chaine) == 0){
            return i;
        }
    }
    return 0;
}

/**
 * Fonction qui affiche les informations demandee sur tous les pays, les pays 
 * d'une region en particulier, ou d'un seul pays en fonction de la commande 
 * entree par l'utilisateur.
 *
 * @param paysOuRegion      Chaine de caractere contenant soit le code a trois
 *                          lettre du pays ou le nom de la region que l'on 
 *                          souhaite obtenir des informations, ou rien si
 *                          l'on souhaite obtenir les informations sur tous 
 *                          les pays.
 * @param doitAffLan        Determine si l'on doit afficher les langues.
 * @param doitAffCap        Determine si l'on doit afficher la capitale.
 * @param doitAffFro        Determine si l'on doit afficher le code a trois 
 *                          lettres des pays frontaliers.
 * @param doitAffPay        Determine si l'on doit afficher les informations
 *                          sur un seul pays en particulier (si 'doitAffPay'
 *                          et 'doitAffReg' sont tous les deux 'false', doit 
 *                          Afficher les informations sur tous les pays).
 * @param doitAffReg        Determine si l'on afficher les informations sur
 *                          les pays de toutes les regions.
 * @return
 */
void afficherInfoTexte(const char *paysOuRegion, bool doitAffLan,
        bool doitAffCap, bool doitAffFro, bool doitAffPay, bool doitAffReg) {

    FILE *f = fopen("../data/countries/countries.json", "r");
    char *donnees;
    int i;
    size_t taille, index;
    json_error_t erreur;
    json_t *racine;
    json_t *array, *element, *obj;
    json_t *objPays, *objNom, *objNomCommun, *objCode, *objRegion, 
           *objCapitale, *objLangues, *objFrontieres, *tabFrontieres;   
    const char *nomCommun, *code, *region, *capitale, *langues, *frontieres;
    void *iter;

    fseek(f,0,SEEK_END);
    taille = ftell(f);

    rewind(f);

    donnees = malloc(taille + 1);
    fread(donnees, taille, 1, f);
    donnees[taille] = '\0';
         
    racine = json_loads(donnees, 0, &erreur);

    for (i = 0 ; i < json_array_size(racine) ; i++) {

        objPays = json_array_get(racine,i);

        objNom = json_object_get(objPays, "name");
        objNomCommun = json_object_get(objNom, "common");
        nomCommun = json_string_value(objNomCommun);     

        objCode = json_object_get(objPays, "cca3");
        code = json_string_value(objCode);

        objRegion = json_object_get(objPays, "region");
        region = json_string_value(objRegion);
       
        objCapitale = json_object_get(objPays, "capital");
        capitale = json_string_value(objCapitale);     
       
        if (doitAffPay == true && strcasecmp(paysOuRegion, code) == 0 ||   
            doitAffReg == true && strcasecmp(paysOuRegion, region) == 0 ||
               (doitAffPay == false && doitAffReg == false)) {
            printf("Name: %s\n", nomCommun);
            printf("Code: %s\n", code);

            if (doitAffCap == true) {
                printf("Capital: %s\n", capitale);
            }
            if (doitAffLan == true) {
                objLangues = json_object_get(objPays, "languages");
                iter = json_object_iter(objLangues);
                element = json_object_iter_value(iter);
                langues = json_string_value(element);

                printf("Languages: %s", langues);
                iter = json_object_iter_next(objLangues, iter);

                 while(iter != NULL) {
                    element = json_object_iter_value(iter);
                    langues = json_string_value(element);
                    printf(", %s", langues);
                    iter = json_object_iter_next(objLangues, iter);

                }  
                printf("\n");
            }
            if(doitAffFro == true) {
                tabFrontieres = json_object_get(objPays, "borders");
                printf("Borders: ");
                json_array_foreach(tabFrontieres, index, element) {
                    frontieres = json_string_value(element);
                    printf("%s ", frontieres);
                }
                printf("\n");
            }
            printf("-------------------------------\n");
        }
    } 
}    















