#pragma once

#include <memory>
#include <map>

/**
 * \brief Un noeud du graphe
 */
class Vertex final : public std::enable_shared_from_this<Vertex> {
public:
    /**
     * \brief Le pointeur à utiliser sur un noeud
     */
    typedef std::shared_ptr<Vertex> Ptr;
    /**
     * \brief Représente un arc qui va de ce noeud vers un autre, avec un poids
     */
    typedef std::pair<Ptr, int> Edge;

public:
    /**
     * \brief Construit le noeud
     * \param id L'ID du noeud
     * \param player Le joueur qui possède ce noeud
     */
    explicit Vertex(unsigned int id, unsigned int player);
    ~Vertex();

    /**
     * \brief Ajoute un successeur à ce noeud.
     * On ajoute également le noeud actuel au successeur comme prédecesseur.
     * \param vertex Le successeur
     * \param weight Le poids de l'arc
     */
    void addSuccessor(Ptr vertex, int weight);

    /**
     * \brief Donne le successeur qui a le même ID et le poids pour y aller.
     * Si l'ID n'est pas un successeur, retourne (nullptr, 0)
     * \param id L'ID du successeur
     * \return Un tuple (successeur, poids)
     */
    Edge getSuccessor(unsigned int id) const;

    /**
     * \brief Donne le prédecesseur qui a le même ID et le poids pour y aller.
     * Si l'ID n'est pas un prédecesseur, retourne (nullptr, 0)
     * \param id L'ID du prédecesseur
     * \return Un tuple (prédecesseur, poids)
     */
    Edge getPredecessor(unsigned int id) const;

    /**
     * \brief Donne l'ID du noeud
     * \return L'ID du noeud
     */
    unsigned int getID() const;

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

private:
    // On associe (v, weight) à v.id
    typedef std::map<unsigned int, Edge> StoreEdge;

private:
    // Ajoute un prédecesseur. Similaire à addSuccessor
    void addPredecessor(Ptr vertex, int weight);

private:
    const unsigned int m_id;
    const unsigned int m_player;
    StoreEdge m_successors;
    StoreEdge m_predecessors;
};