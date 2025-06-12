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
    virtual std::string name() const = 0;
    virtual long double area() const = 0;
    virtual long double perimeter() const = 0;
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

std::unique_ptr<Figures> createFigures(std::istringstream& is) {
    std::string figure;
    is >> figure;

    if (figure == "rectangle") {
        long double width, height;
        is >> width >> height;
        return std::make_unique<Rectangle>(width, height);
    } else if (figure == "triangle") {
        long double sideA, sideB, sideC;
        is >> sideA >> sideB >> sideC;
        return std::make_unique<Triangle>(sideA, sideB, sideC);
    } else if (figure == "circle") {
        long double radius;
        is >> radius;
        return std::make_unique<Circle>(radius);
    }

    return nullptr;
}

