#pragma once

#include <vector>
#include <queue>
#include <iostream>

#include "Game.hpp"
#include "Player.hpp"
#include "ReachabilityGame.hpp"
#include "types/Long.hpp"
#include "types/DynamicPriorityQueue.hpp"

class MinMaxGame : public Game {
public:
    std::vector<Long> getValues();

    static MinMaxGame convert(ReachabilityGame& game, unsigned int minPlayer);

private:
    struct DijVertex;
    // Structure pour S
    struct Successor {
        Long cost;
        std::shared_ptr<DijVertex> pred;

        // Servira pour l'ordre dans la priority_queue
        bool operator()(const Successor &a, const Successor &b) {
            // On veut la plus petite valeur en haut de la pile
            return a.cost > b.cost;
        }
    };

    // Structure pour Q
    struct DijVertex : public Vertex {
        typedef std::shared_ptr<DijVertex> Ptr;

        Long d;
        std::size_t nSuccessors;
        std::priority_queue<Successor, std::vector<Successor>, Successor> S;

        DijVertex(unsigned int ID, unsigned int player, std::size_t nPlayers);

        void updateKey(Long d) {
            this->d = d;
        }
    };

    struct CompareDijVertex {
        bool operator()(const DijVertex::Ptr &a, const DijVertex::Ptr &b) {
            return a->d > b->d;
        }
    };

private:
    MinMaxGame(Graph &graph, Vertex::Ptr init, const Player& min, const Player& max);

    void dijkstraMinMax();

    void initQ();
    void initS();
    void relax(DijVertex::Ptr s, const Vertex::Edge &edge);

private:
    Player m_min, m_max;
    DynamicPriorityQueue<DijVertex::Ptr, CompareDijVertex> m_Q; // Q
};