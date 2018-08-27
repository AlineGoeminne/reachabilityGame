#pragma once

#include <vector>

#include "Graph.hpp"
#include "Player.hpp"
#include "types/Long.hpp"
#include "Game.hpp"
#include "exploration/BestFirstSearch.hpp"

/**
 * \brief Un jeu d'atteignabilité
 */
class ReachabilityGame : public Game {
public:
    ReachabilityGame(Graph graph, Vertex::Ptr init, const std::vector<Player>& players);

    const std::vector<Player>& getPlayers() const;

    std::size_t getMaxLength() const;

    /**
     * \brief Affiche dans la console le fichier DOT qui décrit le jeu.
     * 
     * Marche uniquement pour les jeux à deux joueurs.
     */
    void printDOT() const;

    /**
     * \brief L'heuristique A* positive telle que définie dans le projet/mémoire
     * \param node Le noeud actuel de l'exploration
     * \param costsMap Les coûts pour arriver à chaque cible
     */
    types::Long AStartPositive(const exploration::Node::Ptr& node, const exploration::CostsMap &costsMap);

    /**
     * \brief Donne le pourcentage de sommets atteignables à partir du sommet initial
     * \return Le pourcentage de sommets atteignables
     */
    std::size_t percentageOfReachableVertices() const;

    friend std::ostream& operator<<(std::ostream &os, const ReachabilityGame &game);

private:
    std::vector<Player> m_players;
    std::vector<types::Long> m_maxWeightsPath;
};

std::ostream& operator<<(std::ostream &os, const ReachabilityGame &game);