//
// Created by Marat on 4.10.25.
//

#include "LRUCache.h"
#include <iostream>

int main() {
    LRUCache<int, int> cache(3);

    std::cout << std::boolalpha;

    cache.put(1, 100);
    cache.put(2, 200);
    cache.put(3, 300);

    std::cout << "get(1) = " << cache.get(1) << " (expected 100)" << '\n';
    std::cout << "get(2) = " << cache.get(2) << " (expected 200)" << '\n';

    cache.put(4, 400);

    std::cout << "get(3) = " << cache.get(3) << " (expected 0, as it was evicted)" << '\n';
    std::cout << "get(4) = " << cache.get(4) << " (expected 400)" << '\n';

    cache.get(1);
    cache.put(5, 500);

    std::cout << "get(2) = " << cache.get(2) << " (expected 0, as it was evicted)" << '\n';
    std::cout << "get(1) = " << cache.get(1) << " (expected 100)" << '\n';
    std::cout << "get(5) = " << cache.get(5) << " (expected 500)" << '\n';
}