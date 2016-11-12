# Travail pratique 2

## Description

Projet visant à introduire les étudiants à la programmation modulaire en 
language C, à la gestion des dépendances et à la construction de suites de 
tests. 

Le projet consiste en un programme qui affiche differentes informations sur un 
ou plusieurs pays en fonction des arguments qui ont été entrés par l'utilisateur
lors de l'exécution du programme. Ces arguments incluent une option pour générer
des objets graphiques sous format *.dot* ou *.pgn*. 

## Auteurs

- Alexis Chrétien (CHRA25049209)

## Plateformes supportées

* CentOS release 6.8 (Final)

## Dépendances

* [Graphviz](http://graphviz.org/Download.php) : Logiciel de visualization      
  graphique.
* Le projet [countries](https://github.com/ablondin/countries) : Projet duquel
  on extrait les informations des différents pays. Le projet 
  *inf3135-aut2016-tp2* 
  contient le projet *countries* sous forme de sous-module. Pour mettre à jour 
  les données du sous-module *countries*, entrez la commande `make data` dans 
  le répertoire racine du projet *inf3135-aut2016-tp2*.
* La bibliothèque [jansson](http://digip.org/jansson/) : Bibliothèque C pour 
  encoder, décoder et manipuler des informations sous forme JSON.

## Installation

* Installez le logiciel *Graphviz* et la bibliothèque *Jansson* (si vous ne les
  avez pas déjà). 
* À la racine du projet, entrez la commande `make data` pour mettre à jour 
  le sous-modules *countries/* qui contient les informations sur les pays. 
* À la racine du projet, entrez la commande `make` pour compiler le projet
  et générer l'exécutable dans le répertoire *bin*.
* À la racine du projet, entrez la commande `make clean` pour nettoyer et 
  supprimer les fichiers *.o*. 
* À la racine du projet, entrez la commande `make test` pour exécuter les trois
  suites de tests contenues dans le répertoire *test/*.
* Pour lancer l'exécutable, entrez la commande `./tp2 [ARGUMENTS]` dans le 
  répertoire *bin/*.
* Entrez `./tp2 --help` dans le répertoire *bin/* pour plus d'information sur
  le fonctionnement du programme. 

## Fonctionnement

* L'argument `--output-format FORMAT` permet de spécifier le format de sortie.
  Les valeurs de *FORMAT* permises sont *text*, *dot* et *png*. Le format par 
  défaut est le format *text*. 
* L'argument `--output-filename FILENAME` permet de spécifier le nom du fichier.
  Cet argument est obligatoire pour le format de sortie *png*. Si cet argument
  argument est omis pour le format *text* ou *dot*, les informations générées 
  seront affichées à la sortie standard. Le nom du fichier ne doit contenir 
  qu'un seul point (pour spécifier l'extension) et ne doit être constitué que 
  de caractères alphanumériques. L'extension du fichier (*.txt*, *dot*, *.png*)
  doit être inclus et respecter le format de sortie. 
* L'argument `--show-languages` permet d'afficher les langues officielles des
  pays.
* L'argument `--show-capital` permet d'afficher la capitale des pays. 
* L'argument `--show-borders` permet d'afficher les codes des pays frontaliers. 
* L'argument `--show-flag` permet d'afficher le drapeau (n'a un effet que pour
  les formats *dot* et *png*).
* L'argument `--country COUNTRY` permet d'afficher les informations sur un pays
  en particulier. *COUNTRY* doit être le code à trois lettres du pays désiré. 
  Les lettres du code peuvent être en majuscules ou minuscules.
* L'argument `--region REGION` permet d'afficher les informations sur les pays
  d'une région. Les régions supportées sont *africa*, *americas*, *asia*, 
  *europe* et *oceania*. La case de l'argument *REGION* n'est pas considérée. 
* Si les arguments `--country COUNTRY` et `--region REGION` sont tous les deux
  spécifiés, seul l'argument `--country COUNTRY` sera considéré.
* Si aucun des arguments `--country COUNTRY` et `--region REGION` n'est 
  spécifié, tous les pays seront traités. 

#### Exemple d'exécution #1

NB: Toutes les exécutions se font à l'intérieur du répertoire de l'exécutable 
*tp2* (*bin/*).
Pour afficher à la sortie standard toutes les informations sur le Canada en
format *text* :

```
./tp2 --country can --show-languages --show-capital --show-borders
```
Ce qui affiche : 
```
Name: Canada
Code: CAN
Capital: Ottawa
Languages: English, French
Borders: USA
------------------------------
```

#### Exemple d'exécution #2

Pour créer un fichier *dot* contenant toutes les informations sur tous les pays :

```
./tp2 --output-format dot --output-filename monde.dot --show-languages --show-capital --show-borders --show-flag
```
Ce qui génère un fichier nommé *monde.dot* dans le répertoire *bin/*, qui 
commence et se termine ainsi : 
```
graph {
    abw [
        shape = none,
        label = <<table border="0" cellspacing="0">
            <tr><td align="center" border="1" fixedsize="true" width="200" height="100"><img src="../data/countries/data/abw.png" scale="trie"/></td></tr>
            <tr><td align="left" border="1"><b>Name</b>: Aruba</td></tr>
            <tr><td align="left" border="1"><b>Code</b>: ABW</td></tr>
            <tr><td align="left" border="1"><b>Capital</b>: Oranjestad</td></tr>
            <tr><td align="left" border="1"><b>Languages</b>: Dutch, Papiamento</td></tr>
            <tr><td align="left" border="1"><b>Borders</b>:</td></tr>
        </table>>
    ];
    afg [
        shape = none,
.
.
.
    zwe [
        shape = none,
        label = <<table border="0" cellspacing="0">
            <tr><td align="center" border="1" fixedsize="true" width="200" height="100"><img src="../data/countries/data/zwe.png" scale="trie"/></td></tr>
            <tr><td align="left" border="1"><b>Name</b>: Zimbabwe</td></tr>
            <tr><td align="left" border="1"><b>Code</b>: ZWE</td></tr>
            <tr><td align="left" border="1"><b>Capital</b>: Harare</td></tr>
            <tr><td align="left" border="1"><b>Languages</b>: Chewa, Chibarwe, English, Kalanga, Khoisan, Ndau, Northern Ndebele, Shona, Sotho, Tonga, Tsonga, Tswana, Venda, Xhosa, Zimbabwean Sign Language</td></tr>
            <tr><td align="left" border="1"><b>Borders</b>: BWA MOZ ZAF ZMB</td></tr>
        </table>>
    ];
afg -- chn;
afg -- ind;
afg -- irn;
.
.
.
tza -- zmb;
zaf -- zwe;
zmb -- zwe;
}

```
#### Exemple d'exécution #3

Pour générer une image *png* contenant toutes les informations sur tous les pays d'Amérique : 

```
./tp2 --region americas --output-format png output-filename americas.png --show-languages --show-capital --show-borders --show-flag 
```
Ce qui génère automatiquement [cette image](http://i.imgur.com/mbZeMSM.png) sous le nom d'*americas.png* 
dans le répertoire *bin/*.

## Contenu du projet

* **Makefile** : Ficher Makefile inculant un service de compilation des fichiers
  sources et de génération du fichier exécutable *tp2* (`make`), un service de
  nettoyage des fichiers du projet (`make clean`) et un service de mise à jour 
  des fichiers du sous-module *countries* (`make data`).
* **README.md** : Fichier markdown servant à la documentation et au formatage 
  de la page GitLab du projet.
* **bin/tp2** : Le fichier exécutable du projet
* **data/countries/** : Répertoire du sous-module *countries*, projet contenant
  les informations des différents pays.
* **srs/countries.c** : Fichier C contenant l'implémentation du fichier 
  *countries.h*
* **srs/countries.h** : Fichier header contenant les déclarations des fonctions
  du ficher *countries.c*. 
* **srs/tp2.c** : Fichier C source du projet produisant l'exécutable.
* **test/suite1.bats** : Série de tests sur les commandes invalides entrées par
  l'utilisateur.
* **test/suite2.bats** : Série de tests sur l'affichage du format *texte*.
* **test/suite3.bats** : Série de tests sur l'affichage du format *dot*.
* **.gitmodules** : Ficher servant à définir la liaison du module *countries* à
 son dépot-mère.
* **.gitlab-ci.yml** : Fichier *YAML* permettant de tester automatiquement les 
  suites de tests lors des *pushes* sur le dépot. 

## Références

** *Blondin Massé, Alexandre*, [Diapositives des cours](www.lacim.uqam.ca/~blondin/fr/inf3135).

## Statut

- [x] Definir les fonctions du fichier *countries.h* 

- [x] Implémentation des fonctions du fichier *countries.h* dans le fichier 
  *countries.c*

  - [x] void afficherAide()
  - [x] int chercherArgument(const \*\*p, const \*chaine, int argc)
  - [x] Pays * recupererDonneesPays(const char \*cle, bool doitAffPays, 
            bool doitAffReg)
  - [x] void traiterFormatTexte(Pays \* pays, const char \*nomFicher, 
            bool doitAffLan, bool doitAffCap, bool doitAffFro)
  - [x] void traiterFormatDot(Pays \* pays, const char \*nomFichier, 
            bool doitAffLan, bool doitAffCap, bool doitAffFro, bool doitAffDra)
  - [x] void traiterFormatPng(const char \*nomFichier, 
            const char \*nomFichierDot);
  - [x] void validerNomFichier(const char \*nomFichier, const char \*format);
  - [x] void trierLangues(Pays \*pays);

- [x] Implémentation du fichier *tp2.c* pour produire un exécutable fonctionnel 

- [ ] Créer des suites de tests et tester le projet
    
  - [x] Creation d'une suite de tests sur les commandes entrées par 
        l'utilisateur
  - [x] Creation d'une suite de tests pour le format texte
  - [x] Creation d'une suite de tests pour le format Dot
  - [ ] Création d'une suite de tests pour le format PNG, si réalisable. 
  - [ ] Validation des tests et corrections éventuelles appliquées au projet

- [ ] Optimisation 
