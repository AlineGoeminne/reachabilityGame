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

#include <unordered_set>
#include "Vertex.hpp"

/**
 * \brief Décrit un joueur
 */
class Player {
public:
    Player(unsigned int id);
    explicit Player(unsigned int id, const std::unordered_set<Vertex::Ptr>& vertices, const std::unordered_set<Vertex::Ptr>& goals);
    ~Player();

    /**
     * \brief Ajoute un sommet appartenant au joueur.
     * \param vertex Le sommet
     */
    void addVertex(Vertex::Ptr vertex);

    /**
     * \brief Donne l'ensemble des sommets appartenant à ce joueur
     * \return L'ensemble des sommets de ce joueur
     */
    const std::unordered_set<Vertex::Ptr>& getVertices() const;

    /**
     * \brief Ajoute un goal appartenant au joueur.
     * 
     * Le joueur est également enregistré dans le sommet.
     * \param vertex Le goal
     */
    void addGoal(Vertex::Ptr vertex);

    /**
     * \brief Donne l'ensemble des cibles appartenant à ce joueur
     * \return L'ensemble des cibles de ce joueur
     */
    const std::unordered_set<Vertex::Ptr>& getGoals() const;

private:
    unsigned int m_id;
    std::unordered_set<Vertex::Ptr> m_vertices;
    std::unordered_set<Vertex::Ptr> m_goals;
};