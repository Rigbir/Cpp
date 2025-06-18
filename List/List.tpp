//
// Created by Marat on 14.06.25.
//

#pragma once

template<typename T>
List<T>::List()
        : _value()
        , next(nullptr)
        , prev(nullptr) {}

template <typename T>
List<T>::List(const T& value)
        : _value(value)
        , next(nullptr)
        , prev(nullptr) {}

template <typename T>
List<T>::List(size_t count, const T& value)
        : _value(value)
        , next(nullptr)
        , prev(nullptr) {
    List<T>* current = this;

    for (size_t i = 1; i < count; ++i) {
        List<T>* newNode = new List<T>(value);

        newNode->next = nullptr;
        newNode->prev = current;
        current->next = newNode;
        current = newNode;
    }
}

template <typename T>
List<T>::List(std::initializer_list<T> list)
        : _value(*list.begin())
        , next(nullptr)
        , prev(nullptr) {
    List<T>* current = this;
    auto it = list.begin();
    ++it;

    for (; it != list.end(); ++it) {
        List<T>* newNode = new List<T>(*it);
        newNode->next = nullptr;
        newNode->prev = current;
        current->next = newNode;

        current = newNode;
    }
}

template <typename T>
List<T>::List(const List<T>& other)
        : _value(other._value)
        , next(nullptr)
        , prev(nullptr) {
    const List<T>* otherCurrent = other.next;
    List<T>* current = this;

    while (otherCurrent->next != nullptr) {
        List<T>* newNode = new List<T>(otherCurrent->_value);

        newNode->prev = current;
        current->next = newNode;
        current = newNode;

        otherCurrent = otherCurrent->next;
    }
}

template <typename T>
List<T>::List(List<T>&& other)
        : _value(std::move(other._value))
        , next(other.next)
        , prev(other.prev) {
    other.next = nullptr;
    other.prev = nullptr;
}

template <typename T>
void List<T>::append(const T& value) {
    List<T>* current = this;

    while (current->next != nullptr) {
        current = current->next;
    }

    List<T>* newNode = new List<T>(value);

    newNode->next = nullptr;
    newNode->prev = current;
    current->next = newNode;
}

template <typename T>
List<T>* List<T>::insert(List<T>* pos, const T& value) {
    List<T>* newNode = new List<T>(value);

    newNode->next = pos;
    newNode->prev = pos->prev;

    if (pos->prev) {
        pos->prev->next = newNode;
    }
    pos->prev = newNode;

    return (newNode->prev == nullptr) ? newNode : pos;
}

template <typename T>
List<T>* List<T>::begin() {
    return this;
}

template <typename U>
std::ostream& operator << (std::ostream& os, List<U>* it) {
    return os << it->_value;
}

template <typename T>
void List<T>::print() {
    List<T>* current = this;
    while (current != nullptr) {
        std::cout << current->_value << ' ';
        current = current->next;
    }
    std::cout << '\n';
}

template <typename T>
List<T>::~List() {
    while (this->prev != nullptr) {
        const List<T>* temp = this->prev;
        this->prev = this->prev->prev;
        delete temp;
    }
}