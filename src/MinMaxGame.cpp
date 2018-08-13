#include "MinMaxGame.hpp"

#define MIN 0
#define MAX 1

MinMaxGame::MinMaxGame(Graph &graph, Vertex::Ptr init, const Player& min, const Player& max) :
    Game(graph, init),
    m_min(min),
    m_max(max),
    m_goals(min.getGoals())
    {

}

std::vector<Long> MinMaxGame::getValues() {

}

MinMaxGame MinMaxGame::convert(ReachabilityGame &game, unsigned int minPlayer) {
    // TODO : si trop lent, trouver autre moyen
    std::vector<Vertex::Ptr> newVertices;
    std::unordered_set<Vertex::Ptr> minVertices, maxVertices;
    std::unordered_set<Vertex::Ptr> minGoals;
    Graph &graph = game.getGraph();
    // On commence par créer les nouveaux sommets
    for (auto &vertex : graph.getVertices()) {
        // Même ID
        // On répartit entre Min et Max
        Vertex::Ptr newV;
        if (vertex->getPlayer() == minPlayer) {
            newV = std::make_shared<Vertex>(vertex->getID(), MIN, 2);
            minVertices.insert(newV);
        }
        else {
            newV = std::make_shared<Vertex>(vertex->getID(), MAX, 2);
            maxVertices.insert(newV);
        }

        // On "copie" les goals du joueur min (le joueur max n'en a pas besoin dans notre cas)
        if (vertex->isTargetFor(minPlayer)) {
            newV->addTargetFor(MIN);
            minGoals.insert(newV);
        }

        newVertices.push_back(newV);
    }

    // On copie les successeurs et prédecesseurs
    for (auto &vertex : graph.getVertices()) {
        for (auto &e : *vertex) {
            // e.first = ID du vertex
            // e.second.second = poids sur l'arc
            vertex->addSuccessor(newVertices[e.first], e.second.second);
        }
    }

    // Pour finir, on crée les deux nouveaux joueurs
    Player min(minVertices, minGoals), max(maxVertices, {});

    // Les poids sur les arcs sont les mêmes
    Graph g(newVertices, graph.getMaxWeights());

    return MinMaxGame(graph, game.getInit(), min, max);
}

void MinMaxGame::initQ() {
    //m_Q = std::priority_queue<DijkstraNode, std::vector<DijkstraNode>, DijkstraNode>();
    const auto &vertices = getGraph().getVertices();
    for (std::size_t i = 0 ; i < vertices.size() ; i++) {

    }
}

void MinMaxGame::initS() {
    const auto &vertices = getGraph().getVertices();
    m_S.resize(vertices.size());
    for (std::size_t i = 0 ; i < vertices.size() ; i++) {
        m_S[i] = std::priority_queue<Sucessor, std::vector<Sucessor>, Sucessor>();
        Sucessor node;
        if (vertices[i]->isTarget()) {
            node.cost = 0;
            node.pred = nullptr;
        }
        else {
            node.cost = Long::infinity;
            node.pred = nullptr;
        }
        m_S[i].push(node);
    }
}