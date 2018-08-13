#pragma once

#include <vector>
#include <queue>

#include "Game.hpp"
#include "Player.hpp"
#include "ReachabilityGame.hpp"
#include "types/Long.hpp"

class MinMaxGame : public Game {
public:
    MinMaxGame(Graph &graph, Vertex::Ptr init, const Player& min, const Player& max);

    std::vector<Long> getValues();

    static MinMaxGame convert(ReachabilityGame& game, unsigned int minPlayer);

private:
    // Structure pour S
    struct Sucessor {
        Long cost;
        std::shared_ptr<Sucessor> pred;

        // Servira pour l'ordre dans la priority_queue
        bool operator()(const Sucessor &a, const Sucessor &b) {
            // On veut la plus petite valeur en haut de la pile
            return a.cost > b.cost;
        }
    };

private:
    void DijkstraMinMax();

    void initQ();
    void initS();

private:
    Player m_min, m_max;
    const std::unordered_set<Vertex::Ptr> &m_goals; // Référence vers les goals de Min
    std::vector<std::priority_queue<Sucessor, std::vector<Sucessor>, Sucessor>> m_S; // S
};