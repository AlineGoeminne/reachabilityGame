#pragma once

#include <list>
#include <stdexcept>

#include "Vertex.hpp"

class ReachabilityGame;

/**
 * \brief L'exception à lancer si le chemin construit est invalide.
 * 
 * Par exemple, s'il existe u et v qui se suivent dans le chemin mais tels qu'il n'existe pas d'arc entre u et v
 */
class InvalidPath : public std::runtime_error {
public:
    explicit InvalidPath(const std::string &what) :
        std::runtime_error(what) {
    }
    explicit InvalidPath(const char* what) :
        std::runtime_error(what) {
    }
};

/**
 * \brief Représente un chemin dans le graphe (ou une histoire dans un jeu)
 */
class Path final {
public:
    typedef std::unordered_map<unsigned int, std::vector<types::Long>> Coalitions;

public:
    Path(const ReachabilityGame& game, std::shared_ptr<const Vertex> start);
    Path(const ReachabilityGame& game, std::vector<std::shared_ptr<const Vertex>> steps);
    Path(const Path& path);

    /**
     * \brief Ajoute un pas au chemin
     * \param step Le pas
     */
    void addStep(std::shared_ptr<const Vertex> step);

    /**
     * \brief Pour chaque joueur, indique si le joueur a déjà atteint une cible et son coût actuel
     * \return Un tableau de paires (bool, Long)
     */
    const std::vector<std::pair<bool, types::Long>>& getCosts() const;

    /**
     * \brief Indique si le chemin est un équilibre de Nash.
     * 
     * Les joueurs qui sont donnés en entrée sont ignorés.
     * \param playersAlreadyTested L'ensemble des joueurs à ignorer
     * \return Vrai ssi le chemin est un équilibre de Nash
     */
    bool isANashEquilibrium(std::unordered_set<unsigned int> playersAlreadyTested = {}) const;

    /**
     * \return La longueur du chemin
     */
    std::size_t size() const;

    const std::shared_ptr<const Vertex> getLast() const;

    friend bool operator==(const Path& a, const Path &b);

    friend std::ostream& operator<<(std::ostream &os, const Path& a);

private:
    bool respectProperty(const types::Long& val, const std::vector<types::Long>& epsilon, unsigned int player) const;

private:
    const ReachabilityGame& m_game;
    std::list<std::shared_ptr<const Vertex>> m_path;
    std::vector<std::pair<bool, types::Long>> m_costs;
};

bool operator==(const Path& a, const Path& b);

std::ostream& operator<<(std::ostream &os, const Path &a);