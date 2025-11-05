//
// Created by Marat on 14.06.25.
//

#include "List.h"
#include <iostream>

void testMerge() {
    std::cout << "\n=== Test merge() ===\n";
    MyList<int> l1 = {1, 3, 5, 7, 9};
    MyList<int> l2 = {2, 4, 6, 8, 10};
    std::cout << "First sorted list: ";
    l1.print();
    std::cout << "Second sorted list: ";
    l2.print();
    l1.merge(l2);
    std::cout << "After merge: ";
    l1.print();
    std::cout << "Second list (should be empty): ";
    l2.print();
    std::cout << "Is second list empty? " << std::boolalpha << l2.empty() << '\n';
}

void testSplice() {
    std::cout << "\n=== Test splice() ===\n";
    MyList<int> l1 = {1, 2, 3, 4, 5};
    MyList<int> l2 = {10, 20, 30};
    std::cout << "Original list: ";
    l1.print();
    std::cout << "List to splice: ";
    l2.print();
    auto splicePos = l1.begin();
    ++splicePos;
    ++splicePos;
    l1.splice(splicePos, l2);
    std::cout << "After splice at position 2: ";
    l1.print();
    std::cout << "Second list (should be empty): ";
    l2.print();
}

void testComparisonOperators() {
    std::cout << "\n=== Test comparison operators ===\n";
    MyList<int> l1 = {1, 2, 3};
    MyList<int> l2 = {1, 2, 3};
    MyList<int> l3 = {1, 2, 4};
    MyList<int> l4 = {1, 2};

    std::cout << "l1: ";
    l1.print();
    std::cout << "l2: ";
    l2.print();
    std::cout << "l3: ";
    l3.print();
    std::cout << "l4: ";
    l4.print();

    std::cout << "l1 == l2: " << std::boolalpha << (l1 == l2) << '\n';
    std::cout << "l1 != l3: " << std::boolalpha << (l1 != l3) << '\n';
    std::cout << "l1 < l3: " << std::boolalpha << (l1 < l3) << '\n';
    std::cout << "l3 > l1: " << std::boolalpha << (l3 > l1) << '\n';
    std::cout << "l4 <= l1: " << std::boolalpha << (l4 <= l1) << '\n';
    std::cout << "l1 >= l4: " << std::boolalpha << (l1 >= l4) << '\n';
}

void testSort() {
    std::cout << "\n=== Test sort() with different data ===\n";
    MyList<int> l = {64, 34, 25, 12, 22, 11, 90};
    std::cout << "Before sort: ";
    l.print();
    l.sort(l.begin(), l.end());
    std::cout << "After sort: ";
    l.print();
}

void testMergeWithEmptyList() {
    std::cout << "\n=== Test merge() with empty list ===\n";
    MyList<int> l1 = {1, 3, 5};
    MyList<int> l2;
    std::cout << "Non-empty list: ";
    l1.print();
    std::cout << "Empty list: ";
    l2.print();
    l1.merge(l2);
    std::cout << "After merge: ";
    l1.print();

    MyList<int> l3;
    MyList<int> l4 = {2, 4, 6};
    std::cout << "Empty list: ";
    l3.print();
    std::cout << "Non-empty list: ";
    l4.print();
    l3.merge(l4);
    std::cout << "After merge: ";
    l3.print();
}

int main() {
    testMerge();
    testSplice();
    testComparisonOperators();
    testSort();
    testMergeWithEmptyList();
}
