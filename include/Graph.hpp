#pragma once

#include <vector>
#include <initializer_list>

#include "Vertex.hpp"
#include "types/Long.hpp"

/**
 * \brief Un graphe
 */
class Graph final {
public:
    /**
     * \brief Construit le graphe.
     * Ce constructeur cherche le poids maximal parmi les arcs
     * \param vertices Les sommets du graphe
     * \param nPlayers Le nombre de joueurs
     */
    explicit Graph(std::vector<Vertex::Ptr>& vertices, std::size_t nPlayers);
    /**
     * \brief Construit le graphe
     * \param vertices Les sommets du graphe
     * \param maxWeight Le poids maximal parmi les arcs
     */
    explicit Graph(std::vector<Vertex::Ptr>& vertices, std::vector<long> maxWeight);

    /**
     * \brief Donne les poids de l'arc entre u et v
     * \param u L'ID d'un sommet
     * \param v L'ID d'un sommet
     * \return Les poids de l'arc si l'arc existe, +infini sinon
     */
    std::vector<Long> getWeights(unsigned int u, unsigned int v) const;

private:
    /**
     * \brief Cherche, pour chaque joueur, le poids maximal parmi les arcs
     */
    void computeMaxWeights(std::size_t nPlayers);

private:
    std::vector<Vertex::Ptr> m_vertices;
    std::vector<long> m_maxWeights;
};