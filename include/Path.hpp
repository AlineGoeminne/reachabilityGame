#pragma once

#include <list>
#include <stdexcept>

#include "Vertex.hpp"
#include "ReachabilityGame.hpp"

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
    typedef std::unordered_map<unsigned int, std::vector<Long>> Coalitions;

public:
    Path(const ReachabilityGame& game, Vertex::Ptr start, std::size_t nPlayers);
    Path(const ReachabilityGame& game, std::vector<Vertex::Ptr> steps, std::size_t nPlayers);
    Path(const Path& path);

    void addStep(Vertex::Ptr step);

    const std::vector<std::pair<bool, Long>>& getCosts() const;

    std::pair<bool, Coalitions> isANashEquilibrium(std::unordered_set<unsigned int> playersAlreadyTested = {}) const;

private:
    bool respectProperty(const Long& val, const std::vector<Long>& epsilon, unsigned int player) const;

private:
    const ReachabilityGame& m_game;
    std::list<Vertex::Ptr> m_path;
    std::vector<std::pair<bool, Long>> m_costs;
};