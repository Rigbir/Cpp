//
// Created by Marat on 10.09.25.
//

#include "BinaryTree.h"
#include <iostream>
#include <random>

struct A {
    int b;
    int c;
};

int main() {
    BinaryTree<int> tree;

    /*
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,10);

    for (size_t i = 0; i < 5; ++i) {
        tree.add(dist(gen));
    }
    */

    tree.add(5);
    tree.add(3);
    tree.add(6);
    tree.add(2);
    tree.add(1);
    tree.add(4);

    tree.print();
    std::cout << std::boolalpha << tree.find(1) << '\n';

    tree.del(5);

    tree.print();
    std::cout << std::boolalpha << tree.find(1) << '\n';

    std::cout << "Height: " << tree.height() << '\n';
    std::cout << "Min value: " << tree.minValue() << '\n';
    std::cout << "Max value: " << tree.maxValue() << '\n';

    std::cout << "In-Order: ";
    tree.inOrder();
    std::cout << '\n';

    std::cout << "Pre-Order: ";
    tree.preOrder();
    std::cout << '\n';

    std::cout << "Post-Order: ";
    tree.postOrder();
    std::cout << '\n';
}