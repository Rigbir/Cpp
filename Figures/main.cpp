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

int main() {

    std::vector<std::unique_ptr<Figures>> figures;

    for (std::string line; std::getline(std::cin, line);){
        std::istringstream is(line);
        std::string command;
        is >> command;

        if (command == "add") {
            handleAdd(figures, is);
        } else if (command == "print") {
            handlePrint(figures);
        } else if (command == "end") {
            break;
        } else {
            std::cout << "Unknown command: " << command << '\n';
        }
    }
}