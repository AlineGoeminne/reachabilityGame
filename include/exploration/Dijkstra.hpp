#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ReachabilityGame.hpp"
#include "Vertex.hpp"
#include "Graph.hpp"

/**
 * \brief Les coûts par joueur
 */
typedef std::vector<Long> CostPlayers;
/**
 * \brief Les coûts à partir de chaque sommet
 */
typedef std::vector<CostPlayers> CostVertices;
/**
 * \brief Les coûts pour arriver à chaque sommet.
 * 
 * Pour chaque sommet enregistré, donne, pour chacun des sommets du graphe, le coût pour y arriver par joueur
 */
typedef std::unordered_map<Vertex::Ptr, CostVertices> CostDijkstra;

/**
 * \brief Exécute Dijkstra
 */
CostDijkstra dijkstra(const Graph &graph, const std::unordered_set<Vertex::Ptr> starts);
CostVertices dijkstra(const Graph &graph, Vertex::Ptr start);