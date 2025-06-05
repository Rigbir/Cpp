//
// Created by Marat on 5.06.25.
//

#pragma once
#include <initializer_list>

class MyString {
public:

    MyString(size_t n, char c);
    MyString(std::initializer_list<char> list);

    [[nodiscard]] size_t size() const noexcept;
    [[nodiscard]] size_t capacity() const noexcept;

    void print();

private:
    char* arr;
    size_t StrSize_;
    size_t StrCapacity_;
};