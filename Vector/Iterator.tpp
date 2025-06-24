//
// Created by Marat on 4.06.25.
//

#pragma once

template <typename T>
template<bool isConst>
MyVector<T>::Iterator<isConst>::Iterator(T* p) : ptr(p) {}

template <typename T>
template<bool isConst>
typename MyVector<T>::template Iterator<isConst>::reference_type
MyVector<T>::Iterator<isConst>::operator * () {
    return *ptr;
}

template <typename T>
template<bool isConst>
typename MyVector<T>::template Iterator<isConst>::pointer_type
MyVector<T>::Iterator<isConst>::operator -> () {
    return ptr;
}

template <typename T>
template<bool isConst>
typename MyVector<T>::template Iterator<isConst>&
MyVector<T>::Iterator<isConst>::operator ++ () {
    ++ptr;
    return *this;
}

template <typename T>
template<bool isConst>
typename MyVector<T>::template Iterator<isConst>
MyVector<T>::Iterator<isConst>::operator ++ (int) {
    Iterator copy = *this;
    ++ptr;
    return copy;
}

template<typename T>
template<bool isConst>
bool MyVector<T>::Iterator<isConst>::operator == (const Iterator<isConst>& other) {
    return ptr == other.ptr;
}

template<typename T>
template<bool isConst>
bool MyVector<T>::Iterator<isConst>::operator != (const Iterator<isConst>& other) {
    return ptr != other.ptr;
}

template<typename T>
template<bool isConst>
MyVector<T>::Iterator<isConst>::operator MyVector<T>::Iterator<true>() const {
    return MyVector<T>::Iterator<true>(ptr);
}
