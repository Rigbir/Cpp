#include "Vector.h"
#include <iostream>

int main() {
    MyVector vec(5, -2);

    vec.print();

    std::cout << "Front: " << vec.front() << '\n';
    std::cout << "Back: " << vec.back() << '\n';
    std::cout << "Size: " << vec.size() << '\n';
    std::cout << "Capacity: " << vec.capacity() << '\n';
    std::cout << "Value of Index: " << vec[2] << '\n';

    vec.push_back(3);
    vec.push_back(8);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(1);
    vec.push_back(9);
    vec.print();
    std::cout << "Size: " << vec.size() << '\t' << "Capacity: " << vec.capacity() << '\n' << '\n';

    vec.clear();
    vec.print();
    std::cout << "Size: " << vec.size() << '\t' << "Capacity: " << vec.capacity() << '\n' << '\n';

    vec.resize(15);
    vec.print();
    std::cout << "Size: " << vec.size() << '\t' << "Capacity: " << vec.capacity() << '\n' << '\n';

    vec.reserve(25);
    vec.push_back(3);
    vec.print();
    std::cout << "Size: " << vec.size() << '\t' << "Capacity: " << vec.capacity() << '\n' << '\n';

    std::cout << "Empty: " << vec.empty() << '\n';

    MyVector vec2 = vec;
    vec2.print();
    std::cout << "Size: " << vec2.size() << '\t' << "Capacity: " << vec2.capacity() << '\n' << '\n';

    MyVector vec3;
    vec3 = vec2;
    vec3.print();
    std::cout << "Size: " << vec3.size() << '\t' << "Capacity: " << vec3.capacity() << '\n' << '\n';

    MyVector vec4;
    vec4 = std::move(vec3);
    vec4.print();
    std::cout << "Size: " << vec4.size() << '\t' << "Capacity: " << vec4.capacity() << '\n' << '\n';
    vec4.shrink_to_fit();
    std::cout << "Size: " << vec4.size() << '\t' << "Capacity: " << vec4.capacity() << '\n' << '\n';

    vec4.insert(4, 9);
    vec4.print();
    std::cout << "Size: " << vec4.size() << '\t' << "Capacity: " << vec4.capacity() << '\n' << '\n';

    vec4.erase(4);
    vec4.print();
    std::cout << "Size: " << vec4.size() << '\t' << "Capacity: " << vec4.capacity() << '\n' << '\n';

    MyVector vec5(3, 1);
    vec5.print();
    std::cout << "Size: " << vec4.size() << '\t' << "Capacity: " << vec4.capacity() << '\n' << '\n';

    vec5.swap(vec4);
    vec5.print();
    std::cout << "Size: " << vec4.size() << '\t' << "Capacity: " << vec4.capacity() << '\n' << '\n';

    vec4.print();
    std::cout << "Size: " << vec4.size() << '\t' << "Capacity: " << vec4.capacity() << '\n' << '\n';

    MyVector vec6 = {1, 2, 3};
    vec6.print();
    std::cout << "Size: " << vec6.size() << '\t' << "Capacity: " << vec6.capacity() << '\n' << '\n';


    MyVector vec7 = {1, 2, 3};
    bool equal = vec6 == vec7;
    bool notEqual = vec6 != vec7;
    std::cout << "Equal: " << equal << '\n';
    std::cout << "Equal: " << notEqual << '\n';
}
