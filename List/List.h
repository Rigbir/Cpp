//
// Created by Marat on 14.06.25.
//

#pragma once

#include <iostream>
#include <initializer_list>

template<typename T>
class List {
public:

    List();
    explicit List(const T& value);
    explicit List(size_t count, const T& value);
    List(std::initializer_list<T> list);
    List(const List<T>& other);
    List(List<T>&& other);

    void clear();
    List<T>* insert(List<T>* pos, const T& value);
    List<T>* erase(List<T>* pos);
    void push_back(const T& value);
    void pop_back();
    void push_front(const T& value);
    void pop_front();
    void resize(size_t count);
    void swap(List<T>& other);





    bool empty() const;
    void size() const;
    void max_size() const;

    List<T>* begin();

    template <typename U>
    friend std::ostream& operator << (std::ostream& os, List<U>* it);

    void print();

    ~List();

private:
    T _value;
    List<T>* next;
    List<T>* prev;
};

#include "List.tpp"


