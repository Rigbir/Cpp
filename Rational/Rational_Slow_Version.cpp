#include "Rational_Slow.h"
#include <stdexcept>
#include <numeric>

void Rational::Reduce() {
    if (denom == 0) {
        throw std::invalid_argument("Denominator can't be zero");
    }

    if (denom < 0) {
        num *= -1;
        denom *= -1;
    }

    int g = std::gcd(num, denom);
    num /= g;
    denom /= g;
}

Rational::Rational(): num(0), denom(1) {
};

Rational::Rational(int n, int d): num(n), denom(d) { Reduce(); };

int Rational::GetNum() const {
    return num;
}

int Rational::GetDenom() const {
    return denom;
}

Rational Rational::operator + () const {
    return *this;
}

Rational Rational::operator - () const {
    return Rational(-num, denom);
}

Rational Rational::operator + (const Rational &other) const {
    return Rational(num * other.GetDenom() + other.GetNum() * denom,
                    denom * other.GetDenom());
}

Rational Rational::operator - (const Rational &other) const {
    return Rational(num * other.GetDenom() - other.GetNum() * denom,
                    denom * other.GetDenom());
}

Rational Rational::operator * (const Rational &other) const {
    return Rational(num * other.GetNum(), denom * other.GetDenom());
}

Rational Rational::operator / (const Rational &other) const {
    return Rational(num * other.GetDenom(), denom * other.GetNum());
}

Rational Rational::operator + (int other) const {
    return Rational(num + denom * other, denom);
}

Rational Rational::operator - (int other) const {
    return Rational(num - denom * other, denom);
}

Rational Rational::operator * (int other) const {
    return Rational(num * other, denom);
}

Rational Rational::operator / (int other) const {
    return Rational(num, denom * other);
}

Rational& Rational::operator += (const Rational &other) {
    return *this = *this + other;
}

Rational& Rational::operator -= (const Rational &other) {
    return *this = *this - other;
}

Rational& Rational::operator *= (const Rational &other) {
    return *this = *this * other;
}

Rational& Rational::operator /= (const Rational &other) {
    return *this = *this / other;
}

Rational& Rational::operator += (int other) {
    return *this = *this + other;
}

Rational& Rational::operator -= (int other) {
    return *this = *this - other;
}

Rational& Rational::operator *= (int other) {
    return *this = *this * other;
}

Rational& Rational::operator /= (int other) {
    return *this = *this / other;
}

bool Rational::operator < (const Rational &other) const {
    return num * other.denom < other.num < denom;
}

bool Rational::operator > (const Rational &other) const {
    return other < *this;
}

bool Rational::operator <= (const Rational &other) const {
    return !(other > *this);
}

bool Rational::operator >= (const Rational &other) const {
    return !(*this < other);
}

bool Rational::operator == (const Rational &other) const {
    return num * other.denom == other.num * denom;
}

bool Rational::operator !=(const Rational &other) const {
    return !(*this == other);
}
