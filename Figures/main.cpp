//
// Created by Marat on 11.06.25.
//

#include "FiguresFactory.cpp"
#include "Figures.cpp"
#include <iostream>
#include <vector>

void print() { std::cout << '\n'; }

template <typename Head, typename... Tail>
void print(const Head& head, const Tail&... tail) {
    std::cout << head;
    print(tail...);
}

void checkEmpty(const std::vector<std::unique_ptr<Figures>>& v) {
    if (v.empty()) {
        std::cout << "No figures available.\n";
        return;
    }
}

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
              "Perimeter: ", figure->perimeter(), '\n',
              "Centroid point: ", figure->centroid().first, ' ', figure->centroid().second, '\n',
              "Angles: ", figure->angles(), '\n');
    }
}

void changeScale(const std::vector<std::unique_ptr<Figures>>& v) {
    checkEmpty(v);

    double scale;
    std::cout << "Print scale: ";
    std::cin >> scale;
    std::cout << '\n';

    for (auto& figure : v) {
        figure->scale(scale);
        handlePrint(v);
    }
}

void containsPoint(const std::vector<std::unique_ptr<Figures>>& v) {
    checkEmpty(v);

    double pointFirst, pointSecond;
    std::cout << "Enter two points: ";
    std::cin >> pointFirst >> pointSecond;
    std::cout << '\n';

    for (const auto& figure : v) {
        if (figure->name() == "Triangle") continue;
        bool contain = figure->containsPointer(pointFirst, pointSecond);
        print("For Figure ", figure->name(), ": ", std::boolalpha, contain, '\n');
    }
}

void userInterface() {
    print("Command list: ", '\n',
          "1. add -> create new figure. (add 'name figure' 'sizes figures')", '\n',
          "2. print -> print all information about figures.", '\n',
          "3. scale -> change area figures.", '\n',
          "4. point -> checks whether the point is in the figure.", '\n',
          "5. end -> end program.", '\n',
          "Program supports figures: rectangle, triangle, circle.", '\n');
}

int main() {

    userInterface();

    std::vector<std::unique_ptr<Figures>> figures;

    for (std::string line; std::getline(std::cin, line);){
        std::istringstream is(line);
        std::string command;
        is >> command;

        if (command == "add") {
            handleAdd(figures, is);
        } else if (command == "print") {
            handlePrint(figures);
        } else if (command == "scale") {
            changeScale(figures);
        } else if (command == "point") {
            containsPoint(figures);
        } else if (command == "end") {
            break;
        } else if (command.empty()) {
            continue;
        }
    }
}