//
// Created by Marat on 11.06.25.
//

#include "Figures.cpp"

int main() {

    Rectangle rectangle(5, 4);

    std::cout << "Name Figures: " << rectangle.name() << '\n';
    std::cout << "Rectangle Area: " << rectangle.area() << '\n';
    std::cout << "Rectangle Perimeter: " << rectangle.perimeter() << "\n\n";

    Triangle triangle(5, 16, 20);

    std::cout << "Name Figures: " << triangle.name() << '\n';
    std::cout << "Triangle Area: " << triangle.area() << '\n';
    std::cout << "Triangle Perimeter: " << triangle.perimeter() << "\n\n";

    Circle circle(184);

    std::cout << "Name Figures: " << circle.name() << '\n';
    std::cout << "Triangle Area: " << circle.area() << '\n';
    std::cout << "Triangle Perimeter: " << circle.perimeter() << "\n\n";

}