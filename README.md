# Pays

## Description

Projet visant � introduire les �tudiants � la programmation modulaire en 
language C, � la gestion des d�pendances et � la construction de suites de 
tests. 

Le projet consiste en un programme qui affiche differentes informations sur un 
ou plusieurs pays en fonction des arguments qui ont �t� entr�s par l'utilisateur
lors de l'ex�cution du programme. Ces arguments incluent une option pour g�n�rer
des objets graphiques sous format `.dot` ou `.pgn`. 

## Auteurs

- Alexis Chr�tien

## Plateformes support�es

* CentOS Linux release 7.4.1708 (Core)
 
## D�pendances

* [Graphviz](http://graphviz.org/Download.php) : Logiciel de visualization graphique.
* Le projet [countries](https://github.com/ablondin/countries) : Projet duquel on 
  extrait les informations des diff�rents pays, inclus sous forme de sous-module.
* La biblioth�que [jansson](http://digip.org/jansson/) : Biblioth�que C pour 
  encoder, d�coder et manipuler des informations sous forme JSON.
* Le syst�me de tests automatis�s [Bats](https://github.com/sstephenson/bats) : Outil
  permettant le lancement des s�ries tests contenues dans le r�pertoire `test/`.

## Installation

* Installez le logiciel *Graphviz* et la biblioth�que *Jansson* (si vous ne les
  avez pas d�j�). 
* � la racine du projet, entrez la commande `make data` pour mettre � jour 
  le sous-modules `countries/` contenant les informations sur les pays. 
* � la racine du projet, entrez la commande `make` pour compiler le projet
  et g�n�rer l'ex�cutable dans le r�pertoire `bin/`.
* � la racine du projet, entrez la commande `make clean` pour  supprimer les fichiers 
  de format `.o`, `.txt`, `.dot`, `.png` ainsi que l'ex�cutable `bin/tp2`. 
* � la racine du projet, entrez la commande `make test` pour ex�cuter les trois
  suites de tests contenues dans le r�pertoire `test/`.
* Pour lancer l'ex�cutable, entrez la commande `./tp2 [ARGUMENTS]` dans le 
  r�pertoire `bin/`.
* Entrez `./tp2 --help` dans le r�pertoire `bin/` pour plus d'informations sur
  le fonctionnement du programme. 

## Fonctionnement

* L'argument `--output-format FORMAT` permet de sp�cifier le format de sortie.
  Les valeurs de `FORMAT` permises sont `text`, `dot` et `png`. Le format par 
  d�faut est le format `text`. 
* L'argument `--output-filename FILENAME` permet de sp�cifier le nom du fichier.
  Cet argument est obligatoire pour le format de sortie `png`. Si cet argument
  est omis pour le format `text` ou `dot`, les informations g�n�r�es seront 
  affich�es � la sortie standard. Le nom du fichier ne doit contenir 
  qu'un seul point (pour sp�cifier l'extension) et ne doit �tre constitu� que 
  de caract�res alphanum�riques. L'extension du fichier (`.txt`, `.dot`, `.png`)
  doit �tre inclus et respecter le format de sortie. 
* L'argument `--show-languages` permet d'afficher les langues officielles des
  pays.
* L'argument `--show-capital` permet d'afficher la capitale des pays. 
* L'argument `--show-borders` permet d'afficher les codes des pays frontaliers. 
* L'argument `--show-flag` permet d'afficher le drapeau (n'a un effet que pour
  les formats `dot` et `png`).
* L'argument `--country COUNTRY` permet d'afficher les informations sur un pays
  en particulier. `COUNTRY` doit �tre le code � trois lettres du pays d�sir�. 
  Les lettres du code peuvent �tre en majuscules ou minuscules.
* L'argument `--region REGION` permet d'afficher les informations sur les pays
  d'une r�gion. Les r�gions support�es sont `africa`, `americas`, `asia`, 
  `europe` et `oceania`. La case de l'argument `REGION` n'est pas consid�r�e. 
* Si les arguments `--country COUNTRY` et `--region REGION` sont tous les deux
  sp�cifi�s, seul l'argument `--country COUNTRY` sera consid�r�.
* Si aucun des arguments `--country COUNTRY` et `--region REGION` n'est 
  sp�cifi�, tous les pays seront trait�s. 

#### Exemple d'ex�cution #1

NB: Toutes les ex�cutions se font � l'int�rieur du r�pertoire de l'ex�cutable 
`tp2` (`bin/`).

Pour afficher � la sortie standard toutes les informations sur le Canada en
format `text` :

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

#### Exemple d'ex�cution #2

Pour cr�er un fichier `dot` contenant toutes les informations sur tous les pays :

```
./tp2 --output-format dot --output-filename monde.dot --show-languages --show-capital --show-borders --show-flag
```
Ce qui g�n�re un fichier nomm� `monde.dot` dans le r�pertoire `bin/`, qui 
commence et se termine ainsi (les trois points verticaux repr�sentent des lignes
ignor�es � fin de pr�senter un exemple plus court) : 
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
#### Exemple d'ex�cution #3

Pour g�n�rer une image `png` contenant toutes les informations sur tous les pays d'Am�rique : 

```
./tp2 --region americas --output-format png --output-filename americas.png --show-languages --show-capital --show-borders --show-flag 
```
Ce qui g�n�re automatiquement [cette image](http://i.imgur.com/mbZeMSM.png) sous le nom d'`americas.png` 
dans le r�pertoire `bin/`.

## Contenu du projet

* `Makefile` : Ficher Makefile inculant diff�rents services pour g�rer,
   entretenir et tester le projet. 
* `README.md` : Fichier markdown servant � la documentation et au formatage 
   de la page GitLab du projet.
* `bin/tp2` : Le fichier ex�cutable du projet.
* `data/countries/` : R�pertoire du sous-module `countries`, projet contenant
   les informations des diff�rents pays.
* `srs/countries.c` : Fichier C contenant l'impl�mentation du fichier
  `countries.h`
* `srs/countries.h` : Fichier *header* contenant les d�clarations des fonctions
   du ficher `countries.c` ainsi que leurs documentations. 
* `srs/tp2.c` : Fichier C source du projet produisant l'ex�cutable.
* `test/suite1.bats` : S�rie de tests sur les commandes invalides entr�es par
   l'utilisateur.
* `test/suite2.bats` : S�rie de tests sur l'affichage du format `text`.
* `test/suite3.bats` : S�rie de tests sur l'affichage du format `dot`.
* `.gitmodules` : Ficher servant � d�finir la liaison du sous-module `countries` �
   son d�pot-m�re.
* `.gitlab-ci.yml` : Fichier `YAML` permettant de tester automatiquement les 
   suites de tests lors des *pushes* sur le d�pot. 
* `.gitignore` : Fichier sp�cifiant au logiciel Git quels fichiers ignorer. 

## R�f�rences

* *Blondin Mass�, Alexandre*, [Diapositives des cours](http://www.lacim.uqam.ca/~blondin/fr/inf3135).

## Statut

- [x] Definir les fonctions du fichier `countries.h`. 

- [x] Impl�mentation des fonctions du fichier `countries.h` dans le fichier 
  `countries.c`.

  - [x] void afficherAide()
  - [x] int chercherArgument(const char \*\*p, const char \*chaine, int nbArguments)
  - [x] Pays * recupererDonneesPays(const char \*cle, bool doitAffPays, 
            bool doitAffReg)
  - [x] void traiterFormatTexte(Pays \* pays, const char \*nomFicher, 
            bool doitAffLan, bool doitAffCap, bool doitAffFro)
  - [x] void traiterFormatDot(Pays \* pays, const char \*nomFichier, 
            bool doitAffLan, bool doitAffCap, bool doitAffFro, bool doitAffDra)
  - [x] void traiterFormatPng(const char \*nomFichier, const char \*nomFichierDot);
  - [x] void validerNomFichier(const char \*nomFichier, const char \*format);
  - [x] void trierLangues(Pays \*pays);

- [x] Impl�mentation du fichier `tp2.c` pour produire un ex�cutable fonctionnel. 

- [x] Cr�er des suites de tests et tester le projet.
    
  - [x] Creation d'une suite de tests sur les commandes entr�es par 
        l'utilisateur.
  - [x] Creation d'une suite de tests pour le format texte.
  - [x] Creation d'une suite de tests pour le format Dot.

- [ ] Optimisation. 
