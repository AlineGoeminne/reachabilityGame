#include "Path.hpp"

#include "MinMaxGame.hpp"
#include "ReachabilityGame.hpp"

Path::Path(const ReachabilityGame &game, Vertex::Ptr start, std::size_t nPlayers) :
    m_game(game),
    m_path{start},
    m_costs(nPlayers, std::make_pair(false, 0))
    {
    for (auto &player : start->getTargetPlayers()) {
        m_costs[player].first = true;
    }
}

Path::Path(const ReachabilityGame& game, std::vector<Vertex::Ptr> steps, std::size_t nPlayers) :
    Path(game, steps[0], nPlayers)
    {
    for (std::size_t i = 1 ; i < steps.size() ; i++) {
        addStep(steps[i]);
    }
}

Path::Path(const Path &path) :
    m_game(path.m_game),
    m_path(path.m_path.begin(), path.m_path.end()),
    m_costs(path.m_costs.begin(), path.m_costs.end())
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
        // On vérifie que le joueur i n'a pas déjà atteint une cible
        if (!m_costs[i].first) {
            m_costs[i].second += costs[i];
        }
    }
    // On met à jour les joueurs qui ont atteint une cible
    for (const unsigned int &player : step->getTargetPlayers()) {
        m_costs[player].first = true;
    }
    // Finalement, on enregistre le pas
    m_path.push_back(step);
}

const std::vector<std::pair<bool, Long>>& Path::getCosts() const {
    return m_costs;
}

std::pair<bool, Path::Coalitions> Path::isANashEquilibrium(std::unordered_set<unsigned int> playersAlreadyTested) const {
    std::size_t nPlayers = m_costs.size();
    std::vector<Long> epsilon(nPlayers, 0); // Poids du chemin jusqu'au noeud courant
    bool nash = true;

    // unordered_...::find ont une complexité de O(1) en moyenne
    std::unordered_set<unsigned int> visitedPlayers; // Ensemble des joueurs ayant déjà atteint une de leurs cibles
    std::unordered_map<unsigned int, std::vector<Long>> coalitions; // A un joueur, on associe les valeurs de la coalition contre lui

    for (auto itr = m_path.begin() ; nash && itr != m_path.end() ; ++itr) {
        const Vertex::Ptr current = *itr;

        auto& players = current->getTargetPlayers();
        visitedPlayers.insert(players.begin(), players.end()); // Equivalent de l'union

        if (itr != m_path.begin()) {
            // Si on n'est pas au premier sommet, on incrémente epsilon
            const Vertex::Ptr prev = *std::prev(itr); // On récupère le vertex précédent
            std::vector<Long> weights = prev->getWeights(current->getID());

            for (std::size_t i = 0 ; i < epsilon.size() ; i++) {
                epsilon[i] += weights[i];
            }
        }

        unsigned int player = current->getPlayer();

        if (playersAlreadyTested.find(player) == playersAlreadyTested.end() && visitedPlayers.find(player) == visitedPlayers.end()) {
            //  Si le joueur actuel n'a pas déjà atteint une cible (et qu'il n'a pas déjà été testé), on vérifie si c'est bien un EN

            Long val(0);
            
            if (coalitions.find(player) == coalitions.end()) {
                // On ne connait pas encore les valeurs
                MinMaxGame minmax = MinMaxGame::convert(m_game, player);

                std::vector<Long> values = minmax.getValues(m_game.getPlayers()[player].getGoals());
                coalitions[player] = values;

                val = values[current->getID()];
            }
            else {
                // On connait déjà les valeurs
                val = coalitions[player][current->getID()];
            }

            if (!respectProperty(val, epsilon, player)) {
                nash = false;
            }
        }
    }

    return std::make_pair(nash, coalitions);
}

std::size_t Path::size() const {
    return m_path.size();
}

const Vertex::Ptr Path::getLast() const {
    return m_path.back();
}

bool Path::respectProperty(const Long &val, const std::vector<Long>& epsilon, unsigned int player) const {
    return val + epsilon[player] >= m_costs[player].second;
}

bool operator==(const Path& a, const Path &b) {
    if (a.size() != b.size()) {
        // Pas le même nombre de pas
        return false;
    }

    auto itrA = a.m_path.begin();
    auto itrB = b.m_path.begin();

    for (; itrA != a.m_path.end() && itrB != b.m_path.end() ; ++itrA, ++itrB) {
        const Vertex::Ptr va = *itrA;
        const Vertex::Ptr vb = *itrB;
        if (*va != *vb) {
            // Les chemins ont des pas différents
            return false;
        }
    }
    // Même longueur et mêmes pas
    return true;
}

std::ostream& operator<<(std::ostream &os, const Path &a) {
    for (const Vertex::Ptr v : a.m_path) {
        os << *v << "->";
    }
    os << "end";
    return os;
}