//
// Created by Marat on 11.06.25.
//

//#include "FiguresFactory.cpp"
#include <iostream>
#include <vector>
#include "Figures.cpp"

void print() { std::cout << '\n'; }

template <typename Head, typename... Tail>
void print(const Head& head, const Tail&... tail) {
    std::cout << head;
    print(tail...);
}

#ifdef TESTING
void handleAdd(std::vector<std::unique_ptr<Figures>>& v, std::istringstream& is) {
    if (std::unique_ptr<Figures> figure = createFigures(is)) {
        v.push_back(std::move(figure));
    } else {
        std::cout << "Invalid figure type\n";
    }
}

void handlePrint(const std::vector<std::unique_ptr<Figures>>& v) {
    for (const auto& figure : v) {
        print("Name: ", figure->name(), '\n',
              "Area: ", figure->area(), '\n',
              "Perimeter: ", figure->perimeter(), '\n');
    }
}
#endif

int main() {

    // std::vector<std::unique_ptr<Figures>> figures;
    //
    // for (std::string line; std::getline(std::cin, line);){
    //     std::istringstream is(line);
    //     std::string command;
    //     is >> command;
    //
    //     if (command == "add") {
    //         handleAdd(figures, is);
    //     } else if (command == "print") {
    //         handlePrint(figures);
    //     } else if (command == "end") {
    //         break;
    //     } else {
    //         std::cout << "Unknown command: " << command << '\n';
    //     }
    // }

    Rectangle rectangle(10, 5);
    std::cout << "Area: " << rectangle.area() << '\n';
    std::cout << "Perimeter: " << rectangle.perimeter() << '\n';

    double scale;
    std::cout << "Change scale: ";
    std::cin >> scale;
    std::cout << "New Area: " << rectangle.scale(scale) << '\n';

    std::cout << "Centroid: " << rectangle.centroid().first << ' ' << rectangle.centroid().second << '\n';
    std::cout << "Angles: " << rectangle.angles() << '\n';

    double x, y;
    std::cout << "Two point: ";
    std::cin >> x >> y;
    std::cout << "Point contains: " << rectangle.containsPointer(x, y) << '\n';
}