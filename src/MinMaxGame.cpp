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

#include "MinMaxGame.hpp"

#define MIN 0
#define MAX 1

using namespace types;

MinMaxGame::DijVertex::DijVertex(unsigned int ID, unsigned int player, std::size_t nPlayers) :
    Vertex(ID, player, nPlayers),
    d(0),
    nSuccessors(0)
    {

}

std::vector<Long> MinMaxGame::getValues(const std::unordered_set<Vertex::Ptr>& goals) {
    dijkstraMinMax(goals);

    std::vector<Long> values(getGraph().size());

    for (std::size_t i = 0 ; i < getGraph().size() ; i++) {
        DijVertex::Ptr vertex = std::dynamic_pointer_cast<DijVertex>(m_graph.getVertices()[i]);
        values[i] = vertex->S.top().cost;
    }

    return values;
}

MinMaxGame MinMaxGame::convert(const ReachabilityGame &game, unsigned int minPlayer) {
    // TODO : si trop lent, trouver autre moyen
    std::vector<Vertex::Ptr> newVertices;
    std::unordered_set<Vertex::Ptr> minVertices, maxVertices;
    std::unordered_set<Vertex::Ptr> minGoals;
    const Graph &graph = game.getGraph();
    // On commence par créer les nouveaux sommets
    for (auto itr = graph.cbegin() ; itr != graph.cend() ; ++itr) {
        const Vertex::Ptr vertex = *itr;
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

MinMaxGame MinMaxGame::convert(const ReachabilityGame &game) {
    std::vector<Vertex::Ptr> newVertices;
    std::unordered_set<Vertex::Ptr> minVertices;
    const Graph &graph = game.getGraph();

    for (auto itr = graph.cbegin() ; itr != graph.cend() ; ++itr) {
        const Vertex::Ptr vertex = *itr;
        // Même ID
        // Tout appartient à Min
        DijVertex::Ptr newV = std::make_shared<DijVertex>(vertex->getID(), MIN, 2);
        newVertices.push_back(newV);
        minVertices.insert(newV);
    }

    // On copie les successeurs et prédecesseurs
    for (std::size_t i = 0 ; i < graph.size() ; i++) {
        for (auto &e : *graph.getVertices()[i]) {
            // e.first = ID du vertex
            // e.second.second = poids sur l'arc; on ne garde que le poids pour MIN
            newVertices[i]->addSuccessor(newVertices[e.first], e.second.second);
        }
    }

    Player min(MIN, minVertices, {}), max(MAX, {}, {});
    Graph g(newVertices, graph.getMaxWeights());

    return MinMaxGame(g, game.getInit(), min, max);
}

MinMaxGame::MinMaxGame(Graph &graph, Vertex::Ptr init, const Player& min, const Player& max) :
    Game(graph, init),
    m_min(min),
    m_max(max)
    {

}

void MinMaxGame::dijkstraMinMax(const std::unordered_set<Vertex::Ptr> &goals) {
    initQ(goals);
    initS(goals);

    while (!m_Q.empty()) {
        auto s = m_Q.top();
        Successor successor = s->S.top();

        if (successor.cost == Long::infinity) {
            m_Q.pop();
        }
        else if (goals.find(s) != goals.end() || s->getPlayer() == MIN || s->nSuccessors == 1) {
            // Si c'est une cible ou si le sommet appartient à Min ou si le nombre de successeurs est 1, on relaxe le sommet
            m_Q.pop();
            for (auto itr = s->beginPredecessors() ; itr != s->endPredecessors() ; itr++) {
                relax(s, itr->second);
            }
        }
        else {
            // Le sommet appartient à Max et nSuccessors > 1
            // On bloque la plus petite valeur
            s->S.pop();
            Successor newSucc = s->S.top();
            m_Q.updateKeyPointer<Long>(s, newSucc.cost);
            s->nSuccessors--;
        }
    }
}

void MinMaxGame::initQ(const std::unordered_set<Vertex::Ptr>& goals) {
    m_Q = DynamicPriorityQueue<DijVertex::Ptr, CompareDijVertex>();
    auto &vertices = getGraph().getVertices();
    for (std::size_t i = 0 ; i < vertices.size() ; i++) {
        DijVertex::Ptr v = std::static_pointer_cast<DijVertex>(vertices[i]);
        if (goals.find(v) != goals.end()) {
            // v est un goal
            v->d = 0;
        }
        else {
            v->d = Long::infinity;
        }
        m_Q.push(v);
    }
}

void MinMaxGame::initS(const std::unordered_set<Vertex::Ptr>& goals) {
    auto &vertices = getGraph().getVertices();
    for (std::size_t i = 0 ; i < vertices.size() ; i++) {
        DijVertex::Ptr v = std::static_pointer_cast<DijVertex>(vertices[i]);
        v->nSuccessors = v->getNumberSuccessors();
        v->S = std::priority_queue<Successor, std::vector<Successor>, Successor>();
        Successor node;
        if (goals.find(vertices[i]) != goals.end()) {
            node.cost = 0;
        }
        else {
            node.cost = Long::infinity;
        }
        v->S.push(node);
    }
}

void MinMaxGame::relax(DijVertex::Ptr s, const Vertex::Edge& edge) {
    DijVertex::Ptr p = std::dynamic_pointer_cast<DijVertex>(edge.first.lock());
    const Successor &succ = s->S.top();
    Long pVal = edge.second[MIN] + succ.cost;
    const Successor &old = p->S.top();

    if (pVal < old.cost) {
        m_Q.updateKeyPointer(p, pVal);
        if (p->getPlayer() == MIN) {
            Successor newSucc;
            newSucc.cost = pVal;
            p->S = std::priority_queue<Successor, std::vector<Successor>, Successor>();
            p->S.push(newSucc);
        }
    }

    if (p->getPlayer() == MAX) {
        Successor succ;
        succ.cost = pVal;
        p->S.push(succ);
    }
}