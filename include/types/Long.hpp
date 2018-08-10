#include <ostream>

/**
 * \brief Une représentation d'un long permettant l'infini
 */
class Long final {
public:
    static Long infinity();

public:
    Long(long value);
    Long(const Long& value);

    bool isInfinity() const;
    long getValue() const;

    Long operator-() const;

    Long operator+(const Long& other) const;
    Long operator-(const Long& other) const;

    Long& operator+=(const Long& other);
    Long& operator-=(const Long& other);

    friend bool operator==(const Long &a, const Long& b);
    friend bool operator!=(const Long &a, const Long& b);

    friend bool operator<(const Long &a, const Long& b);
    friend bool operator>(const Long &a, const Long& b);

    friend bool operator<=(const Long &a, const Long& b);
    friend bool operator>=(const Long &a, const Long& b);

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