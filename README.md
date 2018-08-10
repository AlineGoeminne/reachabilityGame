# reachabilityGame

## Comment compiler
Il faut un compilateur C++ qui supporte le standard C++17, CMake et make.

Une fois à la racine du projet,
- Créer un dossier build et aller dedans
- Configurer le projet via CMake
  - `cmake ..` dans un terminal/invite de commandes
  - ou utiliser CMake GUI
- Taper `make` dans un terminal/invite de commandes

L'exécutable `ReachabilityGame` est produit dans le dossier.

Il est possible que certains IDE gèrent les projets CMake.

## Comment construire la documentation
Il faut mettre le paramètre `BUILD_DOC` à `TRUE`
  - Ligne de commande : `cmake -DBUILD_DOC=TRUE ..`
  - Interface graphique : cocher la case

Ensuite, `make documentation` la génère dans le dossier `documentation` (à la racine du projet).

## Comment constuire les tests
Il faut mettre le paramètre `BUILD_TESTS` à `TRUE`
  - Ligne de commande : `cmake -DBUILD_TESTS=TRUE ..`
  - Interface graphique : cocher la case

Ensuite, `make ReachabilityGame-tests` génère l'exécutable des tests.