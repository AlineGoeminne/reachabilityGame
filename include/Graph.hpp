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
     * \brief Construit le graphe
     * \param vertices Les sommets du graphe
     */
    explicit Graph(std::vector<Vertex::Ptr>& vertices);
    /**
     * \brief Construit le graphe
     * \param vertices Les sommets du graphe
     * \param maxWeight Le poids maximal parmi les arcs
     */
    explicit Graph(std::vector<Vertex::Ptr>& vertices, long maxWeight);

    /**
     * \brief Donne le poids de l'arc entre u et v
     * \param u L'ID d'un sommet
     * \param v L'ID d'un sommet
     * \return Le poids de l'arc s'il existe, +infini sinon
     */
    Long getWeight(unsigned int u, unsigned int v) const;

private:
    /**
     * \brief Cherche le poids maximal parmi les arcs
     */
    void computeMaxWeight();

private:
    std::vector<Vertex::Ptr> m_vertices;
    long m_maxWeight;
};