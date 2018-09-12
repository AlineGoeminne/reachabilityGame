/*
 * ReachabilityGame - a program to compute the best Nash equilibrium in reachability games
 * Copyright (C) 2018 Gaëtan Staquet and Aline Goeminne
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <vector>
#include <functional>
#include <algorithm>

namespace types {
    /**
     * \brief Une file de priorité dont les clés peuvent changer.
     * 
     * Le code est grandement inspiré de l'implémentation de std::priority_queue de GCC 8.2.
     * 
     * Comme dans GCC, les fonctions utilisent std::make_heap, std::push_heap et std::pop_heap pour gérer la file.
     * 
     * \tparam T Le type de variable à stocker. Il est grandement recommander que T définisse son propre opérateur d'égalité (==)
     * \tparam Compare Le type du comparateur à utiliser. Par défaut, il s'agit de std::less qui fait en sorte que la plus grande valeur se retrouve en top de la file.
     */
    template<
        class T,
        class Compare=std::less<T>
    >
    class DynamicPriorityQueue {
    public:
        /**
         * \brief Construit la file de priorité. Le comparateur est la fonction 'operator()' de Compare.
         * 
         * En détails : la structure/classe doit avoir un constructeur par défaut et avoir une fonction avec la signature 'bool operator()(const T&, const T&) const'
         */
        DynamicPriorityQueue() : DynamicPriorityQueue(Compare()) {}
        /**
         * \brief Construit la file de priorité avec le comparateur donné
         */
        DynamicPriorityQueue(const Compare& compare) : m_compare(compare) {}

        /**
         * \brief Ajoute un nouvel élément dans la file
         * \param value La valeur à ajouter
         */
        void push(const T& value) {
            m_vector.push_back(value);
            std::push_heap(m_vector.begin(), m_vector.end(), m_compare);
        }

        /**
         * \brief Met à jour une valeur vers une nouvelle sans devoir sortir toutes les valeurs précédentes de la file.
         * 
         * Si la valeur n'est pas dans la file, rien ne se passe.
         * \param oldValue L'ancienne valeur
         * \param newValue La nouvelle valeur
         */
        void update(const T& oldValue, const T& newValue) {
            // On va chercher dans m_vector oldValue
            for (std::size_t i = 0 ; i < m_vector.size() ; i++) {
                if (m_vector[i] == oldValue) {
                    // On l'a trouvé
                    m_vector[i] = newValue;
                    std::make_heap(m_vector.begin(), m_vector.end(), m_compare);
                    return;
                }
            }
        }

        /**
         * \brief Met à jour la clé de object si le type de T est un pointeur
         * 
         * T doit définir la fonction de signature 'void updateKey(const S&)'
         * \param object L'object à mettre à jour
         * \param newKey La nouvelle clé de object
         * \tparam S Le type de la clé
         */
        template<typename S>
        void updateKeyPointer(const T& object, const S& newKey) {
            for (std::size_t i = 0 ; i < m_vector.size() ; i++) {
                if (m_vector[i] == object) {
                    m_vector[i]->updateKey(newKey);
                    std::make_heap(m_vector.begin(), m_vector.end(), m_compare);
                }
            }
        }

        /**
         * \brief Met à jour la clé de object si le type de T n'est pas un pointeur.
         * 
         * T doit définir la fonction de signature 'void updateKey(const S&)'
         * \param object L'object à mettre à jour
         * \param newKey La nouvelle clé de object
         * \tparam S Le type de la clé
         */
        template<typename S>
        void updateKeyObject(const T& object, const S& newKey) {
            for (std::size_t i = 0 ; i < m_vector.size() ; i++) {
                if (m_vector[i] == object) {
                    m_vector[i].updateKey(newKey);
                    std::make_heap(m_vector.begin(), m_vector.end(), m_compare);
                }
            }
        }

        /**
         * \brief Est-ce que la file est vide ?
         * \return Vrai ssi la file est vide
         */
        bool empty() const {
            return m_vector.empty();
        }

        /**
         * \brief Donne la valeur au top de la file.
         * 
         * Par exemple, si Compare est std::less, donne la plus grande valeur présente dans la file tandis que std::greater donne la plus petite valeur présente.
         * \return Le haut de la file
         */
        const T& top() {
            if (empty()) {
                throw std::out_of_range("La DynamicPriorityQueue est vide. Impossible de retirer un élément");
            }
            return m_vector.front();
        }

        /**
         * \brief Retire la valeur tout en haut de la file
         */
        void pop() {
            if (empty()) {
                throw std::out_of_range("La DynamicPriorityQueue est vide. Impossible de retirer un élément");
            }
            std::pop_heap(m_vector.begin(), m_vector.end(), m_compare);
            m_vector.pop_back();
        }

        /**
         * \brief Vide la pile
         */
        void clear() {
            while (!empty()) {
                pop();
            }
        }

    private:
        std::vector<T> m_vector;
        Compare m_compare;
    };
}