//
// Created by Marat on 11.06.25.
//

#pragma once

#include <iostream>
#include <string>
#include <list>

class Figures {
public:
    virtual std::string name() const = 0;
    virtual long double area() const = 0;
    virtual long double perimeter() const = 0;
    virtual long double scale(long double scale) = 0;
    virtual bool isConvex() const {}
    virtual std::list<std::string> angles() const {}
    virtual long double centroid() const {}
    virtual bool containsPointer(double pointFirst, double pointSecond) const = 0;
    virtual ~Figures() = default;
};

class Rectangle: public Figures {
public:

    Rectangle(long double width, long double height);

    std::string name() const override;
    long double area() const override;
    long double perimeter() const override;

private:
    long double _width;
    long double _height;
};

class Triangle: public Figures {
public:

    Triangle(long double sideA, long double sideB, long double sideC);

    std::string name() const override;
    long double area() const override;
    long double perimeter() const override;
    bool isValidTriangle() const;

private:
    long double _sideA;
    long double _sideB;
    long double _sideC;
};

class Circle: public Figures {
public:

    Circle(long double radius);

    std::string name() const override;
    long double area() const override;
    long double perimeter() const override;

private:
    long double _radius;
};