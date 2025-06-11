//
// Created by Marat on 11.06.25.
//

#include "Figures.cpp"
#include <vector>

void print() { std::cout << '\n'; }

template <typename Head, typename... Tail>
void print(const Head& head, const Tail&... tail) {
    std::cout << head;
    print(tail...);
}

int main() {

    Rectangle rectangle(5, 4);

    print("Name Figures: ", rectangle.name(), '\n',
            "Rectangle area: ", rectangle.area(), '\n',
            "Rectangle Perimeter: ", rectangle.perimeter(), '\n');

    Triangle triangle(5, 16, 20);

    print("Name Figures: ", triangle.name(), '\n',
            "Triangle area: ", triangle.area(), '\n',
            "Triangle Perimeter: ", triangle.perimeter(), '\n');

    Circle circle(184);

    print("Name Figures: ", circle.name(), '\n',
            "Circle area: ", circle.area(), '\n',
            "Circle Perimeter: ", circle.perimeter(), '\n');
}