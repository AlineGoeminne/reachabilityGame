#pragma once

#include "ReachabilityGame.hpp"
#include "types/Long.hpp"

namespace generators {
    /**
     * \brief Génère un graphe aléatoire inspiré d'un arbre.
     * 
     * Sur une idée originale de Thomas Brihaye.
     * 
     * Le graphe est généré couche par couche en commençant par v0. Pour chaque noeud, on détermine aléatoirement le nombre d'enfants dans l'intervalle [lowBranchingFactor, upBranchingFactor] et s'il peut avoir des liens vers des sommets à la même "profondeur", vers des sommets "plus haut dans l'arbre" et vers des sommets "plus bas dans l'abre" (vers des sommets qui ne sont pas ses enfants). On répète ceci pour chaque enfant jusqu'à atteindre le nombre de sommets désiré.
     * 
     * Le noeud initial est toujours v0.
     * 
     * Les poids des arcs sont toujours 1.
     * 
     * S'il arrive qu'un joueur n'a pas de cible, le paramètre sharedTargets est ignoré pour ce joueur.
     * 
     * Pour chaque joueur, la probabilité qu'un sommet lui appartienne est 1/nPlayers.
     * 
     * Pour chaque joueur, la probabilité qu'un sommet soit une cible pour lui est 0.1.
     * 
     * Les joueurs n'ont pas de limite sur le nombre de cibles
     * 
     * \param size Le nombre de sommets à générer
     * \param lowBranchingFactor La borne inférieure sur le facteur de branchement
     * \param upBranchingFactor La borne supérieure sur le facteur de branchement
     * \param probaSameDepth La probabilité d'avoir un arc entre deux sommets "à la même profondeur"
     * \param probaSkipping La probabilité d'avoir un arc allant d'un sommet à un autre à une "profondeur" inférieure (et qui n'est pas son enfant)
     * \param probaClimbing La probabilité d'avoir un arc qui remonte dans l'arbre
     * \param multipleWeights Est-ce que les joueurs voient des poids différents sur un arc ?
     * \param nPlayers Le nombre de joueurs
     * \param sharedTargets Est-ce que plusieurs joueurs peuvent partager la même cible ?
     */
    ReachabilityGame randomTreeLikeGenerator(std::size_t size, std::size_t lowBranchingFactor, std::size_t upBranchingFactor, double probaSameDepth, double probaSkipping, double probaClimbing, bool multipleWeights, std::size_t nPlayers, bool sharedTargets);

    /**
     * \brief Génère un graphe aléatoire inspiré d'un arbre.
     * 
     * Sur une idée originale de Thomas Brihaye.
     * 
     * Le graphe est généré couche par couche en commençant par v0. Pour chaque noeud, on détermine aléatoirement le nombre d'enfants dans l'intervalle [lowBranchingFactor, upBranchingFactor] et s'il peut avoir des liens vers des sommets à la même "profondeur", vers des sommets "plus haut dans l'arbre" et vers des sommets "plus bas dans l'abre" (vers des sommets qui ne sont pas ses enfants). On répète ceci pour chaque enfant jusqu'à atteindre le nombre de sommets désiré.
     * 
     * Le noeud initial est toujours v0.
     * 
     * S'il arrive qu'un joueur n'a pas de cible, le paramètre sharedTargets est ignoré pour ce joueur.
     * 
     * Pour chaque joueur, la probabilité qu'un sommet lui appartienne est 1/nPlayers.
     * 
     * Pour chaque joueur, la probabilité qu'un sommet soit une cible pour lui est 0.1.
     * 
     * Les joueurs n'ont pas de limite sur le nombre de cibles
     * 
     * \param size Le nombre de sommets à générer
     * \param lowBranchingFactor La borne inférieure sur le facteur de branchement
     * \param upBranchingFactor La borne supérieure sur le facteur de branchement
     * \param probaSameDepth La probabilité d'avoir un arc entre deux sommets "à la même profondeur"
     * \param probaSkipping La probabilité d'avoir un arc allant d'un sommet à un autre à une "profondeur" inférieure (et qui n'est pas son enfant)
     * \param probaClimbing La probabilité d'avoir un arc qui remonte dans l'arbre
     * \param minWeight Le poids minimal
     * \param maxWeight Le poids maximal
     * \param multipleWeights Est-ce que les joueurs voient des poids différents sur un arc ?
     * \param nPlayers Le nombre de joueurs
     * \param sharedTargets Est-ce que plusieurs joueurs peuvent partager la même cible ?
     */
    ReachabilityGame randomTreeLikeGenerator(std::size_t size, std::size_t lowBranchingFactor, std::size_t upBranchingFactor, double probaSameDepth, double probaSkipping, double probaClimbing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets);

    /**
     * \brief Génère un graphe aléatoire inspiré d'un arbre.
     * 
     * Sur une idée originale de Thomas Brihaye.
     * 
     * Le graphe est généré couche par couche en commençant par v0. Pour chaque noeud, on détermine aléatoirement le nombre d'enfants dans l'intervalle [lowBranchingFactor, upBranchingFactor] et s'il peut avoir des liens vers des sommets à la même "profondeur", vers des sommets "plus haut dans l'arbre" et vers des sommets "plus bas dans l'abre" (vers des sommets qui ne sont pas ses enfants). On répète ceci pour chaque enfant jusqu'à atteindre le nombre de sommets désiré.
     * 
     * Le noeud initial est toujours v0.
     * 
     * S'il arrive qu'un joueur n'a pas de cible, le paramètre sharedTargets est ignoré pour ce joueur.
     * 
     * Pour chaque joueur, la probabilité qu'un sommet soit une cible pour lui est 0.1.
     * 
     * Les joueurs n'ont pas de limite sur le nombre de cibles
     * 
     * \param size Le nombre de sommets à générer
     * \param lowBranchingFactor La borne inférieure sur le facteur de branchement
     * \param upBranchingFactor La borne supérieure sur le facteur de branchement
     * \param probaSameDepth La probabilité d'avoir un arc entre deux sommets "à la même profondeur"
     * \param probaSkipping La probabilité d'avoir un arc allant d'un sommet à un autre à une "profondeur" inférieure (et qui n'est pas son enfant)
     * \param probaClimbing La probabilité d'avoir un arc qui remonte dans l'arbre
     * \param minWeight Le poids minimal
     * \param maxWeight Le poids maximal
     * \param multipleWeights Est-ce que les joueurs voient des poids différents sur un arc ?
     * \param nPlayers Le nombre de joueurs
     * \param sharedTargets Est-ce que plusieurs joueurs peuvent partager la même cible ?
     * \param probaPlayers Un tableau qui indique pour chaque joueur la probabilité qu'un sommet lui appartienne
     */
    ReachabilityGame randomTreeLikeGenerator(std::size_t size, std::size_t lowBranchingFactor, std::size_t upBranchingFactor, double probaSameDepth, double probaSkipping, double probaClimbing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets, const std::vector<double>& probaPlayers);

    /**
     * \brief Génère un graphe aléatoire inspiré d'un arbre.
     * 
     * Sur une idée originale de Thomas Brihaye.
     * 
     * Le graphe est généré couche par couche en commençant par v0. Pour chaque noeud, on détermine aléatoirement le nombre d'enfants dans l'intervalle [lowBranchingFactor, upBranchingFactor] et s'il peut avoir des liens vers des sommets à la même "profondeur", vers des sommets "plus haut dans l'arbre" et vers des sommets "plus bas dans l'abre" (vers des sommets qui ne sont pas ses enfants). On répète ceci pour chaque enfant jusqu'à atteindre le nombre de sommets désiré.
     * 
     * Le noeud initial est toujours v0.
     * 
     * S'il arrive qu'un joueur n'a pas de cible, le paramètre sharedTargets est ignoré pour ce joueur.
     * 
     * Les joueurs n'ont pas de limite sur le nombre de cibles
     * 
     * \param size Le nombre de sommets à générer
     * \param lowBranchingFactor La borne inférieure sur le facteur de branchement
     * \param upBranchingFactor La borne supérieure sur le facteur de branchement
     * \param probaSameDepth La probabilité d'avoir un arc entre deux sommets "à la même profondeur"
     * \param probaSkipping La probabilité d'avoir un arc allant d'un sommet à un autre à une "profondeur" inférieure (et qui n'est pas son enfant)
     * \param probaClimbing La probabilité d'avoir un arc qui remonte dans l'arbre
     * \param minWeight Le poids minimal
     * \param maxWeight Le poids maximal
     * \param multipleWeights Est-ce que les joueurs voient des poids différents sur un arc ?
     * \param nPlayers Le nombre de joueurs
     * \param sharedTargets Est-ce que plusieurs joueurs peuvent partager la même cible ?
     * \param probaPlayers Un tableau qui indique pour chaque joueur la probabilité qu'un sommet lui appartienne
     * \param probaTargets Un tableau qui indique pour chaque joueur la probabilité qu'un sommet soit une cible pour lui
     */
    ReachabilityGame randomTreeLikeGenerator(std::size_t size, std::size_t lowBranchingFactor, std::size_t upBranchingFactor, double probaSameDepth, double probaSkipping, double probaClimbing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets, const std::vector<double>& probaPlayers, const std::vector<double> &probaTargets);
    /**
     * \brief Génère un graphe aléatoire inspiré d'un arbre.
     * 
     * Sur une idée originale de Thomas Brihaye.
     * 
     * Le graphe est généré couche par couche en commençant par v0. Pour chaque noeud, on détermine aléatoirement le nombre d'enfants dans l'intervalle [lowBranchingFactor, upBranchingFactor] et s'il peut avoir des liens vers des sommets à la même "profondeur", vers des sommets "plus haut dans l'arbre" et vers des sommets "plus bas dans l'abre" (vers des sommets qui ne sont pas ses enfants). On répète ceci pour chaque enfant jusqu'à atteindre le nombre de sommets désiré.
     * 
     * Le noeud initial est toujours v0.
     * 
     * S'il arrive qu'un joueur n'a pas de cible, le paramètre sharedTargets est ignoré pour ce joueur.
     * 
     * \param size Le nombre de sommets à générer
     * \param lowBranchingFactor La borne inférieure sur le facteur de branchement
     * \param upBranchingFactor La borne supérieure sur le facteur de branchement
     * \param probaSameDepth La probabilité d'avoir un arc entre deux sommets "à la même profondeur"
     * \param probaSkipping La probabilité d'avoir un arc allant d'un sommet à un autre à une "profondeur" inférieure (et qui n'est pas son enfant)
     * \param probaClimbing La probabilité d'avoir un arc qui remonte dans l'arbre
     * \param minWeight Le poids minimal
     * \param maxWeight Le poids maximal
     * \param multipleWeights Est-ce que les joueurs voient des poids différents sur un arc ?
     * \param nPlayers Le nombre de joueurs
     * \param sharedTargets Est-ce que plusieurs joueurs peuvent partager la même cible ?
     * \param probaPlayers Un tableau qui indique pour chaque joueur la probabilité qu'un sommet lui appartienne
     * \param probaTargets Un tableau qui indique pour chaque joueur la probabilité qu'un sommet soit une cible pour lui
     * \param maximumTargets Un tableau qui indique pour chaque joueur le nombre maximal de cibles qu'il peut avoir
     */
    ReachabilityGame randomTreeLikeGenerator(std::size_t size, std::size_t lowBranchingFactor, std::size_t upBranchingFactor, double probaSameDepth, double probaSkipping, double probaClimbing, long minWeight, long maxWeight, bool multipleWeights, std::size_t nPlayers, bool sharedTargets, const std::vector<double>& probaPlayers, const std::vector<double> &probaTargets, const std::vector<types::Long>& maximumTargets);
}