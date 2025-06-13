# Rational

`Rational` is a class representing rational numbers (fractions) with integer numerators and denominators. It supports arithmetic operations, comparisons, and in-place modifications, providing both rational–rational and rational–integer interactions. All rational numbers are automatically reduced to their simplest form.

## Implemented Functionality

### Constructors

- `Rational()`  
  Default constructor. Initializes the rational number to `0/1`.

- `Rational(int num_, int denom_)`  
  Constructs a rational number with the given numerator and denominator. Automatically reduces the fraction to its simplest form.

### Unary Operators

- `Rational operator+()`  
  Returns the rational number unchanged.

- `Rational operator-()`  
  Returns the negated rational number.

### Binary Arithmetic Operators (Rational–Rational)

- `Rational operator+(const Rational& rhs, const Rational& lhs) const`  
  Returns the sum of two rational numbers.

- `Rational operator-(const Rational& rhs, const Rational& lhs) const`  
  Returns the difference of two rational numbers.

- `Rational operator*(const Rational& rhs, const Rational& lhs) const`  
  Returns the product of two rational numbers.

- `Rational operator/(const Rational& rhs, const Rational& lhs) const`  
  Returns the quotient of two rational numbers. Assumes `lhs` is not zero.

### Binary Arithmetic Operators (Rational–Integer)

- `Rational operator+(int rhs) const`  
  Adds an integer to the rational number.

- `Rational operator-(int rhs) const`  
  Subtracts an integer from the rational number.

- `Rational operator*(int rhs) const`  
  Multiplies the rational number by an integer.

- `Rational operator/(int rhs) const`  
  Divides the rational number by a non-zero integer.

### Compound Assignment Operators (Rational–Rational)

- `Rational& operator+=(const Rational& rhs)`  
  Adds another rational number in place.

- `Rational& operator-=(const Rational& rhs)`  
  Subtracts another rational number in place.

- `Rational& operator*=(const Rational& rhs)`  
  Multiplies by another rational number in place.

- `Rational& operator/=(const Rational& rhs)`  
  Divides by another rational number in place.

### Compound Assignment Operators (Rational–Integer)

- `Rational& operator+=(int rhs)`  
  Adds an integer in place.

- `Rational& operator-=(int rhs)`  
  Subtracts an integer in place.

- `Rational& operator*=(int rhs)`  
  Multiplies by an integer in place.

- `Rational& operator/=(int rhs)`  
  Divides by an integer in place.

### Comparison Operators

- `bool operator<(const Rational& rhs) const`  
  Returns `true` if the current rational number is less than `rhs`.

- `bool operator>(const Rational& rhs) const`  
  Returns `true` if greater than `rhs`.

- `bool operator<=(const Rational& rhs) const`  
  Returns `true` if less than or equal to `rhs`.

- `bool operator>=(const Rational& rhs) const`  
  Returns `true` if greater than or equal to `rhs`.

- `bool operator==(const Rational& rhs) const`  
  Returns `true` if equal to `rhs`.

- `bool operator!=(const Rational& rhs) const`  
  Returns `true` if not equal to `rhs`.

## Internal Utility

- `void Reduce()`  
  Private method that simplifies the rational number by dividing the numerator and denominator by their greatest common divisor (GCD).
