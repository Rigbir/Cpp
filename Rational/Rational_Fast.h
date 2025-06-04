#pragma once

class Rational {
private:
    int num;
    int denom;
    void Reduce();
public:
    Rational();
    Rational(int num_, int denom_);

    Rational operator + ();
    Rational operator - ();

    Rational operator + (const Rational& rhs, const Rational& lhs) const;
    Rational operator - (const Rational& rhs, const Rational& lhs) const;
    Rational operator * (const Rational& rhs, const Rational& lhs) const;
    Rational operator / (const Rational& rhs, const Rational& lhs) const;
    Rational operator + (int rhs) const;
    Rational operator - (int rhs) const;
    Rational operator * (int rhs) const;
    Rational operator / (int rhs) const;

    Rational& operator += (const Rational& rhs);
    Rational& operator -= (const Rational& rhs);
    Rational& operator *= (const Rational& rhs);
    Rational& operator /= (const Rational& rhs);
    Rational& operator += (int rhs);
    Rational& operator -= (int rhs);
    Rational& operator *= (int rhs);
    Rational& operator /= (int rhs);

    bool operator < (const Rational& rhs) const;
    bool operator > (const Rational& rhs) const;
    bool operator <= (const Rational& rhs) const;
    bool operator >= (const Rational& rhs) const;
    bool operator == (const Rational& rhs) const;
    bool operator != (const Rational& rhs) const;
};
