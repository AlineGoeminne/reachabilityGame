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