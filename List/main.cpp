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

    l.push_back(4);
    l.print();

    auto pos = l.begin();
    std::cout << pos << '\n';

    //pos = l.insert(pos, 8);
    //l.print();

    List<int> l2(4, 1);
    l2.print();

    List<int> l3 = l;
    l3.print();

    List<int> l4 = std::move(l3);
    l4.print();

    std::cout << std::boolalpha << l4.empty() << '\n';
    l4.clear();
    std::cout << std::boolalpha << l4.empty() << '\n';

    std::cout << "List before pop_back(): ";
    l.print();
    l.pop_back();

    std::cout << "List after pop_back(): ";
    l.print();

    List<int> l5 = {1};
    l5.print();
    l5.pop_back();
    std::cout << std::boolalpha << l5.empty() << '\n';

    List<int> l6;
    l6.push_back(2);
    l6.print();

    l6.push_front(1);
    l6.print();

    l6.pop_front();
    l6.print();
}