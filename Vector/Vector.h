//
// Created by Marat on 4.06.25.
//

#pragma once
#include <initializer_list>

template<typename T>
class MyVector {
public:
    MyVector() = default;

    explicit MyVector(size_t size, T value);
    MyVector(std::initializer_list<T> list);

    MyVector(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    ~MyVector();

    void push_back(const T& value);
    void pop_back();
    void insert(size_t pos, T value);
    void erase(size_t pos);
    void clear() noexcept;
    void resize(size_t newSize);
    void reserve(size_t newCapacity);
    void shrink_to_fit() noexcept;
    void swap(MyVector& other) noexcept;

    int& operator[](size_t index) noexcept;
    const int& operator[](size_t index) const noexcept;
    [[nodiscard]] int& at(size_t index);
    [[nodiscard]] const int& at(size_t index) const;
    [[nodiscard]] const int& front() const;
    [[nodiscard]] const int& back() const;

    MyVector& operator = (const MyVector& other);
    MyVector& operator = (MyVector&& other) noexcept;

    bool operator == (const MyVector& other) const;
    bool operator != (const MyVector& other) const;

    T* begin() noexcept;
    T* end() noexcept;
    const T* begin() const noexcept;
    const T* end() const noexcept;

    [[nodiscard]] size_t size() const noexcept;
    [[nodiscard]] size_t capacity() const noexcept;
    [[nodiscard]] bool empty() const noexcept;

    void print() const noexcept;

private:
    T* arr = nullptr;
    size_t vecSize = 0;
    size_t vecCapacity = 0;

    void checkEmpty() const;
    void checkValidIndex(size_t index) const;
    void reallocate(size_t newCapacity);
};

#include "Vector.tpp"
