//
// Created by Marat on 11.06.25.
//

#pragma once

#include <utility>
#include <string>

class Figures {
public:
    virtual std::string name() const = 0;
    virtual long double area() const = 0;
    virtual long double perimeter() const = 0;
    virtual long double scale(double _scale) = 0;
    virtual bool isConvex() const { return true; }
    virtual std::string angles() const { return {}; }
    virtual std::pair<long double, long double> centroid() const { return {}; }
    virtual bool containsPointer(double pointFirst, double pointSecond) const = 0;
    virtual ~Figures() = default;
};

class Rectangle final: public Figures {
public:

    explicit Rectangle(long double width, long double height);

    std::string name() const override;
    long double area() const override;
    long double perimeter() const override;
    long double scale(double _scale) override;
    std::string angles() const override;
    std::pair<long double, long double> centroid() const override;
    bool containsPointer(double pointFirst, double pointSecond) const override;

private:
    long double _width;
    long double _height;
};

class Triangle final: public Figures {
public:

    explicit Triangle(long double sideA, long double sideB, long double sideC);

    bool isValidTriangle() const;
    std::string name() const override;
    long double area() const override;
    long double perimeter() const override;
    long double scale(double _scale) override;
    std::string angles() const override;
    std::pair<long double, long double> centroid() const override;
    bool containsPointer(double pointFirst, double pointSecond) const override;

private:
    long double _sideA;
    long double _sideB;
    long double _sideC;
};

class Circle final: public Figures {
public:

    explicit Circle(long double radius);

    std::string name() const override;
    long double area() const override;
    long double perimeter() const override;
    long double scale(double _scale) override;
    bool containsPointer(double pointFirst, double pointSecond) const override;

private:
    long double _radius;
};
