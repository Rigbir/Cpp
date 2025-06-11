//
// Created by Marat on 11.06.25.
//

#include "Figures.h"
#include "math.h"

#define INVALID_ARGUMENT(msg) throw std::invalid_argument(std::string(msg) + \
" [File: " + __FILE__ + ", Line: " + std::to_string(__LINE__) + "]")

Rectangle::Rectangle(long double width, long double height)
        : _width(width)
        , _height(height) {}

std::string Rectangle::name() {
    return "Rectangle";
}

long double Rectangle::area() const {
    return _width * _height;
}

long double Rectangle::perimeter() const {
    return 2 * (_width + _height);
}

Triangle::Triangle(long double sideA, long double sideB, long double sideC)
        : _sideA(sideA)
        , _sideB(sideB)
        , _sideC(sideC) {}

std::string Triangle::name() {
    return "Triangle";
}

long double Triangle::area() const {
    if (!isValidTriangle()) {
        INVALID_ARGUMENT("Invalid triangle");
    }
    long double semiPerimeter = (_sideA + _sideB + _sideC) / 2.0L;
    return std::sqrtl(semiPerimeter * (semiPerimeter - _sideA)
                                    * (semiPerimeter - _sideB)
                                    * (semiPerimeter - _sideC));
}

long double Triangle::perimeter() const {
    return _sideA + _sideB + _sideC;
}

bool Triangle::isValidTriangle() const {
    return (_sideB + _sideC > _sideA)
        && (_sideA + _sideC > _sideB)
        && (_sideA + _sideB > _sideC);
}

Circle::Circle(long double radius): _radius(radius) {}

std::string Circle::name() {
    return "Circle";
}

long double Circle::area() const {
    return M_PI * _radius * _radius;
}

long double Circle::perimeter() const {
    return 2 * M_PI * _radius;
}
