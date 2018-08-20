#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <unordered_set>

#include "types/Long.hpp"

/**
 * \brief Un noeud du graphe.
 * 
 * Un noeud est décrit par son ID, ses successeurs, ses prédecesseurs, son joueur et pour quel(s) joueur(s) il est une cible
 */
class Vertex : public std::enable_shared_from_this<Vertex> {
public:
    /**
     * \brief Le pointeur à utiliser sur un noeud
     */
    typedef std::shared_ptr<Vertex> Ptr;
    /**
     * \brief Représente un arc qui va de ce noeud vers un autre, avec un poids par joueur
     */
    typedef std::pair<Ptr, std::vector<types::Long>> Edge;

    /**
     * \brief Type de la map servant à stocker les arcs.
     * 
     * On associe à l'ID de l'autre noeud de l'arc, un pointeur vers cet autre noeud et les poids de l'arc
     */
    typedef std::unordered_map<unsigned int, Edge> StoreEdge;

public:
    /**
     * \brief Construit le noeud
     * \param id L'ID du noeud
     * \param player Le joueur qui possède ce noeud
     * \param nPlayers Le nombre de joueurs
     */
    explicit Vertex(unsigned int id, unsigned int player, std::size_t nPlayers);
    ~Vertex();

    /**
     * \brief Ajoute un successeur à ce noeud avec un poids commun à tous les joueurs.
     * 
     * On ajoute également le noeud actuel au successeur comme prédecesseur.
     * \param vertex Le successeur
     * \param weight Le poids de l'arc
     */
    virtual void addSuccessor(Ptr vertex, types::Long weight);

    /**
     * \brief Ajoute un successeur à ce noeud avec un poids par joueur.
     * 
     * On ajoute également le noeud actuel au successeur comme prédecesseur.
     * \param vertex Le successeur
     * \param weights Les poids de l'arc
     */
    virtual void addSuccessor(Ptr vertex, std::vector<types::Long> weights);

    /**
     * \brief Donne le successeur qui a le même ID et le poids pour y aller.
     * 
     * Si l'ID n'est pas un successeur, retourne (nullptr, 0)
     * \param id L'ID du successeur
     * \return Un tuple (successeur, poids)
     */
    Edge getSuccessor(unsigned int id) const;

    /**
     * \brief Donne le prédecesseur qui a le même ID et le poids pour y aller.
     * 
     * Si l'ID n'est pas un prédecesseur, retourne (nullptr, 0)
     * \param id L'ID du prédecesseur
     * \return Un tuple (prédecesseur, poids)
     */
    Edge getPredecessor(unsigned int id) const;

    /**
     * \brief Détermine si le sommet a un successeur avec l'ID donné.
     * \param id L'ID du successeur
     * \return Vrai ssi le sommet a un successeur ID
     */
    bool hasSuccessor(unsigned int id) const;

    /**
     * \brief Donne les coûts pour aller du noeud courant à son prédecesseur id.
     * \param id L'ID du prédecesseur
     * \return Les coûts de l'arc, ou +infini si id n'est pas successeur du sommet
     */
    std::vector<types::Long> getWeights(unsigned int id) const;

    /**
     * \brief Donne l'ID du noeud
     * \return L'ID du noeud
     */
    unsigned int getID() const;

    /**
     * \brief Donne l'ID du joueur qui possède ce sommet
     * \return L'ID du joueur
     */
    unsigned int getPlayer() const;

    /**
     * \brief Donne le nombre de successeurs de ce noeud
     * \return Le nombre de successeurs de ce noeud
     */
    std::size_t getNumberSuccessors() const;

    /**
     * \brief Donne le nombre de prédecesseurs de ce noeud
     * \return Le nombre de prédecesseurs de ce noeud
     */
    std::size_t getNumberPredecessors() const;

    /**
     * \brief Retourne un itérateur sur le début des successeurs
     * \return Un itérateur sur le début des successeurs
     */
    StoreEdge::iterator begin();

    /**
     * \brief Retourne un itérateur sur la fin des successeurs
     * \return Un itérateur sur la fin des successeurs
     */
    StoreEdge::iterator end();

    /**
     * \brief Retourne un itérateur sur le début des prédecesseurs
     * \return Un itérateur sur le début des prédecesseurs
     */
    StoreEdge::iterator beginPredecessors();

    /**
     * \brief Retourne un itérateur sur la fin des prédecesseurs
     * \return Un itérateur sur la fin des prédecesseurs
     */
    StoreEdge::iterator endPredecessors();

    /**
     * \brief Regarde si le noeud est une cible pour un joueur
     * \return Vrai ssi le sommet une cible pour un joueur quelconque
     */
    bool isTarget() const;

    /**
     * \brief Regarde si le sommet une cible pour le joueur donné
     * \param player Le joueur
     * \return Vrai ssi le sommet une cible pour le joueur donné
     */
    bool isTargetFor(unsigned int player) const;

    /**
     * \brief Donne l'ensemble des joueurs qui ont ce sommet comme cible
     * \return L'ensemble des joueurs qui ont ce sommet comme cible
     */
    const std::unordered_set<unsigned int>& getTargetPlayers() const;

    /**
     * \brief Enregistre le sommet comme une cible pour le joueur donné
     * \param player Le joueur
     */
    void addTargetFor(unsigned int player);

    friend bool operator==(const Vertex &a, const Vertex &b);
    friend std::ostream& operator<<(std::ostream &os, const Vertex &a);

private:
    // Ajoute un prédecesseur. Similaire à addSuccessor
    void addPredecessor(Ptr vertex, std::vector<types::Long> weight);

private:
    const std::size_t m_nPlayers;
    const unsigned int m_id;
    const unsigned int m_player;
    StoreEdge m_successors;
    StoreEdge m_predecessors;
    std::unordered_set<unsigned int> m_target; // On stocke les IDs des joueurs
};

bool operator==(const Vertex &a, const Vertex &b);
bool operator!=(const Vertex &a, const Vertex &b);
std::ostream& operator<<(std::ostream &os, const Vertex &a);

// On va définir hash et equal_to pour Vertex::Ptr afin de pouvoir facilement utiliser les unordered_set/map
namespace std {
    template<>
    struct hash<Vertex::Ptr> {
        size_t operator()(const Vertex::Ptr &v) const noexcept {
            return hash<unsigned int>{}(v->getID());
        }
    };

    template<>
    struct equal_to<Vertex::Ptr> {
        bool operator()(const Vertex::Ptr &a, const Vertex::Ptr &b) const noexcept {
            return *a == *b;
        }
    };
}