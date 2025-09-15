//
// Created by Marat on 4.06.25.
//

#include "Vector.h"
#include <iostream>

int main() {

    MyVector<int> vec(5, -2);

    vec.print();

    std::cout << "Front: " << vec.front() << '\n';
    std::cout << "Back: " << vec.back() << '\n';
    std::cout << "Size: " << vec.size() << '\n';
    std::cout << "Capacity: " << vec.capacity() << '\n';
    std::cout << "Value of Index: " << vec[2] << '\n';

    vec.clear();
    vec.push_back(3);
    vec.push_back(8);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(1);
    vec.push_back(9);

    for (auto i = vec.begin(); i != vec.end(); ++i) {
        std::cout << *i << ' ';
    }
    std::cout << '\n';

    MyVector<std::string> vec2 = {"some", "test"};
    vec2.print();
}
