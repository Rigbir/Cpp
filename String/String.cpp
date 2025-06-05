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

size_t MyString::size() const noexcept {
    return StrSize_;
}

size_t MyString::capacity() const noexcept {
    return StrCapacity_;
}


void MyString::print() {
    std::cout << std::string_view(arr, StrSize_) << '\n';
}

