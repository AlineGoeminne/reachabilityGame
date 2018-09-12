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
#include <queue>
#include <iostream>

#include "Game.hpp"
#include "Player.hpp"
#include "ReachabilityGame.hpp"
#include "types/Long.hpp"
#include "types/DynamicPriorityQueue.hpp"

/**
 * \brief Représente un jeu Min-Max.
 * 
 * Le seul algorithme applicable sur ce jeu est DijkstraMinMax
 */
class MinMaxGame : public Game {
public:
    /**
     * \brief Exécute DijkstraMinMax et retourne les valeurs obtenues.
     * 
     * Une valeur par sommet.
     * \return Un tableau avec les résultats de DijkstraMinMax
     */
    std::vector<types::Long> getValues(const std::unordered_set<Vertex::Ptr>& goals);

    /**
     * \brief Convertit un jeu d'atteignabilité en un jeu Min-Max avec le joueur donné en tant que Min.
     * 
     * Les autres joueurs sont réunis en Max.
     * \param game Le jeu
     * \param minPlayer Le joueur qui devient le joueur Min.
     * \return Le jeu Min-Max
     */
    static MinMaxGame convert(const ReachabilityGame& game, unsigned int minPlayer);

    /**
     * \brief Convertit un jeu d'atteignabilité en un jeu Min-Max où tous les sommets appartiennent à Min.
     * 
     * Permet de pouvoir faire un simple Dijkstra
     * \param game Le jeu d'atteignabilité
     * \return Le jeu Min-Max
     */
    static MinMaxGame convert(const ReachabilityGame& game);

private:
    struct DijVertex;
    // Structure pour S
    struct Successor {
        types::Long cost;

        // Servira pour l'ordre dans la priority_queue
        bool operator()(const Successor &a, const Successor &b) {
            // On veut la plus petite valeur en haut de la pile
            return a.cost > b.cost;
        }
    };

    // Structure pour Q
    struct DijVertex : public Vertex {
        typedef std::shared_ptr<DijVertex> Ptr;

        types::Long d;
        std::size_t nSuccessors;
        std::priority_queue<Successor, std::vector<Successor>, Successor> S;

        DijVertex(unsigned int ID, unsigned int player, std::size_t nPlayers);

        void updateKey(types::Long d) {
            this->d = d;
        }
    };

    struct CompareDijVertex {
        bool operator()(const DijVertex::Ptr &a, const DijVertex::Ptr &b) {
            return a->d > b->d;
        }
    };

private:
    MinMaxGame(Graph &graph, Vertex::Ptr init, const Player& min, const Player& max);

    void dijkstraMinMax(const std::unordered_set<Vertex::Ptr>& goals);

    void initQ(const std::unordered_set<Vertex::Ptr>& goals);
    void initS(const std::unordered_set<Vertex::Ptr>& goals);
    void relax(DijVertex::Ptr s, const Vertex::Edge &edge);

private:
    Player m_min, m_max;
    types::DynamicPriorityQueue<DijVertex::Ptr, CompareDijVertex> m_Q; // Q
};