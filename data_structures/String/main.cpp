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

    std::cout << str3.empty() << '\n';

    str.push_back('f');
    str.print();
    std::cout << str.size() << '\n';
    std::cout << str.capacity() << '\n';

    str.push_back('f');
    str.print();
    std::cout << str.size() << '\n';
    std::cout << str.capacity() << '\n';

    str.pop_back();
    str.print();
    std::cout << str.size() << '\n';
    std::cout << str.capacity() << '\n';
    str.pop_back();

    MyString str4 = {'a', 'b', 'c'};
    bool equal = str == str4;
    std::cout << equal << '\n';

    MyString str5 = str4.substr(1, 2);
    str5.print();

    std::cout << str5.find('b', 0) << '\n';

    MyString str6 = "abracadabra";
    MyString str7 = "cad";
    str6.print();
    std::cout << str6.find(str7, 0) << '\n';

    for (const char& c : str6) {
        std::cout << c << '\t';
    }

    std::cout << '\n';
    std::cout << str6 << '\n';

    MyString s;
    std::cin >> s;
    std::cout << s << '\n';
}