/* UQAM - Automne 2016 - INF3135 - Groupe 21 - TP2
 *
 * countries.c - Fichier source C contenant l'implementation
 * des fonctions declarees dans le fichier 'countries.h'
 *
 * @Auteur      Chretien Alexis (CHRA25049209)
 * @Version     10 novembre 2016
 */

#include "countries.h"

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

int chercherArgument(const char **p, const char *chaine, int nbArguments) {

    int i;
        
    for (i = 1 ; i < nbArguments ; i++) {
        if (strcmp(p[i],chaine) == 0){
            return i;
        }
    }
    return 0;
}

Pays * recupererDonneesPays(const char* cle, bool doitAffPays, 
        bool doitAffReg) {

    FILE *f = fopen("../data/countries/countries.json", "r");
    char *donnees;
    char *bufferLan[NBPAYS];
    int i; 
    int j;
    int k;
    size_t taille, index;
    json_error_t erreur;
    json_t *racine, *element;
    json_t *objPays, *objNom, *objNomCommun, *objCode, *objRegion, 
           *objCapitale, *objLangues, *tabFrontieres;   
    const char *nomCommun[NBPAYS], *code[NBPAYS], *region[NBPAYS], 
           *capitale[NBPAYS], *langues[NBPAYS];
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

        if ((doitAffPays == true && strcasecmp(cle, code[i]) == 0) ||
                (doitAffReg == true && strcasecmp(cle, region[i]) == 0) ||
                (doitAffPays == false && doitAffReg == false)) {
           
            pays[j].code = code[i];
            pays[j].region = region[i];
            
            objNom = json_object_get(objPays, "name");
            objNomCommun = json_object_get(objNom, "common");
            nomCommun[i] = json_string_value(objNomCommun);
            pays[j].nom = nomCommun[i];

            objCapitale = json_object_get(objPays, "capital");
            capitale[i] = json_string_value(objCapitale);     
            pays[j].capitale = capitale[i];

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
            pays[j].langues = bufferLan[i];

            tabFrontieres = json_object_get(objPays, "borders");

            k = 0;
            json_array_foreach(tabFrontieres, index, element) {
               pays[j].frontieres[k] = json_string_value(element);
               ++k;
            }
            pays[j].frontieres[k] = "\0";
            ++j;
        }
    }
    free(donnees); 
    pays[j].nom = "\0";
    pays[j].code = "\0";
    pays[j].region = "\0";
    pays[j].capitale = "\0";
    pays[j].langues = "\0";
    pays[j].frontieres[0] = "\0";

    paysRetour = pays;
    return paysRetour;
}    

void traiterFormatTexte(Pays *pays, const char *nomFichier, bool doitAffLan, 
        bool doitAffCap, bool doitAffFro) {

    int i = 0;
    int j;
    FILE *f = stdout;

    if(strcmp(nomFichier, "\0") != 0) {
        f = fopen(nomFichier, "w");
    }   
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
            fputs("Borders:", f);
            j = 0;
            while(strcmp(pays[i].frontieres[j], "\0") != 0) {
                fprintf(f, " %s", pays[i].frontieres[j]);
                ++j;
            }
            fprintf(f, "\n");
        } 
        fputs("------------------------------\n", f);
        ++i;       
    }
   if(strcmp(nomFichier, "\0") != 0) {
      fclose(f);
   } 
}

void traiterFormatDot(Pays *pays, const char *nomFichier, bool doitAffLan, 
        bool doitAffCap, bool doitAffFro, bool doitAffDra) {
  
    int i = 0;
    int j, k;
    char codeMin[NBPAYS][4];
    FILE *f = stdout;

    if (strcmp(nomFichier, "\0") != 0) {
        f = fopen(nomFichier, "w");
    }
    fputs("graph {\n", f);
    while(strcmp(pays[i].code, "\0") != 0) {
        
        for(j = 0 ; j < 4 ; j++) {
            codeMin[i][j] = tolower(pays[i].code[j]);
        }

        fprintf(f, "    %s [\n", codeMin[i]); 
        fputs("        shape = none,\n", f);
        fputs("        label = <<table border=\"0\" cellspacing=\"0\">\n", f);
        if (doitAffDra == true) {
            fputs("            <tr><td align=\"center\" border=\"1\" fixedsize=\"true\" width=\"200\" height=\"100\">", f);
            fprintf(f, "<img src=\"../data/countries/data/%s.png\" scale=\"trie\"/>", codeMin[i]);
            fputs("</td></tr>\n", f);
        }
        fprintf(f, "            <tr><td align=\"left\" border=\"1\"><b>Name</b>: %s</td></tr>\n", pays[i].nom);
        fprintf(f, "            <tr><td align=\"left\" border=\"1\"><b>Code</b>: %s</td></tr>\n", pays[i].code);
        if (doitAffCap == true) {
            fprintf(f, "            <tr><td align=\"left\" border=\"1\"><b>Capital</b>: %s</td></tr>\n", pays[i].capitale);
        }
        if (doitAffLan == true) {
            fprintf(f, "            <tr><td align=\"left\" border=\"1\"><b>Languages</b>: %s</td></tr>\n", pays[i].langues);
        }
        if (doitAffFro == true) {
            fprintf(f, "            <tr><td align=\"left\" border=\"1\"><b>Borders</b>:");
            k = 0;
            while(strcmp(pays[i].frontieres[k], "\0") != 0) {
                fprintf(f, " %s", pays[i].frontieres[k]);
                ++k;
            }
            fputs("</td></tr>\n", f);
        }
        fputs("        </table>>\n", f);
        fputs("    ];\n", f);
        ++i;
    }
    i = 0;
    while(strcmp(pays[i].code, "\0") != 0) {
        j = i + 1;
        while(strcmp(pays[j].code, "\0") != 0) {
            k = 0;
            while(strcmp(pays[j].frontieres[k], "\0") != 0) {
                if(strcmp(pays[i].code, pays[j].frontieres[k]) == 0) {
                    fprintf(f, "%s -- %s;\n", codeMin[i], codeMin[j]);
                }
                ++k;
            } 
            ++j;
        }
        ++i;
    }
    fputs("}\n", f);
    
    if(strcmp(nomFichier, "\0") != 0) {
        fclose(f);
    }
}

void traiterFormatPng(const char  *nomFichier, const char *nomFichierDot) {
    char *commande;

    commande = malloc(35*sizeof(char) + strlen(nomFichier) + strlen(nomFichierDot));
    commande[0] = '\0';
    strcat(commande, "neato -Goverlap=false -Tpng -o ");
    strcat(commande, nomFichier);
    strcat(commande, " ");
    strcat(commande, nomFichierDot);
    system(commande);
    remove(nomFichierDot); 
}

bool validerNomFichier(const char *nomFichier, const char *format) {

    int i;
    char *chaine;

    if(strcmp(format, "text\0") == 0) {
        format = malloc(4*sizeof(char));
        format = "txt\0";
    }   
    chaine = malloc(strlen(nomFichier) + 1 );
    chaine[0] = '\0';
    strcpy(chaine, nomFichier);
    
    if(strcmp(strtok(chaine, "."), nomFichier) == 0) {
        printf("Erreur. Extension \".%s\" du fichier manquant.\n", format);
        return false;
     }
    if(strcmp(strtok(NULL, "."), format) != 0) {
        printf("Erreur. L'extension du fichier devrait etre \".%s\".\n", format);
        return false;
    }
    if(strtok(NULL, ".")  != NULL) {
        printf("Erreur. Le nom du fichier ne doit contenir qu'un seul point.\n");
        return false;
    }

    for(i = 0 ; chaine[i] != '\0' ;  i++) {
        if(chaine[i] < 48 || chaine[i] > 122 ||
                (chaine[i] > 57 && chaine[i] < 65) ||
                 (chaine[i] > 90 && chaine[i] < 97)) {
            printf("Erreur. Le caractere '%c' est illegal pour le nom du fichier.\n", chaine[i]);
            return false;
        }
    }
    return true;

}
