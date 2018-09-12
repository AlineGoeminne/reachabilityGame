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

#include "Path.hpp"
#include "ReachabilityGame.hpp"

namespace exploration {
    /**
     * \brief Erreur à lancer quand aucun équilibre de nash n'a été généré
     */
    class NoENGenerated : public std::runtime_error {
    public:
        explicit NoENGenerated(const std::string &what) :
            std::runtime_error(what) {
        }
        explicit NoENGenerated(const char* what) :
            std::runtime_error(what) {
        }
    };

    /**
     * \brief Génère un certain nombre de chemins aléatoires et garde le meilleur équilibre de Nash.
     * 
     * \param game Le jeu
     * \param nPaths Le nombre de chemins à générer
     * \return Le meilleur équilibire de Nash 
     */
    Path randomPath(const ReachabilityGame &game, std::size_t nPaths);
}