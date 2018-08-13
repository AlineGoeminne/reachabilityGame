#pragma once

#include <list>
#include <stdexcept>

#include "Vertex.hpp"

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

class Path final {
public:
    Path(Vertex::Ptr start, std::size_t nPlayers);

    void addStep(Vertex::Ptr step);

    const std::vector<Long>& getCosts() const;

private:
    std::list<Vertex::Ptr> m_path;
    std::vector<Long> m_costs;
};