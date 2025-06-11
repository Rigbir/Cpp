//
// Created by Marat on 11.06.25.
//

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <memory>

class Figures {
public:
    virtual std::string name() = 0;
    virtual long double area() const = 0;
    virtual long double perimeter() const = 0;
};

class Rectangle: public Figures {
public:

    Rectangle(long double width, long double height);

    std::string name() override;
    long double area() const override;
    long double perimeter() const override;

private:
    long double _width;
    long double _height;
};

class Triangle: public Figures {
public:

    Triangle(long double sideA, long double sideB, long double sideC);

    std::string name() override;
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

    std::string name() override;
    long double area() const override;
    long double perimeter() const override;

private:
    long double _radius;
};



