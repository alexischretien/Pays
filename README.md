# Travail pratique 2

## Description

Projet visant à introduire les étudiants à la programmation modulaire en language C, à la gestion des dépendances et à la construction de suites de tests. 

Le projet consiste en un programme qui affiche differentes informations sur un ou plusieurs pays en fonction des arguments qui ont été entré par l'utilisateur lors de l'exécution du programme. Ces arguments incluent une option pour générer des objets graphiques sous format .dot ou .pgn

## Auteurs

- Alexis Chrétien (CHRA25049209)

## Plateformes supportées

À venir

## Dépendances

* [Graphviz](http://graphviz.org/Download.php) : Logiciel de visualization graphique.
* Le projet [countries](https://github.com/ablondin/countries) : Projet duquel on extrait les informations des différents pays. Le projet *inf3135-aut2016-tp2* contient le projet *countries* sous forme de sous-module. Pour mettre à jour les données du sous-module *countries*, entrez la commande `make data` dans le répertoire racine du projet *inf3135-aut2016-tp2*.
* La bibliothèque [jansson](http://digip.org/jansson/) : Bibliothèque C pour encoder, décoder et manipuler des informations sous forme JSON - www.digip.org/jansson/

## Installation

À venir

## Fonctionnement

À venir

## Contenu du projet

* **Makefile** : Ficher Makefile inculant un service de compilation des fichiers sources et de génération du fichier exécutable *tp2* (`make`), un service de nettoyage des fichiers du projet (`make clean`) et un service de mise à jour des fichiers du sous-module *countries* (`make data`).
* **README.md** : Fichier markdown servant à la documentation et au formatage de la page GitLab du projet.
* **tp2** : Le fichier exécutable du projet
* **countries/** : Répertoire du sous-module *countries*, projet contenant les informations des différents pays.
* **countries.c** : Fichier C contenant l'implémentation du fichier *countries.h*
* **countries.h** : Fichier header contenant les déclarations des fonctions du ficher *countries.c*. 
* **tp2.c** : Fichier C source du projet produisant l'exécutable.
* **suite1.bats**, **suite2.bats**, **...** : Fichers .bats produisant des séries de tests servant à vérifier la bonne implémentation du projet. 
* **.gitmodules** : Ficher servant à définir le module *countries*.

## Références

À venir, s'il y a lieu.

## Statut

- [ ] Definir les fonctions du fichier *countries.h* 

- [ ] Implémentation des fonctions du fichier *countries.h* dans le fichier *countries.c*

  - [x] void afficherAide()
  - [x] int chercherArgument(const \*\*p, const \*chaine, int argc) 
  - [x] char * trim(char [] chaine)
  - [x] void genererFichierPays(FILE * f)
  - [x] fonction #5
  - [ ] ...

- [ ] Implémentation du fichier *tp2.c* pour produire un exécutable fonctionnel 

- [ ] Créer des suites de tests et tester le projet

  - [ ] Creation d'une suite de tests pour le format texte
  - [ ] Creation d'une suite de tests pour le format Graphviz
  - [ ] Création d'une suite de tests pour le format PNG
  - [ ] Validation des tests et corrections éventuelles appliquées au projet

- [ ] Optimisation 
