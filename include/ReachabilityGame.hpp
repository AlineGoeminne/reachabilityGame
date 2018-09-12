/*
 * ReachabilityGame - a program to compute the best Nash equilibrium in reachability games
 * Copyright (C) 2018 Gaëtan Staquet and Aline Goeminne
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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