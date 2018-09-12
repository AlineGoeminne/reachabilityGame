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

#include "types/Long.hpp"

#include <iostream>
#include <cmath>

#include "types/InfinityError.hpp"

namespace types {
    const Long Long::infinity = Long::make_infinity();

    Long::Long() :
        m_value(0),
        m_infinity(false)
        {

    }

    Long::Long(long value) :
        m_value(value),
        m_infinity(false)
        {

    }

    Long::Long(const Long& value) :
        m_value(value.m_value),
        m_infinity(value.m_infinity)
        {

    }

    bool Long::isInfinity() const {
        return m_infinity;
    }

    long Long::getValue() const {
        return m_value;
    }

    Long Long::operator-() const {
        Long l = *this; // On copie
        l.m_value = -l.m_value; // On oppose la valeur
        return l;
    }

    Long Long::operator+(const Long& other) const {
        if (isInfinity() || other.isInfinity()) {
            if (isInfinity() && other.isInfinity() && m_value != other.m_value) {
                // Pas le même infini
                throw InfinityError("+infini -infini n'est pas une opération autorisée");
            }
            else if (isInfinity()) {
                return *this;
            }
            else {
                return other;
            }
            return Long::infinity;
        }
        else {
            Long l(m_value + other.m_value);
            return l;
        }
    }

    Long Long::operator-(const Long& other) const {
        if (isInfinity() || other.isInfinity()) {
            if (isInfinity() && other.isInfinity() && m_value == other.m_value) {
                // Même infini => erreur
                throw InfinityError("+infini -infini n'est pas une opération autorisée");
            }
            else if (isInfinity()) {
                return *this;
            }
            else {
                return -other;
            }
        }
        else {
            Long l(m_value - other.m_value);
            return l;
        }
    }

    Long Long::operator*(const Long& other) const {
        if (isInfinity() && other.isInfinity()) {
            if (m_value == other.m_value) {
                // +inf * +inf = +inf
                // -inf * -inf = +inf
                return Long::infinity;
            }
            else {
                // +inf * -inf = -inf
                // -inf * +inf = -inf
                return -Long::infinity;
            }
        }
        else if (isInfinity() || other.isInfinity()) {
            if (std::signbit(m_value) == std::signbit(other.m_value)) {
                // Même signe => +inf
                return Long::infinity;
            }
            else {
                return -Long::infinity;
            }
        }
        else {
            // Pas d'infini => simple multiplication de deux nombres
            return m_value * other.m_value;
        }
    }

    Long& Long::operator+=(const Long& other) {
        if (other.isInfinity()) {
            if (isInfinity() && other.isInfinity() && m_value != other.m_value) {
                throw InfinityError("+infini -infini n'est pas une opération autorisée");
            }
            m_infinity = true;
            m_value = other.m_value;
        }
        else if (!isInfinity()) {
            // On ne change rien si c'est déjà l'infini
            m_value += other.m_value;
        }
        return *this;
    }

    Long& Long::operator-=(const Long& other) {
        if (other.isInfinity()) {
            if (isInfinity() && other.isInfinity() && m_value == other.m_value) {
                throw InfinityError("+infini -infini n'est pas une opération autorisée");
            }
            m_infinity = true;
            m_value = other.m_value;
        }
        else if (!isInfinity()) {
            // On ne change rien si c'est déjà l'infini
            m_value -= other.m_value;
        }
        return *this;
    }

    Long Long::make_infinity() {
        Long l(1);
        l.m_infinity = true;
        return l;
    }

    bool operator==(const Long& a, const Long& b) {
        if (a.isInfinity()) {
            if (b.isInfinity() && a.m_value == b.m_value) {
                // Mêmes infinis
                return true;
            }
            return false;
        }
        else {
            if (b.isInfinity()) {
                return false;
            }
            return a.m_value == b.m_value;
        }
    }

    bool operator!=(const Long& a, const Long& b) {
        return !(a == b);
    }

    bool operator<(const Long& a, const Long& b) {
        if (a.isInfinity()) {
            if (b.isInfinity()) {
                return a.m_value < b.m_value;
            }
            // Si +infini, toujours >
            // Si -infini, toujours <
            return a.m_value < 0;
        }
        else {
            if (b.isInfinity()) {
                return b.m_value > 0;
            }
            return a.m_value < b.m_value;
        }
    }

    bool operator>(const Long& a, const Long& b) {
        if (a.isInfinity()) {
            if (b.isInfinity()) {
                return a.m_value > b.m_value;
            }
            // Si +infini, toujours >
            // Si -infini, toujours <
            return a.m_value > 0;
        }
        else {
            if (b.isInfinity()) {
                return b.m_value < 0;
            }
            return a.m_value > b.m_value;
        }
    }

    bool operator<=(const Long& a, const Long& b) {
        return a == b || a < b;
    }

    bool operator>=(const Long& a, const Long& b) {
        return a == b || a > b;
    }

    std::ostream& operator<<(std::ostream &os, const Long &a) {
        if (a.isInfinity()) {
            if (a.getValue() < 0) {
                os << "-infini";
            }
            else {
                os << "+infini";
            }
        }
        else {
            os << a.getValue();
        }
        return os;
    }
}