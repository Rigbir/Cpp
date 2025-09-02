//
// Created by Marat on 4.06.25.
//

#pragma once
#include <type_traits>
#include <initializer_list>
#include <iterator>

template<typename T, typename Alloc = std::allocator<T>>
class MyVector {

    template<bool isConst>
    class Iterator {
    public:
        using pointer_type = std::conditional_t<isConst, const T*, T*>;
        using reference_type = std::conditional_t<isConst, const T&, T&>;
        using value_type = T;

    private:
        pointer_type ptr;
        friend class MyVector<T>;

    public:
        explicit Iterator(pointer_type p);
        Iterator(const Iterator& other) = default;
        Iterator& operator = (const Iterator& other) = default;
        reference_type operator * ();
        pointer_type operator -> ();
        Iterator& operator ++ ();
        Iterator operator ++ (int);
        Iterator operator + (size_t n) const;
        Iterator operator - (size_t n) const;
        bool operator == (const Iterator& other);
        bool operator != (const Iterator& other);
        explicit operator Iterator<true>() const;
    };

public:
    using iterator = Iterator<false>;
    using const_iterator = Iterator<true>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    MyVector() = default;

    explicit MyVector(size_t size, T value);
    MyVector(std::initializer_list<T> list);
    MyVector(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector& operator = (const MyVector& other);
    MyVector& operator = (MyVector&& other) noexcept;
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
    void merge(iterator beginFirst, iterator endFirst,
               iterator beginSecond, iterator endSecond,
               iterator result);
    void sort(iterator begin, iterator end);

    T& operator[](size_t index) noexcept;
    const T& operator[](size_t index) const noexcept;
    [[nodiscard]] T& at(size_t index);
    [[nodiscard]] const T& at(size_t index) const;
    [[nodiscard]] const T& front() const;
    [[nodiscard]] const T& back() const;

    bool operator == (const MyVector& other) const;
    bool operator != (const MyVector& other) const;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    [[nodiscard]] size_t size() const noexcept;
    [[nodiscard]] size_t capacity() const noexcept;
    [[nodiscard]] bool empty() const noexcept;

    void print() const noexcept;

private:
    T* arr = nullptr;
    size_t vecSize = 0;
    size_t vecCapacity = 0;
    Alloc allocator;

    void checkEmpty() const;
    void checkValidIndex(size_t index) const;
    void reallocate(size_t newCapacity);
};

#include "Iterator.tpp"
#include "Vector.tpp"
