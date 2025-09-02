//
// Created by Marat on 4.06.25.
//

#pragma once

template <typename T, typename Alloc>
template<bool isConst>
MyVector<T, Alloc>::Iterator<isConst>::Iterator(pointer_type p) : ptr(p) {}

template <typename T, typename Alloc>
template<bool isConst>
typename MyVector<T, Alloc>::template Iterator<isConst>::reference_type
MyVector<T, Alloc>::Iterator<isConst>::operator * () {
    return *ptr;
}

template <typename T, typename Alloc>
template<bool isConst>
typename MyVector<T, Alloc>::template Iterator<isConst>::pointer_type
MyVector<T, Alloc>::Iterator<isConst>::operator -> () {
    return ptr;
}

template <typename T, typename Alloc>
template<bool isConst>
typename MyVector<T, Alloc>::template Iterator<isConst>&
MyVector<T, Alloc>::Iterator<isConst>::operator ++ () {
    ++ptr;
    return *this;
}

template <typename T, typename Alloc>
template<bool isConst>
typename MyVector<T, Alloc>::template Iterator<isConst>
MyVector<T, Alloc>::Iterator<isConst>::operator ++ (int) {
    Iterator copy = *this;
    ++ptr;
    return copy;
}

template <typename T, typename Alloc>
template<bool isConst>
typename MyVector<T, Alloc>::template Iterator<isConst>
MyVector<T, Alloc>::Iterator<isConst>::operator + (size_t n) const {
    return Iterator(ptr + n);
}

template <typename T, typename Alloc>
template<bool isConst>
typename MyVector<T, Alloc>::template Iterator<isConst>
MyVector<T, Alloc>::Iterator<isConst>::operator - (size_t n) const {
    return Iterator(ptr - n);
}

template<typename T, typename Alloc>
template<bool isConst>
bool MyVector<T, Alloc>::Iterator<isConst>::operator == (const Iterator<isConst>& other) {
    return ptr == other.ptr;
}

template<typename T, typename Alloc>
template<bool isConst>
bool MyVector<T, Alloc>::Iterator<isConst>::operator != (const Iterator<isConst>& other) {
    return ptr != other.ptr;
}

template<typename T, typename Alloc>
template<bool isConst>
MyVector<T, Alloc>::Iterator<isConst>::operator MyVector<T, Alloc>::Iterator<true>() const {
    return MyVector<T, Alloc>::Iterator<true>(ptr);
}
