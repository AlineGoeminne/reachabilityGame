#include "MinMaxGame.hpp"

#define MIN 0
#define MAX 1

MinMaxGame::DijVertex::DijVertex(unsigned int ID, unsigned int player, std::size_t nPlayers) :
    Vertex(ID, player, nPlayers),
    d(0),
    nSuccessors(0)
    {

}

std::vector<Long> MinMaxGame::getValues() {
    dijkstraMinMax();

    std::vector<Long> values(getGraph().size());

    for (std::size_t i = 0 ; i < getGraph().size() ; i++) {
        DijVertex::Ptr vertex = std::dynamic_pointer_cast<DijVertex>(getGraph().getVertices()[i]);
        values[i] = vertex->S.top().cost;
    }

    return values;
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
        DijVertex::Ptr newV;
        if (vertex->getPlayer() == minPlayer) {
            newV = std::make_shared<DijVertex>(vertex->getID(), MIN, 2);
            minVertices.insert(newV);
        }
        else {
            newV = std::make_shared<DijVertex>(vertex->getID(), MAX, 2);
            maxVertices.insert(newV);
        }

        // On "copie" les goals du joueur min (le joueur max n'en a pas besoin dans notre cas)
        if (vertex->isTargetFor(minPlayer)) {
            newV->addTargetFor(MIN);
            minGoals.insert(newV);
        }

        newVertices.push_back(std::move(newV));
    }

    // On copie les successeurs et prédecesseurs
    for (std::size_t i = 0 ; i < graph.size() ; i++) {
        for (auto &e : *graph.getVertices()[i]) {
            // e.first = ID du vertex
            // e.second.second = poids sur l'arc; on ne garde que le poids pour MIN
            newVertices[i]->addSuccessor(newVertices[e.first], e.second.second[minPlayer]);
        }
    }

    // Pour finir, on crée les deux nouveaux joueurs
    Player min(MIN, minVertices, minGoals), max(MAX, maxVertices, {});

    // Les poids sur les arcs sont les mêmes
    Graph g(newVertices, graph.getMaxWeights());

    return MinMaxGame(g, game.getInit(), min, max);
}

MinMaxGame::MinMaxGame(Graph &graph, Vertex::Ptr init, const Player& min, const Player& max) :
    Game(graph, init),
    m_min(min),
    m_max(max)
    {

}

void MinMaxGame::dijkstraMinMax() {
    initQ();
    initS();

    while (!m_Q.empty()) {
        auto s = m_Q.top();
        Successor successor = s->S.top();

        if (successor.cost == Long::infinity) {
            m_Q.pop();
        }
        else if (s->isTarget() || s->getPlayer() == MIN || s->nSuccessors == 1) {
            m_Q.pop();
            for (auto itr = s->beginPredecessors() ; itr != s->endPredecessors() ; itr++) {
                relax(s, itr->second);
            }
        }
        else {
            s->S.pop();
            Successor newSucc = s->S.top();
            m_Q.updateKeyPointer<Long>(s, newSucc.cost);
            s->nSuccessors--;
        }
    }
}

void MinMaxGame::initQ() {
    m_Q = DynamicPriorityQueue<DijVertex::Ptr, CompareDijVertex>();
    auto &vertices = getGraph().getVertices();
    for (std::size_t i = 0 ; i < vertices.size() ; i++) {
        DijVertex::Ptr v = std::static_pointer_cast<DijVertex>(vertices[i]);
        if (v->isTarget()) {
            v->d = 0;
        }
        else {
            v->d = Long::infinity;
        }
        m_Q.push(v);
    }
}

void MinMaxGame::initS() {
    auto &vertices = getGraph().getVertices();
    for (std::size_t i = 0 ; i < vertices.size() ; i++) {
        DijVertex::Ptr v = std::static_pointer_cast<DijVertex>(vertices[i]);
        v->nSuccessors = v->getNumberSuccessors();
        auto S = std::priority_queue<Successor, std::vector<Successor>, Successor>();
        Successor node;
        if (vertices[i]->isTarget()) {
            node.cost = 0;
            node.pred = nullptr;
        }
        else {
            node.cost = Long::infinity;
            node.pred = nullptr;
        }
        v->S.push(node);
    }
}

void MinMaxGame::relax(DijVertex::Ptr s, const Vertex::Edge& edge) {
    DijVertex::Ptr p = std::dynamic_pointer_cast<DijVertex>(edge.first);
    const Successor &succ = s->S.top();
    Long pVal = edge.second[MIN] + succ.cost;
    const Successor &old = p->S.top();

    if (pVal < old.cost) {
        m_Q.updateKeyPointer(p, pVal);
        if (p->getPlayer() == MIN) {
            Successor newSucc;
            newSucc.cost = pVal;
            newSucc.pred = s;
            p->S = std::priority_queue<Successor, std::vector<Successor>, Successor>();
            p->S.push(newSucc);
        }
    }

    if (p->getPlayer() == MAX) {
        Successor succ;
        succ.cost = pVal;
        succ.pred = s;
        p->S.push(succ);
    }
}