/* UQAM - Automne 2016 - INF3135 - Groupe 21 - TP2
 *
 * countries.h - Fichier interface contenant les declarations
 * des differentes fonctions du fichier 'countries.c'
 *
 * @Auteur      Chretien Alexis (CHRA25049209)
 * @Version     6 novembre 2016 
 */
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<jansson.h>
#define NBPAYS 249

//
// Structure
//
typedef struct {
    const char *nom;
    const char *code;
    const char *capitale;
    const char *region;
    const char *langues;
    const char *frontieres[NBPAYS];
} Pays;

//
//
// Prototypes
//

/**
 * Affiche les informations d'aide lorsque l'argument '--help' est present.
 *
 * @return
 */
void afficherAide();

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
int chercherArgument(const char **p, const char *chaine, int nbArguments);

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
Pays * recupererDonneesPays(const char *cle, bool doitAffPays, 
        bool doitAffReg);

/**
 * Fonction qui genere un fichier contenant les informations demandees pour
 * le ou les pays contenus dans le pointeur de pays sous format texte. Si
 * 'nomFichier' est vide (l'utilisateur n'a pas donne de nom de fichier),
 * les donnees sont affichees a la sortie standard. 
 *
 * @param *pays       Pointeur de pays contenant les informations sur le
 *                    ou les pays a traiter.
 * @param *nomFichier Le nom du fichier a generer. Si vide, envoie les 
 *                    information a la sortie standard.                     
 * @param doitAffLan  Determine si la fonction doit afficher les langues.
 * @param doitAffCap  Determine si la fonction doit afficher la capitale.
 * @param doitAffFro  Determine si la fonction doit afficher les pays 
 *                    frontaliers.
 */
void traiterFormatTexte(Pays *pays, const char *nomFichier, bool doitAffLan,
        bool doitAffCap, bool doitAffFro);

/*
 * Fonction qui genere un fichier contenant les informations demandees pour
 * le ou les pays contenus dans le pointeur de pays sous format dot. Si 
 * 'nomFichier' est vide (l'utilisateur n'a pas donne de nom de fichier),
 * les donnees sont affichees a la sortie standard. 
 *
 * @param *pays         Pointeur pointant vers le ou les pays.
 * @param *nomFichier   Le nom du fichier a generer. Si vide, envoie les
 *                      informations a la sortie standard.
 * @param doitAffLan    Determine si la fonction doit afficher les langues
 * @param doitAffCap    Determine si la fonction doit afficher la capitale
 * @param doitAffFro    Determine si la fonction doit afficher les pays 
 *                      frontaliers
 * @param doitAffDra    Determine si la fonction doit afficher le drapeau
 * @return
 */
void traiterFormatDot(Pays *pays, const char * nomFichier, bool doitAffLan, 
        bool doitAffCap, bool doitAffFro, bool doitAffDra);
