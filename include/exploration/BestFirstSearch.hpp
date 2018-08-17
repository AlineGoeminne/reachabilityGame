#pragma once

#include <functional>
#include <vector>
#include <map>

#include "Vertex.hpp"
#include "Path.hpp"

class ReachabilityGame;

/**
 * \brief Contient les algorithmes d'exploration
 */
namespace exploration {

    /**
     * \brief Un état de l'exploration.
     * 
     * Contient le RP total, les coûts par joueur et l'ensemble des joueurs qui n'ont pas encore atteint une cible
     */
    struct State {
        State(std::size_t nPlayers) :
            RP(0),
            costsPlayers(nPlayers, 0)
            {
            for (unsigned int i = 0 ; i < nPlayers ; i++) {
                notVisitedPlayers.insert(i);
            }
        }

        types::Long RP; // Somme des coûts
        std::vector<types::Long> costsPlayers; // Coût par joueur jusqu'au sommet courant
        std::unordered_set<unsigned int> notVisitedPlayers; // Ensemble des joueurs qui n'ont pas encore atteint un objectif
    };

    /**
     * \brief Un noeud de l'exploration
     */
    struct Node {
        typedef std::shared_ptr<Node> Ptr;

        Node(std::size_t nPlayers, Path p) :
            state(nPlayers),
            pathCost(0),
            path(p)
            {
        }

        Node(State s, types::Long pcost, Path p) :
            state(s),
            pathCost(pcost),
            path(p)
            {
        }

        Node(Node::Ptr node) :
            state(node->state),
            pathCost(node->pathCost),
            path(node->path)
            {

        }

        State state;
        types::Long pathCost;
        Path path;
    };

    /**
     * \brief Pour chaque sommet, contient les coûts minimaux pour arriver vers un sommet donné
     */
    typedef std::vector<types::Long> CostsForATarget;
    /**
     * \brief Pour chaque sommet enregistré, contient un CostsForATarget vers ce sommet
     */
    typedef std::unordered_map<Vertex::Ptr, CostsForATarget> CostsMap;
    /**
     * \brief La signature qu'une fonction heuristique doit avoir.
     * 
     * \param node Le noeud d'exploration pour lequel on veut calculer la valeur
     * \param epsilon Les coûts jusqu'au noeud courant
     * \param costsMap Pour chaque cible, contient les coûts minimaux pour y arriver par sommet du graphe
     * \return La valeur de l'heuristique
     */
    typedef std::function<types::Long(const Node::Ptr& node, const std::vector<types::Long>& epsilon, const CostsMap& costsMap)> heuristicSignature;

    /**
     * \brief Exécute une exploration de type Best First Search avec l'heuristique donnée
     * \param game Le jeu
     * \param heuristic L'heuristique
     * \param allowedTime Le temps permis en secondes
     */
    Path bestFirstSearch(const ReachabilityGame& game, const heuristicSignature& heuristic, types::Long allowedTime = types::Long::infinity);
}