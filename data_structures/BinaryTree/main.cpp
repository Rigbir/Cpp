//
// Created by Marat on 10.09.25.
//

#include "BinaryTree.h"
#include <iostream>

int main() {
    BinaryTree<int> tree;

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