//
// Created by Marat on 5.06.25.
//

#include "String.h"
#include <iostream>
#include <algorithm>
#include <string_view>

MyString::MyString(size_t n, char c)
        : arr(new char[n + 1])
        , StrSize_(n)
        , StrCapacity_(n + 1) {
    std::ranges::fill(arr, arr + StrSize_, c);
    arr[StrSize_] = '\0';
}

MyString::MyString(std::initializer_list<char> list)
        : arr(new char[list.size() + 1])
        , StrSize_(list.size())
        , StrCapacity_(list.size() + 1) {
    std::ranges::copy(list.begin(), list.end(), arr);
    arr[StrSize_] = '\0';
}

MyString::MyString(const MyString& other)
        : arr(new char[other.StrCapacity_])
        , StrSize_(other.StrSize_)
        , StrCapacity_(other.StrCapacity_) {
    std::ranges::copy(other.arr, other.arr + other.StrSize_, arr);
}

size_t MyString::size() const noexcept {
    return StrSize_;
}

size_t MyString::capacity() const noexcept {
    return StrCapacity_;
}

MyString::~MyString() {
    delete[] arr;
}

void MyString::print() {
    std::cout << std::string_view(arr, StrSize_) << '\n';
}

