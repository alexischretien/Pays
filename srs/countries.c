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
 * Fonction qui retourne un pointeur de pays contenant les informations 
 * relatives au noms commun, au code a trois lettres, a la region, a la
 * capitale, aux langues et aux pays frontaliers de tous les pays documentes
 * dans le fichier '../data/countries/countries.json'.
 *
 * @return      Le pointeur de pays 
 */
Pays * recupererDonneesPays() {

    FILE *f = fopen("../data/countries/countries.json", "r");
    char *donnees;
    char *bufferLan[NBPAYS], *bufferFro[NBPAYS];
    int i;
    size_t taille, index;
    json_error_t erreur;
    json_t *racine;
    json_t *array, *element, *obj;
    json_t *objPays, *objNom, *objNomCommun, *objCode, *objRegion, 
           *objCapitale, *objLangues, *objFrontieres, *tabFrontieres;   
    const char *nomCommun[NBPAYS], *code[NBPAYS], *region[NBPAYS], 
          *capitale[NBPAYS], *langues[NBPAYS], *frontieres[NBPAYS];
    void *iter;

    Pays pays[NBPAYS];
    Pays *paysRetour;

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
        nomCommun[i] = json_string_value(objNomCommun);     
        pays[i].nom = nomCommun[i];

        objCode = json_object_get(objPays, "cca3");
        code[i] = json_string_value(objCode);
        pays[i].code = code[i];

        objRegion = json_object_get(objPays, "region");
        region[i] = json_string_value(objRegion);
        pays[i].region = region[i];

        objCapitale = json_object_get(objPays, "capital");
        capitale[i] = json_string_value(objCapitale);     
        pays[i].capitale = capitale[i];

        objLangues = json_object_get(objPays, "languages");
        iter = json_object_iter(objLangues);
        element = json_object_iter_value(iter);
        langues[i] = json_string_value(element);
        bufferLan[i] = calloc(sizeof(char), 150);
        bufferLan[i] = (char *)langues[i];
        iter = json_object_iter_next(objLangues, iter);
        while(iter != NULL) {
            element = json_object_iter_value(iter);
            langues[i] = json_string_value(element);
            iter = json_object_iter_next(objLangues, iter);
            strncat(bufferLan[i], ", ", 3);
            strncat(bufferLan[i], langues[i], strlen(langues[i]) + 1);
        }
        strncat(bufferLan[i], "\0", 1);

        pays[i].langues = bufferLan[i];

        tabFrontieres = json_object_get(objPays, "borders");
        bufferFro[i] = calloc(sizeof(char),50);
        json_array_foreach(tabFrontieres, index, element) {
            frontieres[i] = json_string_value(element);
            strncat(bufferFro[i], frontieres[i], strlen(frontieres[i]));
            strncat(bufferFro[i], " ", 1);
        }
        strncat(bufferFro[i], "\0", 1);
        pays[i].frontieres = bufferFro[i];
    } 
    paysRetour = pays;
    return paysRetour;
}    

/**
 * Fonction qui affiche a la sortie standard les informations demandes pour
 * un pays, pour les pays d'une region ou pour tous les pays.
 *
 * @param *pays       Pointeur de pays contenant toutes les informations sur
 *                    tous les pays.
 * @param *paysOuReg  Le code a trois lettre ou le nom de la region du/des pays 
 *                    demandes. Vide si la fonction doit afficher tous les pays.
 * @param doitAffPays Determine si la fonction doit afficher un pays en 
 *                    particulier (et seulement ce pays).
 * @param doitAffReg  Determine si la fonction doit afficher les pays d'une 
 *                    region en particulier. (NB : si 'doitAffPays' et 
 *                    'doitAffReg' tout deux 'false', la fonction doit afficher
 *                    les informations demandees pour tous les pays.
 * @param doitAffLan  Determine si la fonction doit afficher les langues.
 * @param doitAffCap  Determine si la fonction doit afficher la capitale.
 * @param doitAffFro  Determine si la fonction doit afficher les pays 
 *                    frontaliers.
 */
void afficherInfoTexte(Pays *pays, const char* paysOuReg, bool doitAffPays,
        bool doitAffReg, bool doitAffLan, bool doitAffCap, bool doitAffFro) {
    int i;
    printf("size dans afficher: %d\n", sizeof(pays));
    for (i = 0 ; i < NBPAYS ; i++) {
        if (doitAffPays == true && strcasecmp(paysOuReg, pays[i].code) == 0  ||
                doitAffReg==true && strcasecmp(paysOuReg, pays[i].region)==0 ||
                (doitAffPays == false && doitAffReg == false)) {
            printf("Name: %s\n", pays[i].nom);
            printf("Code: %s\n", pays[i].code);
            if (doitAffCap == true) {
                printf("Capital: %s\n", pays[i].capitale);
            }
            if (doitAffLan == true) {
                printf("Languages: %s\n", pays[i].langues);
            }
            if (doitAffFro == true) {
                printf("Borders: %s\n", pays[i].frontieres);
            } 
            printf("-------------------------------\n");
        }
    } 
}

