//
// Created by Marat on 13.06.25.
//

#include "FiguresFactory.h"

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