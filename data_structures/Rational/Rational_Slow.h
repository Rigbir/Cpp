//
// Created by Marat on 3.06.25.
//

#pragma once

class Rational {
private:
    int num = 0;
    int denom = 1;
    void Reduce();
public:
    Rational();
    Rational(int n, int d);
    int GetNum() const;
    int GetDenom() const;

    Rational operator + () const;
    Rational operator - () const;

    Rational operator + (const Rational& other) const;
    Rational operator - (const Rational& other) const;
    Rational operator * (const Rational& other) const;
    Rational operator / (const Rational& other) const;
    Rational operator + (int other) const;
    Rational operator - (int other) const;
    Rational operator * (int other) const;
    Rational operator / (int other) const;

    Rational& operator += (const Rational& other);
    Rational& operator -= (const Rational& other);
    Rational& operator *= (const Rational& other);
    Rational& operator /= (const Rational& other);
    Rational& operator += (int other);
    Rational& operator -= (int other);
    Rational& operator *= (int other);
    Rational& operator /= (int other);

    bool operator < (const Rational& other) const;
    bool operator > (const Rational& other) const;
    bool operator <= (const Rational& other) const;
    bool operator >= (const Rational& other) const;
    bool operator == (const Rational& other) const;
    bool operator != (const Rational& other) const;
};