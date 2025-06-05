//
// Created by Marat on 5.06.25.
//

#include "String.cpp"
#include <iostream>

int main() {
    MyString str = {'a', 'b', 'c'};

    str.print();
    std::cout << str.size() << '\n';
    std::cout << str.capacity() << '\n';

    MyString str2 = {'h', 'i'};
    str2.print();

    MyString str3 = str2;
    str3.print();
}