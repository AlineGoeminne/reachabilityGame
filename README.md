# Présentation
Ce projet vise à avoir une idée des graphes intéressants pour la recherche d'équilibres de Nash dans des jeux d'atteignabilité sur graphe.

  - Algorithmes implémentés :
    - DijkstraMinMax
    - Exploration avec A*
  - Générateurs aléatoires implémentés :
    - Un générateur "naïf" qui génère des graphes sans contraintes sur la forme;
    - Un générateur "arbre" qui génère au départ un arbre et qui le modifie selon les paramètres et les contraintes des jeux d'atteignabilité;
    - Un générateur de graphes fortement connexes.
  - Limites :
    - Les poids sur les arcs doivent être positifs
    - L'exploration peut consommer beaucoup de mémoire
    - Il n'y a pas de résultats sur le générateur de graphes fortement connexes.
  - Améliorations possibles :
    - Réussir à diminuer la consommation de mémoire
      - Eviter de stocker les poids dans les successeurs et les prédecesseurs
      - Réduire la consommation de mémoire de l'exploration, si possible
    - Trouver une meilleure heuristique, si possible
    - Permettre d'avoir des poids négatifs

# Compiler et exécuter
Il faut un compilateur C++ qui supporte le standard `C++17`, make et CMake. Une fois dans la racine du projet :
  1. Créer un dossier `build`
  2. Rentrer dans le dossier `build`
  3. Lancer CMake
    - En ligne de commandes : `cmake ..`
    - Via CMake-gui et remplissez les champs :
      - "Where is the source code" : le chemin vers la racine du projet
      - "Where to build the binaries" : le chemin vers le fichier `build`
    - Via votre IDE favori
  4. Configurer CMake
    - Pour constuire les tests unitaires, activez `BUILD_TESTS`
      - En ligne de commandes : `cmake -DBUILD_TESTS=TRUE ..`
      - En cochant la case dans l'interface graphique
      - Via votre IDE favori
    - Pour construire les tests de performance, activez `BUILD_PERFORMANCE`
      - En ligne de commandes : `cmake -DBUILD_PERFORMANCE=TRUE ..`
      - En cochant la case dans l'interface graphique
      - Via votre IDE favori
    - Pour construire la documentation, activez `BUILD_DOC`
      - En ligne de commandes : `cmake -DBUILD_DOC=TRUE ..`
      - En cochant la case dans l'interface graphique
      - Via votre IDE favori
  5. Exécuter make
    - En ligne de commandes : `make`
    - Via votre IDE favori
  6. Pour générer la documentation : `make documentation`

Les programmes seront générés dans le dossier `build` et les sous-dossiers `tests` et `performance` tandis que la documentation sera générée dans le dossier `documentation` à la racine du projet.

Pour exécuter les tests unitaires, il suffit de lancer `ReachabilityGame-tests` dans le dossier `tests`. Pour exécuter les tests de performance, il suffit de lancer, dans le dossier `performance`, `ReachabilityGame-perf-naive` pour le générateur naïf et `ReachabilityGame-perf-tree` pour le générateur d'arbre.

## Résultats de performance
Il faut modifier les fichiers `naiveTests.cpp` et `treeTests.cpp` du dossier `performance` pour changer les paramètres à tester. Une limite de 10 secondes par jeu est fixé.

La sortie produite (dans un fichier) devrait contenir le paramètre testé et les moyennes et médiannes des temps CPU obtenus ainsi que le nombre de fois que les 10 secondes ont été atteintes.
