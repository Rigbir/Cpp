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

    int size = l6.size();
    int size2 = l.size();
    std::cout << "Size: " << size << '\n';
    std::cout << "Size: " << size2 << '\n';

    size_t maxSize = l6.max_size();
    std::cout << "Max size: " << maxSize << '\n';

    l6.resize(10);
    l6.print();
    size = l6.size();
    std::cout << "Size: " << size << '\n';

    l.resize(1);
    l.print();

    List<int> l7 = {1, 2, 3, 8};
    auto it = l7.begin();
    std::cout << *it << '\n';

    for (auto value : l7) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    for (auto it = l7.begin(); it != l7.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    List<int> l8 = {1, 2, 3};
    auto pos = l8.begin();
    //++pos;

    auto last = pos;
    while (pos != l8.end()) {
        last = pos;
        ++pos;
    }

    l8.insert(last, 6);
    l8.print();

    l8.erase(++(l8.begin()));
    l8.print();

    l8.insert(l8.begin(), 9);
    l8.print();

    std::cout << "List before swap: ";
    std::cout << "First: ";
    l7.print();
    std::cout << "Second: ";
    l8.print();

    l7.swap(l8);

    std::cout << "List after swap: " << '\n';
    std::cout << "First: ";
    l7.print();
    std::cout << "Second: ";
    l8.print();
}