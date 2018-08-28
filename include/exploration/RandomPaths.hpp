#pragma once

#include "Path.hpp"
#include "ReachabilityGame.hpp"

namespace exploration {
    /**
     * \brief Génère un certain nombre de chemins aléatoires et garde le meilleur équilibre de Nash.
     * 
     * \param game Le jeu
     * \param nPaths Le nombre de chemins à générer
     * \return Le meilleur équilibire de Nash 
     */
    Path randomPath(const ReachabilityGame &game, std::size_t nPaths);
}