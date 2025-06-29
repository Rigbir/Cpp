//
// Created by Marat on 14.06.25.
//

#include "List.h"
#include <iostream>

struct point {
    int x, y;
};

int main() {

    MyList<int> l = {1, 2, 3};
    MyList<std::string> ls = {"some", "string"};

    l.print();
    ls.print();

    l.push_back(4);
    l.print();

    MyList<int> l2(4, 1);
    l2.print();

    MyList<int> l3 = l;
    l3.print();

    MyList<int> l4 = std::move(l3);
    l4.print();

    std::cout << std::boolalpha << l4.empty() << '\n';
    l4.clear();
    std::cout << std::boolalpha << l4.empty() << '\n';

    std::cout << "MyList before pop_back(): ";
    l.print();
    l.pop_back();

    std::cout << "MyList after pop_back(): ";
    l.print();

    MyList<int> l5 = {1};
    l5.print();
    l5.pop_back();
    std::cout << std::boolalpha << l5.empty() << '\n';

    MyList<int> l6;
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

    MyList<int> l7 = {1, 2, 3, 8};
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

    MyList<int> l8 = {1, 2, 3};
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

    std::cout << "MyList before swap: ";
    std::cout << "First: ";
    l7.print();
    std::cout << "Second: ";
    l8.print();

    l7.swap(l8);

    std::cout << "MyList after swap: " << '\n';
    std::cout << "First: ";
    l7.print();
    std::cout << "Second: ";
    l8.print();

    MyList<int> l9 = {8, 1, 5, 1, 1, 1, 4, 1, 2, 19, 19, 19};
    l9.remove(1);
    l9.print();

    l9.unique();
    l9.print();

    MyList<int> l10 = {1, 2, 3, 4, 5};
    MyList<int> l11 = {10, 11, 12};
    auto p = l10.begin();
    ++p;
    ++p;

    l10.print();
    l10.reverse();
    l10.print();

    //l10.splice(p, l11);

    MyList<int> l12 = {8, 2, 4, 9, 7};
    auto begin = l12.begin();
    auto end = l12.end();
    l12.print();
    l12.sort(begin, end);
    l12.print();
}