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

template<typename T, typename Alloc>
MyVector<T, Alloc>::MyVector(size_t size, T value)
        : allocator()
        , arr(std::allocator_traits<Alloc>::allocate(allocator, size * 2))
        , vecSize(size)
        , vecCapacity(size * 2) {

    size_t index = 0;
    try {
        for (; index < vecSize; ++index) {
            std::allocator_traits<Alloc>::construct(allocator, arr + index, value);
        }
    } catch (...) {
        for (size_t oldIndex = 0; oldIndex < index; ++oldIndex) {
            std::allocator_traits<Alloc>::destroy(allocator, arr + oldIndex);
        }
        std::allocator_traits<Alloc>::deallocate(allocator, arr, vecCapacity);
        throw;
    }
}

template<typename T, typename Alloc>
MyVector<T, Alloc>::MyVector(std::initializer_list<T> list)
        : allocator()
        , arr(std::allocator_traits<Alloc>::allocate(allocator, list.size() * 2))
        , vecSize(list.size())
        , vecCapacity(list.size() * 2) {

    size_t index = 0;
    try {
        for (const auto& element : list) {
            std::allocator_traits<Alloc>::construct(allocator, arr + index, element);
            ++index;
        }
    } catch (...) {
        for (size_t oldIndex = 0; oldIndex < index; ++oldIndex) {
            std::allocator_traits<Alloc>::destroy(allocator, arr + oldIndex);
        }
        std::allocator_traits<Alloc>::deallocate(allocator, arr, vecCapacity);
        throw;
    }
}

template<typename T, typename Alloc>
MyVector<T, Alloc>::MyVector(const MyVector& other)
        : allocator(other.allocator)
        , arr(std::allocator_traits<Alloc>::allocate(allocator, other.vecCapacity))
        , vecSize(other.vecSize)
        , vecCapacity(other.vecCapacity) {

    size_t index = 0;
    try {
        for (; index < vecSize; ++index) {
            std::allocator_traits<Alloc>::construct(allocator, arr + index, other.arr[index]);
        }
    } catch (...) {
        for (size_t oldIndex = 0; oldIndex < index; ++oldIndex) {
            std::allocator_traits<Alloc>::destroy(allocator, arr + oldIndex);
        }
        std::allocator_traits<Alloc>::deallocate(allocator, arr, other.vecCapacity);
        throw;
    }
}

template<typename T, typename Alloc>
MyVector<T, Alloc>& MyVector<T, Alloc>::operator = (const MyVector& other) {
    if (this != &other) {
        Alloc newAllocator = std::allocator_traits<Alloc>::propagate_on_container_copy_assignment::value
                             ? other.allocator
                             : allocator;

        T* newArr = std::allocator_traits<Alloc>::allocate(newAllocator, other.vecCapacity);

        size_t index = 0;
        try {
            for (; index < other.vecSize; ++index) {
                std::allocator_traits<Alloc>::construct(newAllocator, newArr + index, other.arr[index]);
            }
        } catch (...) {
            for (size_t oldIndex = 0; oldIndex < index; ++oldIndex) {
                std::allocator_traits<Alloc>::destroy(newAllocator, newArr + oldIndex);
            }
            std::allocator_traits<Alloc>::deallocate(newAllocator, newArr, other.vecCapacity);
            throw;
        }

        for (size_t i = 0; i < vecSize; ++i) {
            std::allocator_traits<Alloc>::destroy(allocator, arr + i);
        }
        std::allocator_traits<Alloc>::deallocate(allocator, arr, vecCapacity);

        allocator = newAllocator;
        arr = newArr;
        vecSize = other.vecSize;
        vecCapacity = other.vecCapacity;
    }
    return *this;
}

template<typename T, typename Alloc>
MyVector<T, Alloc>::MyVector(MyVector&& other) noexcept
        : arr(other.arr)
        , vecSize(other.vecSize)
        , vecCapacity(other.vecCapacity) {
    other.arr = nullptr;
    other.vecSize = 0;
    other.vecCapacity = 0;
}

template<typename T, typename Alloc>
MyVector<T, Alloc>& MyVector<T, Alloc>::operator=(MyVector&& other) noexcept {
    if (this != &other) {
        for (size_t i = 0; i < vecSize; ++i) {
            std::allocator_traits<Alloc>::destroy(allocator, arr + i);
        }

        if (arr) {
            std::allocator_traits<Alloc>::deallocate(allocator, arr, vecCapacity);
        }

        if (std::allocator_traits<Alloc>::propagate_on_container_move_assignment::value) {
            allocator = std::move(other.allocator);
        }

        arr = other.arr;
        vecSize = other.vecSize;
        vecCapacity = other.vecCapacity;

        other.arr = nullptr;
        other.vecSize = 0;
        other.vecCapacity = 0;
    }
    return *this;
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::push_back(const T& value) {
    emplace_back(value);
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::push_back(T&& value) {
    emplace_back(std::move(value));
}

template<typename T, typename Alloc>
template<typename... Args>
void MyVector<T, Alloc>::emplace_back(Args&&... args) {
    if (vecSize == vecCapacity) {
        const size_t newCapacity = (vecCapacity == 0) ? 1 : vecCapacity * 2;
        reallocate(newCapacity);
    }
    std::allocator_traits<Alloc>::construct(
        allocator,
        arr + vecSize,
        std::forward<Args>(args)...
    );
    ++vecSize;
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::pop_back() {
    checkEmpty();
    --vecSize;
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::clear() noexcept {
    vecSize = 0;
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::resize(const size_t newSize) {
    if (newSize > vecSize) {
        if (newSize > vecCapacity) {
            const size_t newCapacity = newSize * 2;
            reallocate(newCapacity);
        }
        for (size_t i = vecSize; i < newSize; ++i) {
            arr[i] = 0;
        }
    }
    vecSize = newSize;
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::reserve(const size_t newCapacity) {
    if (newCapacity <= vecCapacity) {
        return;
    }
    reallocate(newCapacity);
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::shrink_to_fit() noexcept {
    if (vecCapacity > vecSize) {
        reallocate(vecSize);
    }
}

template<typename T, typename Alloc>
T& MyVector<T, Alloc>::at(size_t index) {
    checkValidIndex(index);
    return arr[index];
}

template<typename T, typename Alloc>
const T& MyVector<T, Alloc>::at(size_t index) const {
    checkValidIndex(index);
    return arr[index];
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::insert(size_t pos, T value) {
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

template<typename T, typename Alloc>
void MyVector<T, Alloc>::erase(const size_t pos) {
    if (pos >= vecSize) {
        THROW_OUT_OF_RANGE("Index out of range.");
    }

    for (size_t i = pos; i < vecSize - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    --vecSize;
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::swap(MyVector& other) noexcept {
    T* tempArr = arr;
    size_t tempVecSize = vecSize;
    size_t tempVecCapacity = vecCapacity;

    arr = other.arr;
    vecSize = other.vecSize;
    vecCapacity = other.vecCapacity;

    other.arr = tempArr;
    other.vecSize = tempVecSize;
    other.vecCapacity = tempVecCapacity;
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::merge(iterator beginFirst, iterator endFirst,
                        iterator beginSecond, iterator endSecond,
                        iterator result) {
    while (beginFirst != endFirst && beginSecond != endSecond) {
        if (*beginFirst < *beginSecond) {
            *result = *beginFirst;
            ++beginFirst;
        } else {
            *result = *beginSecond;
            ++beginSecond;
        }
        ++result;
    }

    while (beginFirst != endFirst) {
        *result = *beginFirst;
        ++beginFirst;
        ++result;
    }

    while (beginSecond != endSecond) {
        *result = *beginSecond;
        ++beginSecond;
        ++result;
    }
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::sort(iterator begin, iterator end) {
    auto dist = end.ptr - begin.ptr;
    if (dist <= 1) return;

    iterator mid = (begin + dist / 2);

    sort(begin, mid);
    sort(mid, end);

    std::vector<T> temp(dist);

    merge(begin, mid, mid, end, iterator(temp.data()));
    std::copy(temp.begin(), temp.end(), begin.ptr);
}

template<typename T, typename Alloc>
T& MyVector<T, Alloc>::operator[](size_t index) noexcept {
    return arr[index];
}

template<typename T, typename Alloc>
const T& MyVector<T, Alloc>::operator[](size_t index) const noexcept {
    return arr[index];
}

template<typename T, typename Alloc>
const T& MyVector<T, Alloc>::front() const {
    checkEmpty();
    return arr[0];
}

template<typename T, typename Alloc>
const T& MyVector<T, Alloc>::back() const {
    checkEmpty();
    return arr[vecSize - 1];
}

template<typename T, typename Alloc>
bool MyVector<T, Alloc>::operator == (const MyVector& other) const {
    return vecSize == other.vecSize &&
        std::equal(arr, arr + vecSize, other.arr);
}

template<typename T, typename Alloc>
bool MyVector<T, Alloc>::operator != (const MyVector& other) const {
    return !(*this == other);
}

template<typename T, typename Alloc>
typename MyVector<T, Alloc>::iterator MyVector<T, Alloc>::begin() noexcept {
    return iterator(arr);
}

template<typename T, typename Alloc>
typename MyVector<T, Alloc>::iterator MyVector<T, Alloc>::end() noexcept {
    return iterator(arr + vecSize);
}

template<typename T, typename Alloc>
typename MyVector<T, Alloc>::const_iterator MyVector<T, Alloc>::cbegin() const noexcept {
    return const_iterator(arr);
}

template<typename T, typename Alloc>
typename MyVector<T, Alloc>::const_iterator MyVector<T, Alloc>::cend() const noexcept {
    return const_iterator(arr + vecSize);
}

template<typename T, typename Alloc>
typename MyVector<T, Alloc>::reverse_iterator MyVector<T, Alloc>::rbegin() noexcept {
    return reverse_iterator(arr);
}

template<typename T, typename Alloc>
typename MyVector<T, Alloc>::reverse_iterator MyVector<T, Alloc>::rend() noexcept {
    return reverse_iterator(arr + vecSize);
}

template<typename T, typename Alloc>
typename MyVector<T, Alloc>::const_reverse_iterator MyVector<T, Alloc>::crbegin() const noexcept {
    return const_reverse_iterator(arr);
}

template<typename T, typename Alloc>
typename MyVector<T, Alloc>::const_reverse_iterator MyVector<T, Alloc>::crend() const noexcept {
    return const_reverse_iterator(arr + vecSize);
}

template<typename T, typename Alloc>
size_t MyVector<T, Alloc>::size() const noexcept {
    return vecSize;
}

template<typename T, typename Alloc>
size_t MyVector<T, Alloc>::capacity() const noexcept {
    return vecCapacity;
}

template<typename T, typename Alloc>
bool MyVector<T, Alloc>::empty() const noexcept {
    return vecSize == 0;
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::checkEmpty() const {
    if (empty()) {
        INVALID_ARGUMENT("Vector is empty");
    }
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::checkValidIndex(size_t index) const {
    if (index >= vecSize) {
        THROW_OUT_OF_RANGE("Index out of range.");
    }
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::reallocate(size_t newCapacity) {
    T* newArr = std::allocator_traits<Alloc>::allocate(allocator, newCapacity);

    size_t index = 0;
    try {
        for (; index < vecSize; ++index) {
            std::allocator_traits<Alloc>::construct(allocator, newArr + index,
                                                    std::move_if_noexcept(arr[index]));
        }
    } catch (...) {
        for (size_t oldIndex = 0; oldIndex < index; ++oldIndex) {
            std::allocator_traits<Alloc>::destroy(allocator, newArr + oldIndex);
        }
        std::allocator_traits<Alloc>::deallocate(allocator, newArr, newCapacity);
        throw;
    }

    for (size_t i = 0; i < vecSize; ++i) {
        std::allocator_traits<Alloc>::destroy(allocator, arr + i);
    }
    std::allocator_traits<Alloc>::deallocate(allocator, arr, vecCapacity);

    arr = newArr;
    vecCapacity = newCapacity;
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::print() const noexcept {
    std::cout << "Vector: ";
    for (size_t i = 0; i < vecSize; ++i) {
        std::cout << arr[i] << ' ';
    }
    std:: cout << '\n';
}

template<typename T, typename Alloc>
MyVector<T, Alloc>::~MyVector() {
    for (size_t i = 0; i < vecSize; ++i) {
        std::allocator_traits<Alloc>::destroy(allocator, arr + i);
    }
    std::allocator_traits<Alloc>::deallocate(allocator, arr, vecCapacity);
}
