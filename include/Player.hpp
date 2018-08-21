#pragma once

#include <unordered_set>
#include "Vertex.hpp"

/**
 * \brief Décrit un joueur
 */
class Player {
public:
    Player(unsigned int id);
    explicit Player(unsigned int id, const std::unordered_set<Vertex::Ptr>& vertices, const std::unordered_set<Vertex::Ptr>& goals);
    ~Player();

    /**
     * \brief Ajoute un sommet appartenant au joueur.
     * \param vertex Le sommet
     */
    void addVertex(Vertex::Ptr vertex);

    /**
     * \brief Donne l'ensemble des sommets appartenant à ce joueur
     * \return L'ensemble des sommets de ce joueur
     */
    const std::unordered_set<Vertex::Ptr>& getVertices() const;

    /**
     * \brief Ajoute un goal appartenant au joueur.
     * 
     * Le joueur est également enregistré dans le sommet.
     * \param vertex Le goal
     */
    void addGoal(Vertex::Ptr vertex);

    /**
     * \brief Donne l'ensemble des cibles appartenant à ce joueur
     * \return L'ensemble des cibles de ce joueur
     */
    const std::unordered_set<Vertex::Ptr>& getGoals() const;

private:
    unsigned int m_id;
    std::unordered_set<Vertex::Ptr> m_vertices;
    std::unordered_set<Vertex::Ptr> m_goals;
};