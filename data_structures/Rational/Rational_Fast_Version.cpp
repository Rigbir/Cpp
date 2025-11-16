//
// Created by Marat on 3.06.25.
//

#include "Rational_Fast.h"
#include <stdexcept>
#include <numeric>

void Rational::Reduce() {
    if (denom == 0) {
        throw std::invalid_argument("Denominator can't be zero.");
    }

    if (denom < 0) {
        num *= -1;
        denom *= -1;
    }

    int g = std::gcd(num, denom);
    num /= g;
    denom /= g;
}

Rational::Rational(int num_ = 0, int denom_ = 1): num(num_), denom(denom_) {
    Reduce();
}

int Rational::GetNum() const {
    return num;
}

int Rational::GetDenom() const {
    return denom;
}

Rational Rational::operator + () {
    return (num, denom);
}

Rational Rational::operator - () {
    return Rational(-num, denom);
}

Rational Rational::operator + (const Rational& rhs, const Rational& lhs) {
    Rational result = lhs;
    result += rhs;
    return result;
}

Rational Rational::operator - (const Rational& rhs, const Rational& lhs) {
    Rational result = lhs;
    result -= rhs;
    return result;
}

Rational Rational::operator * (const Rational& rhs, const Rational& lhs) {
    Rational result = lhs;
    result *= rhs;
    return result;
}

Rational Rational::operator / (const Rational& rhs, const Rational& lhs) {
    Rational result = lhs;
    result /= rhs;
    return result;
}

Rational Rational::operator + (int rhs) const {
    Rational result = *this;
    result += rhs;
    return result;
}

Rational Rational::operator - (int rhs) const {
    Rational result = *this;
    result -= rhs;
    return result;
}

Rational Rational::operator * (int rhs) const {
    Rational result = *this;
    result *= rhs;
    return result;
}

Rational Rational::operator / (int rhs) const {
    Rational result = *this;
    result /= rhs;
    return result;
}

Rational& Rational::operator += (const Rational& rhs) {
    num = num * rhs.GetDenom() + rhs.GetNum() * denom;
    denom *= rhs.GetDenom();
    Reduce();
    return *this;
}

Rational& Rational::operator -= (const Rational& rhs) {
    num = num * rhs.GetDenom() - rhs.GetNum() * denom;
    denom *= rhs.GetDenom();
    Reduce();
    return *this;
}

Rational& Rational::operator *= (const Rational &rhs) {
    num *= rhs.GetNum();
    denom *= rhs.GetDenom();
    Reduce();
    return *this;
}

Rational& Rational::operator /= (const Rational& rhs) {
    num *= rhs.GetDenom();
    denom *= rhs.GetNum();
    Reduce();
    return *this;
}

Rational& Rational::operator += (int rhs) {
    num = num + rhs * denom;
    Reduce();
    return *this;
}

Rational& Rational::operator -= (int rhs) {
    num = num - rhs * denom;
    Reduce();
    return *this;
}

Rational& Rational::operator *= (int rhs) {
    num *= rhs;
    Reduce();
    return *this;
}

Rational& Rational::operator /= (int rhs) {
    denom *= rhs;
    Reduce();
    return *this;
}

bool Rational::operator < (const Rational& rhs) const {
    return num * rhs.GetDenom() < denom * rhs.GetNum();
}

bool Rational::operator > (const Rational& rhs) const {
    return rhs < *this;
}

bool Rational::operator <= (const Rational& rhs) const {
    return !(*this > rhs);
}

bool Rational::operator >= (const Rational& rhs) const {
    return !(rhs < *this);
}

bool Rational::operator == (const Rational& rhs) const {
    return num * rhs.GetDenom() == denom * rhs.GetNum();
}

bool Rational::operator != (const Rational& rhs) const {
    return !(*this == rhs);
}

