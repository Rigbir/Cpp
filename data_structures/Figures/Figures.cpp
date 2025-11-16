//
// Created by Marat on 11.06.25.
//

#include "Figures.h"
#include "math.h"

#define INVALID_ARGUMENT(msg) throw std::invalid_argument(std::string(msg) + \
" [File: " + __FILE__ + ", Line: " + std::to_string(__LINE__) + "]")

template <typename T>
long double Figures::pow(T value) {
    return std::pow(static_cast<long double>(value), 2);
}

Rectangle::Rectangle(long double width, long double height)
        : _width(width)
        , _height(height) {}

std::string Rectangle::name() const {
    return "Rectangle";
}

long double Rectangle::area() const {
    return _width * _height;
}

long double Rectangle::perimeter() const {
    return 2 * (_width + _height);
}

long double Rectangle::scale(double _scale) {
    _width *= _scale;
    _height *= _scale;
    return area();
}

std::string Rectangle::angles() const {
    return "90, 90, 90, 90";
}

std::pair<long double, long double> Rectangle::centroid() const {
    return {_width / 2, _height / 2 };
}

bool Rectangle::containsPointer(double pointFirst, double pointSecond) const {
    return pointFirst <= _width && pointFirst >= 0 && pointSecond <= _height && pointSecond >= 0;
}

Triangle::Triangle(long double sideA, long double sideB, long double sideC)
        : _sideA(sideA)
        , _sideB(sideB)
        , _sideC(sideC) {}

std::string Triangle::name() const {
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

long double Triangle::scale(double _scale) {
    _scale *= _sideA;
    _scale *= _sideB;
    _scale *= _sideC;
    return area();
}

std::string Triangle::angles() const {
    long double alpha = acos((pow(_sideB) + pow(_sideC) - pow(_sideA)) / (2 * _sideB * _sideC));
    long double beta = acos((pow(_sideA) + pow(_sideC) - pow(_sideB)) / (2 * _sideA * _sideC));
    long double gamma = acos((pow(_sideA) + pow(_sideB) - pow(_sideC)) / (2 * _sideA * _sideC));
    return std::to_string(alpha) + ' ' + std::to_string(beta) + ' ' + std::to_string(gamma);
}

std::pair<long double, long double> Triangle::centroid() const {
    long double x = (pow(_sideB) + pow(_sideC) - pow(_sideA)) / (2 * _sideC);
    long double y = sqrt(pow(_sideB) - pow(x));
    long double pointFirst = (_sideC + x) / 3;
    long double pointSecond = y / 3;
    return {pointFirst, pointSecond};
}

Circle::Circle(long double radius): _radius(radius) {}

std::string Circle::name() const {
    return "Circle";
}

long double Circle::area() const {
    return M_PI * _radius * _radius;
}

long double Circle::perimeter() const {
    return 2 * M_PI * _radius;
}

long double Circle::scale(double _scale) {
    _radius *= _scale;
    return area();
}

std::string Circle::angles() const {
    return ("360");
}

std::pair<long double, long double> Circle::centroid() const {
    return {0, 0};
}

bool Circle::containsPointer(double pointFirst, double pointSecond) const {
    return (pow(pointFirst) + pow(pointSecond)) <= (pow(_radius));
}