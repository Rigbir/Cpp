//
// Created by Marat on 4.06.25.
//

#pragma once

#include <algorithm>
#include <stdexcept>
#include <string>
#include <iostream>

#define THROW_OUT_OF_RANGE(msg) throw std::out_of_range(std::string(msg) + \
    " [File: " + __FILE__ + ", Line: " + std::to_string(__LINE__) + "]")
#define INVALID_ARGUMENT(msg) throw std::invalid_argument(std::string(msg) + \
" [File: " + __FILE__ + ", Line: " + std::to_string(__LINE__) + "]")

template<typename T>
MyVector<T>::MyVector(size_t size, T value)
        : arr(new T[size * 2])
        , vecSize(size)
        , vecCapacity(size * 2) {
   std::ranges::fill(arr, arr + size, value);
}

template<typename T>
MyVector<T>::MyVector(std::initializer_list<T> list)
        : arr(new T[list.size() * 2])
        , vecSize(list.size())
        , vecCapacity(list.size() * 2) {
    std::ranges::copy(list.begin(), list.end(), arr);
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other)
        : arr(new T[other.vecCapacity])
        , vecSize(other.vecSize)
        , vecCapacity(other.vecCapacity) {
    std::ranges::copy(other.arr, other.arr + other.vecSize, arr);
}

template<typename T>
MyVector<T>& MyVector<T>::operator = (const MyVector& other) {
    if (this != &other) {
        int* newArr = new T[other.vecCapacity];
        std::ranges::copy(other.arr, other.arr + other.vecSize, newArr);

        delete[] arr;
        arr = newArr;
        vecSize = other.vecSize;
        vecCapacity = other.vecCapacity;
    }
    return *this;
}

template<typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept
        : arr(other.arr)
        , vecSize(other.vecSize)
        , vecCapacity(other.vecCapacity) {
    other.arr = nullptr;
    other.vecSize = 0;
    other.vecCapacity = 0;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    if (this != &other) {
        delete[] arr;

        arr = other.arr;
        vecSize = other.vecSize;
        vecCapacity = other.vecCapacity;

        other.arr = nullptr;
        other.vecSize = 0;
        other.vecCapacity = 0;
    }
    return *this;
}

template<typename T>
void MyVector<T>::push_back(T value) {
    if (vecSize == vecCapacity) {
        size_t newCapacity = (vecCapacity == 0) ? 1 : vecCapacity * 2;
        reallocate(newCapacity);
    }
    arr[vecSize++] = value;
}

template<typename T>
void MyVector<T>::pop_back() {
    checkEmpty();
    --vecSize;
}

template<typename T>
void MyVector<T>::clear() noexcept {
    vecSize = 0;
}

template<typename T>
void MyVector<T>::resize(size_t newSize) {
    if (newSize > vecSize) {
        if (newSize > vecCapacity) {
            size_t newCapacity = newSize * 2;
            reallocate(newCapacity);
        }
        for (size_t i = vecSize; i < newSize; ++i) {
            arr[i] = 0;
        }
    }
    vecSize = newSize;
}

template<typename T>
void MyVector<T>::reserve(size_t newCapacity) {
    if (newCapacity < vecCapacity) {
        return;
    }
    reallocate(newCapacity);
}

template<typename T>
void MyVector<T>::shrink_to_fit() noexcept {
    if (vecCapacity > vecSize) {
        reallocate(vecSize);
    }
}

template<typename T>
int& MyVector<T>::at(size_t index) {
    checkValidIndex(index);
    return arr[index];
}

template<typename T>
const int& MyVector<T>::at(size_t index) const {
    checkValidIndex(index);
    return arr[index];
}

template<typename T>
void MyVector<T>::insert(size_t pos, T value) {
    if (pos > vecSize) {
        THROW_OUT_OF_RANGE("Index out of range.");
    }
    if (vecSize >= vecCapacity) {
        size_t newCapacity = vecCapacity == 0 ? 1 : vecCapacity * 2;
        reallocate(newCapacity);
    }
    for (size_t i = vecSize; i > pos; --i) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = value;
    ++vecSize;
}

template<typename T>
void MyVector<T>::erase(size_t pos) {
    if (pos >= vecSize) {
        THROW_OUT_OF_RANGE("Index out of range.");
    }
    for (size_t i = pos; i < vecSize - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    --vecSize;
}

template<typename T>
void MyVector<T>::swap(MyVector& other) noexcept {
    int* tempArr = arr;
    size_t tempVecSize = vecSize;
    size_t tempVecCapacity = vecCapacity;

    arr = other.arr;
    vecSize = other.vecSize;
    vecCapacity = other.vecCapacity;

    other.arr = tempArr;
    other.vecSize = tempVecSize;
    other.vecCapacity = tempVecCapacity;
}

template<typename T>
int& MyVector<T>::operator[](size_t index) noexcept {
    return arr[index];
}

template<typename T>
const int& MyVector<T>::operator[](size_t index) const noexcept {
    return arr[index];
}

template<typename T>
const int& MyVector<T>::front() const {
    checkEmpty();
    return arr[0];
}

template<typename T>
const int& MyVector<T>::back() const {
    checkEmpty();
    return arr[vecSize - 1];
}

template<typename T>
bool MyVector<T>::operator == (const MyVector& other) const {
    return vecSize == other.vecSize &&
        std::equal(arr, arr + vecSize, other.arr);
}

template<typename T>
bool MyVector<T>::operator != (const MyVector& other) const {
    return !(*this == other);
}

template<typename T>
T* MyVector<T>::begin() noexcept {
    return arr;
}

template<typename T>
T* MyVector<T>::end() noexcept {
    return arr + vecSize;
}

template<typename T>
const T* MyVector<T>::begin() const noexcept {
    return arr;
}

template<typename T>
const T* MyVector<T>::end() const noexcept {
    return arr + vecSize;
}

template<typename T>
size_t MyVector<T>::size() const noexcept {
    return vecSize;
}

template<typename T>
size_t MyVector<T>::capacity() const noexcept {
    return vecCapacity;
}

template<typename T>
bool MyVector<T>::empty() const noexcept {
    return vecSize == 0;
}

template<typename T>
void MyVector<T>::checkEmpty() const {
    if (empty()) {
        INVALID_ARGUMENT("Vector is empty");
    }
}

template<typename T>
void MyVector<T>::checkValidIndex(size_t index) const {
    if (index >= vecSize) {
        THROW_OUT_OF_RANGE("Index out of range.");
    }
}

template<typename T>
void MyVector<T>::reallocate(size_t newCapacity) {
    int* newArr = new int[newCapacity];

    for (size_t i = 0; i < vecSize; ++i) {
        newArr[i] = arr[i];
    }

    delete[] arr;
    arr = newArr;
    vecCapacity = newCapacity;
}

template<typename T>
void MyVector<T>::print() const noexcept {
    std::cout << "Vector: ";
    for (size_t i = 0; i < vecSize; ++i) {
        std::cout << arr[i] << ' ';
    }
    std:: cout << '\n';
}

template<typename T>
MyVector<T>::~MyVector() {
    delete[] arr;
}
