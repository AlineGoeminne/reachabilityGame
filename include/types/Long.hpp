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
#include <ostream>
#include <vector>

/**
 * \brief Les types de données utilisés dans le reste du code
 */
namespace types {
    /**
     * \brief Une représentation d'un long permettant l'infini
     */
    class Long final {
    public:
        /**
         * \brief Construit un +infini
         */
        static const Long infinity;

    public: 
        /**
         * \brief Construit un Long de valeur 0
         */
        Long();
        /**
         * \brief Construit un Long avec la valeur donnée
         * \param value La valeur
         */
        Long(long value);
        /**
         * \brief Copie un Long
         * \param value L'autre Long
         */
        Long(const Long& value);

        /**
         * \brief Est-ce que le Long représente l'infini
         * \return Vrai si c'est un infini, faux sinon
         */
        bool isInfinity() const;

        /**
         * \brief Donne la valeur du Long.
         * 
         * Si le Long représente l'infini, le signe de la valeur retournée donne le signe de l'infini
         * \return La valeur du long
         */
        long getValue() const;

        Long operator-() const;

        Long operator+(const Long& other) const;
        Long operator-(const Long& other) const;
        Long operator*(const Long& other) const;

        Long& operator+=(const Long& other);
        Long& operator-=(const Long& other);

        friend bool operator==(const Long &a, const Long& b);
        friend bool operator!=(const Long &a, const Long& b);

        friend bool operator<(const Long &a, const Long& b);
        friend bool operator>(const Long &a, const Long& b);

        friend bool operator<=(const Long &a, const Long& b);
        friend bool operator>=(const Long &a, const Long& b);

    private:
        static Long make_infinity();

    private:
        long m_value; // Si infinity, 1 -> +infini, -1 -> -infini
        bool m_infinity;
    };

    bool operator==(const Long& a, const Long& b);
    bool operator!=(const Long& a, const Long& b);
    bool operator<(const Long& a, const Long& b);
    bool operator>(const Long& a, const Long& b);
    bool operator<=(const Long& a, const Long& b);
    bool operator>=(const Long& a, const Long& b);

    std::ostream& operator<<(std::ostream &os, const Long &a);
}