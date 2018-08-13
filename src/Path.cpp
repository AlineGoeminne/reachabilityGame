#include "Path.hpp"

Path::Path(Vertex::Ptr start, std::size_t nPlayers) :
    m_path{start},
    m_costs(nPlayers, 0)
    {
}

void Path::addStep(Vertex::Ptr step) {
    // On vérifie d'abord que l'arc entre last et step existe
    Vertex::Ptr last = m_path.back();
    Vertex::Edge e = last->getSuccessor(step->getID());
    if (!e.first) {
        throw InvalidPath("Il n'existe pas d'arc entre le dernier sommet (" + std::to_string(last->getID()) + ") du chemin et l'étape donnée (" + std::to_string(step->getID()) + ")");
    }
    // S'il existe, on ajoute les coûts sur l'arc aux coûts déjà calculés
    const std::vector<Long>& costs = e.second;
    for (std::size_t i = 0 ; i < m_costs.size() ; i++) {
        m_costs[i] += costs[i];
    }
    // Finalement, on enregistre le pas
    m_path.push_back(step);
}