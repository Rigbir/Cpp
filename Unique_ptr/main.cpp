//
// Created by Marat on 25.09.25.
//

#include <iostream>
#include "Unique_ptr.h"

int main() {

    auto x = make_unique<int>(5);
    std::cout << &x << ' ' << *x << '\n';

    const auto y = std::move(x);
    std::cout << *y << '\n';

    auto n = make_unique<int>(4);
    std::cout << *n << '\n';

    n.reset(new int(56));
    std::cout << *n << '\n';

    n.reset();
    if (!n) {
        std::cout << "n: empty" << '\n';
    }

    auto f = make_unique<int>(1);
    const int* g = f.release();
    if (!f) {
        std::cout << "f: empty" << '\n';
    }
    std::cout << *g << '\n';

    delete g;

    auto r1 = make_unique<int>(10);
    auto r2 = make_unique<int>(11);
    std::cout << *r1 << '\n';
    std::cout << *r2 << '\n';

    r2.swap(r1);

    std::cout << *r1 << '\n';
    std::cout << *r2 << '\n';

    if (r2 != nullptr) {
        std::cout << "not empty" << '\n';
    }
}
