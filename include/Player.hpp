#pragma once

#include <unordered_set>
#include "Vertex.hpp"

/**
 * \brief Décrit un joueur
 */
class Player {
public:
    Player();
    explicit Player(const std::unordered_set<Vertex::Ptr>& vertices, const std::unordered_set<Vertex::Ptr>& goals);
    ~Player();

    /**
     * \brief Ajoute un sommet appartenant au joueur.
     * Le sommet NE peut PLUS être modifié après l'insertion sous peine de briser l'ensemble. En effet, les éléments sont stockés selon leur hash key et modifier un sommet modifie son hash key.
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
     * Le sommet NE peut PLUS être modifié après l'insertion sous peine de briser l'ensemble. En effet, les éléments sont stockés selon leur hash key et modifier un sommet modifie son hash key.
     * \param vertex Le goal
     */
    void addGoal(Vertex::Ptr vertex);

    /**
     * \brief Donne l'ensemble des cibles appartenant à ce joueur
     * \return L'ensemble des cibles de ce joueur
     */
    const std::unordered_set<Vertex::Ptr>& getGoals() const;

private:
    std::unordered_set<Vertex::Ptr> m_vertices;
    std::unordered_set<Vertex::Ptr> m_goals;
};