//
// Created by Marat on 14.06.25.
//

#include "List.h"
#include <iostream>


int main() {

    List<int> l = {1, 2, 3};
    List<std::string> ls = {"some", "string"};

    l.print();
    ls.print();

    l.append(4);
    l.print();

    auto pos = l.begin();
    std::cout << pos << '\n';

    pos = l.insert(pos, 8);
    pos->print();
}