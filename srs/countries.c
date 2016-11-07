/* UQAM - Automne 2016 - INF3135 - Groupe 21 - TP2
 *
 * countries.c - Fichier source C contenant l'implementation
 * des fonctions declarees dans le fichier 'countries.h'
 *
 * @Auteur      Chretien Alexis (CHRA25049209)
 * @Version     6 novembre 2016
 */
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<jansson.h>
#include "countries.h"
#define FORMATPARDEFAUT "text\0"
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
 * @param p             Pointeur de pointeurs de caracteres, pointant au debut
 *                      du tableau de chaine de caracteres argv.
 * @param chaine        Chaine recherchee.
 * @param nbArguments   Nombre de chaine contenues dans la commande d'execution
 *                      (argc).
 * @return              La position de la chaine dans la commande, 0 si la 
 *                      chaine est absente.
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
 * capitale, aux langues et aux pays frontaliers d'un pays, de tous les pays 
 * d'une region ou de tous les pays contenus dans le fichier JSON.
 *
 * @param *cle          chaine de caractere contenant soit le code a trois
 *                      chiffre du pays recherche (si on ne cherche qu'un seul
 *                      pays), le nom de la region des pays recherches, ou rien
 *                      si la fonction doit traiter tous les pays.
 * @param doitAffPays   Determine si la fonction doit recuperer les informations
 *                      d'un seul pays.
 * @param doitAffReg    Determine si la fonction doit recuperer les informations
 *                      de tous les pays d'une region (NB : si 'doitAffPays' et
 *                      'doitAffRegions' tous les deux 'false', alors la 
 *                      fonction recupere les informations sur tous les pays.       
 * @return              Le pointeur de pays contenant les informations du ou 
 *                      des pays desires. 
 */
Pays * recupererDonneesPays(const char* cle, bool doitAffPays, 
        bool doitAffReg) {

    FILE *f = fopen("../data/countries/countries.json", "r");
    char *donnees;
    char *bufferLan[NBPAYS], *bufferFro[NBPAYS];
    int i, j;
    size_t taille, index;
    json_error_t erreur;
    json_t *racine, *element;
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
    j = 0;

    for (i = 0 ; i < json_array_size(racine) ; i++) {

        objPays = json_array_get(racine,i);

        objCode = json_object_get(objPays, "cca3");
        code[i] = json_string_value(objCode);

        objRegion = json_object_get(objPays, "region");
        region[i] = json_string_value(objRegion);

        if (doitAffPays == true && strcasecmp(cle, code[i]) == 0 ||
                doitAffReg == true && strcasecmp(cle, region[i]) == 0 ||
                doitAffPays == false && doitAffPays == false) {

            objNom = json_object_get(objPays, "name");
            objNomCommun = json_object_get(objNom, "common");
            nomCommun[i] = json_string_value(objNomCommun);

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

            tabFrontieres = json_object_get(objPays, "borders");
            bufferFro[i] = calloc(sizeof(char),100);
            json_array_foreach(tabFrontieres, index, element) {
                frontieres[i] = json_string_value(element);
                strncat(bufferFro[i], frontieres[i], strlen(frontieres[i]));
                strncat(bufferFro[i], " ", 1);
            }
            strncat(bufferFro[i], "\0", 1);
        }
        pays[j].nom = nomCommun[i];
        pays[j].code = code[i];
        pays[j].region = region[i];
        pays[j].capitale = capitale[i];
        pays[j].langues = bufferLan[i];
        pays[j].frontieres = bufferFro[i];
        ++j;
    }
    free(donnees); 
    pays[j].nom = "\0";
    pays[j].code = "\0";
    pays[j].region = "\0";
    pays[j].capitale = "\0";
    pays[j].langues = "\0";
    pays[j].frontieres = "\0";

    paysRetour = pays;
    return paysRetour;
}    

/**
 * Fonction qui affiche a la sortie standard les informations demandees pour
 * le ou les pays contenus dans le pointeur de pays.
 *
 * @param *pays       Pointeur de pays contenant les informations sur le
 *                    ou les pays a traiter.
 * @param doitAffLan  Determine si la fonction doit afficher les langues.
 * @param doitAffCap  Determine si la fonction doit afficher la capitale.
 * @param doitAffFro  Determine si la fonction doit afficher les pays 
 *                    frontaliers.
 */
void afficherFormatTexte(Pays *pays, bool doitAffLan, bool doitAffCap, 
        bool doitAffFro) {

    int i = 0;
    
    while(strcmp(pays[i].code, "\0") != 0) {  
        printf("i: %d\n", i);        
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
        printf("------------------------------\n");
        ++i;
        
    } 
}
/**
 * Genere un fichier contenant les informations en format texte pour le ou les 
 * pays contenus dans le pointeur de pays.
 *
 * @param *pays         Pointeur pointant vers le ou les pays.
 * @param *nomFichier   Le nom du fichier cree.
 * @param doitAffLan    Determine si la fonction doit imprimer les langues 
 * @param doitAffCap    Determine si la fonction doit imprimer la capitale
 * @param doitAffFro    Determine si la fonction doit imprimer les pays
 *                      frontaliers
 * @return
 */
void genererFichierFormatTexte(Pays *pays, const char *nomFichier, 
        bool doitAffLan, bool doitAffCap, bool doitAffFro) {
    
    printf("test1\n");
    FILE *f;
    f = fopen(nomFichier,"w");
    int i = 0;

    while(strcmp(pays[i].code, "\0") != 0) {
        fprintf(f, "Name: %s\n", pays[i].nom);
        fprintf(f, "Code: %s\n", pays[i].code);
        if (doitAffCap == true) {
            fprintf(f, "Capital: %s\n", pays[i].capitale);
        }
        if (doitAffLan == true) {
            fprintf(f, "Languages: %s\n", pays[i].langues);
        }
        if (doitAffFro == true) {
            fprintf(f, "Borders: %s\n", pays[i].frontieres);
        }
        fprintf(f, "------------------------------\n");
        ++i;
    }
    fclose(f);
}

/*
 * Affiche a la sortie standard les informations en format dot pour le ou les 
 * pays contenus dans le pointeur de pays.
 *
 * @param *pays         Pointeur pointant vers le ou les pays.
 * @param doitAffLan    Determine si la fonction doit afficher les langues
 * @param doitAffCap    Determine si la fonction doit afficher la capitale
 * @param doitAffFro    Determine si la fonction doit afficher les pays 
 *                      frontaliers
 * @param doitAffDra    Determine si la fonction doit afficher le drapeau
 * @return
 */
void afficherFormatDot(Pays *pays, bool doitAffLan, bool doitAffCap, 
        bool doitAffFro, bool doitAffDra) {
    
    int i, j;
    char codeMin[4];
            printf("graph {\n");
    while(strcmp(pays[i].code, "\0") != 0) {
        for(j = 0 ; j < sizeof(codeMin) ; j++) {
            codeMin[j] = tolower(pays[i].code[j]);
        }
        printf("    %s [\n", codeMin); 
        printf("        shape = none,\n");
        printf("        label = <<table border=\"0\" cellspacing=\"0\">\n");
        if (doitAffDra == true) {
            printf("            <tr><td align=\"center\" border=\"1\" fixedsize=\"true\" width=\"200\" height=\"100\">\n");
            printf("              <img src=\"../data/countries/data/%s.png\" scale=\"trie\"/>\n",codeMin);
            printf("            </td></tr>\n");
        }
        printf("            <tr><td align=\"left\" border=\"1\"><b>Name</b>: %s</td></tr>\n", pays[i].nom);
        printf("            <tr><td align=\"left\" border=\"1\"><b>Code</b>: %s</td></tr>\n", pays[i].code);
        if (doitAffCap == true) {
            printf("            <tr><td align=\"left\" border=\"1\"><b>Capital</b>: %s</td></tr>\n", pays[i].capitale);
        }
        if (doitAffLan == true) {
            printf("            <tr><td align=\"left\" border=\"1\"><b>Languages</b>: %s</td></tr>\n", pays[i].langues);
        }
        if (doitAffFro == true) {
            printf("            <tr>td align=\"left\" border=\"1\"><b>Borders</b>: %s</td></tr>\n", pays[i].frontieres);
        }
        printf("        </table>>\n");
        printf("    ];\n");
        ++i;
    }
    printf("}\n");
}
