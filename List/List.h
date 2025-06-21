//
// Created by Marat on 14.06.25.
//

#pragma once

#include <iostream>
#include <initializer_list>

template<typename T>
class List {
public:
    struct Node {
        T _value;
        Node* next;
        Node* prev;
        Node(const T& value);
    };

    Node* head;

public:

    List();
    explicit List(const T& value);
    explicit List(size_t count, const T& value);
    List(std::initializer_list<T> list);
    List(const List<T>& other);
    List(List<T>&& other) noexcept;

    void clear();
    Node* insert(Node* pos, const T& value);
    Node* erase(List<T>* pos);
    void push_back(const T& value);
    void pop_back();
    void push_front(const T& value);
    void pop_front();
    void resize(size_t count);
    void swap(List<T>& other) noexcept;

    bool empty() const;
    size_t size() const;
    size_t max_size() const;

    class Iterator {
    private:
        Node* ptr;

    public:
        Iterator(Node* p);
        T& operator * ();
        Iterator& operator ++ ();
        bool operator != (const Iterator& other);
    };

    Iterator begin();
    Iterator end();

    template <typename U>
    friend std::ostream& operator << (std::ostream& os, List<U>* it);

    void print();

    ~List();
};

#include "List.tpp"


