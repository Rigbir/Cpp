#include "Vector.h"
#include <algorithm>
#include <complex>
#include <stdexcept>
#include <string>
#include <iostream>

#define THROW_OUT_OF_RANGE(msg) throw std::out_of_range(std::string(msg) + \
    " [File: " + __FILE__ + ", Line: " + std::to_string(__LINE__) + "]")
#define INVALID_ARGUMENT(msg) throw std::invalid_argument(std::string(msg) + \
" [File: " + __FILE__ + ", Line: " + std::to_string(__LINE__) + "]")

MyVector::MyVector(size_t size, int value)
        : arr(new int[size * 2])
        , vecSize(size)
        , vecCapacity(size * 2) {
   std::fill(arr, arr + size, value);
}

MyVector::MyVector(std::initializer_list<int> list)
        : arr(new int[list.size() * 2])
        , vecSize(list.size())
        , vecCapacity(list.size() * 2) {
    std::copy(list.begin(), list.end(), arr);
}

MyVector::MyVector(const MyVector &other)
        : arr(new int[other.vecCapacity])
        , vecSize(other.vecSize)
        , vecCapacity(other.vecCapacity) {
    std::copy(other.arr, other.arr + other.vecSize, arr);
}

MyVector& MyVector::operator = (const MyVector &other) {
    if (this != &other) {
        int* newArr = new int[other.vecCapacity];
        std::copy(other.arr, other.arr + other.vecSize, newArr);

        delete[] arr;
        arr = newArr;
        vecSize = other.vecSize;
        vecCapacity = other.vecCapacity;
    }
    return *this;
}

MyVector::MyVector(MyVector&& other) noexcept
        : arr(other.arr)
        , vecSize(other.vecSize)
        , vecCapacity(other.vecCapacity) {
    other.arr = nullptr;
    other.vecSize = 0;
    other.vecCapacity = 0;
}

MyVector& MyVector::operator=(MyVector&& other) noexcept {
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

void MyVector::push_back(int value) {
    if (vecSize == vecCapacity) {
        size_t newCapacity = (vecCapacity == 0) ? 1 : vecCapacity * 2;
        reallocate(newCapacity);
    }
    arr[vecSize++] = value;
}

void MyVector::pop_back() {
    checkEmpty();
    --vecSize;
}

void MyVector::clear() {
    vecSize = 0;
}

void MyVector::resize(size_t newSize) {
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

void MyVector::reserve(size_t newCapacity) {
    if (newCapacity < vecCapacity) {
        return;
    }
    reallocate(newCapacity);
}

void MyVector::shrink_to_fit() {
    if (vecCapacity > vecSize) {
        vecCapacity = vecSize;
    }
}

int& MyVector::at(size_t index) {
    checkValidIndex(index);
    return arr[index];
}

const int& MyVector::at(size_t index) const {
    checkValidIndex(index);
    return arr[index];
}

void MyVector::insert(size_t pos, int value) {
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

void MyVector::erase(size_t pos) {
    if (pos >= vecSize) {
        THROW_OUT_OF_RANGE("Index out of range.");
    }
    for (size_t i = pos; i < vecSize - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    --vecSize;
}

void MyVector::swap(MyVector& other) {
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

int& MyVector::operator[](size_t index) {
    return arr[index];
}

const int& MyVector::operator[](size_t index) const {
    return arr[index];
}

const int& MyVector::front() const {
    checkEmpty();
    return arr[0];
}

const int& MyVector::back() const {
    checkEmpty();
    return arr[vecSize - 1];
}

size_t MyVector::size() const {
    if (empty()) return 0;
    return vecSize;
}

size_t MyVector::capacity() const {
    if (empty()) return 0;
    return vecCapacity;
}

bool MyVector::empty() const {
    return vecSize == 0;
}

void MyVector::checkEmpty() const {
    if (empty()) {
        INVALID_ARGUMENT("Vector is empty");
    }
}

void MyVector::checkValidIndex(size_t index) const {
    if (index >= vecSize) {
        THROW_OUT_OF_RANGE("Index out of range.");
    }
}

void MyVector::reallocate(size_t newCapacity) {
    int* newArr = new int[newCapacity];

    for (size_t i = 0; i < vecSize; ++i) {
        newArr[i] = arr[i];
    }

    delete[] arr;
    arr = newArr;
    vecCapacity = newCapacity;
}

void MyVector::print() const {
    std::cout << "Vector: ";
    for (size_t i = 0; i < vecSize; ++i) {
        std::cout << arr[i] << ' ';
    }
    std:: cout << '\n';
}

MyVector::~MyVector() {
    delete[] arr;
}
