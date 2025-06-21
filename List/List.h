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
        explicit Node(const T& value);
    };
    Node* head;

    class Iterator {
    private:
        Node* ptr;
        friend class List;
    public:
        explicit Iterator(Node* p);
        T& operator * ();
        Iterator& operator ++ ();
        bool operator != (const Iterator& other);
        bool operator == (const Iterator& other);
    };

public:

    List();
    explicit List(const T& value);
    explicit List(size_t count, const T& value);
    List(std::initializer_list<T> list);
    List(const List<T>& other);
    List(List<T>&& other) noexcept;

    void clear();
    Node* insert(Iterator pos, const T& value);
    Node* erase(Iterator pos);
    void push_back(const T& value);
    void pop_back();
    void push_front(const T& value);
    void pop_front();
    void resize(size_t count);
    void swap(List<T>& other) noexcept;

    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] size_t max_size() const;

    List<T>& operator = (const List<T>& other);
    bool operator == (const List<T>& other);
    bool operator != (const List<T>& other);
    bool operator < (const List<T>& other);
    bool operator > (const List<T>& other);
    bool operator <= (const List<T>& other);
    bool operator >= (const List<T>& other);


    Iterator begin();
    Iterator end();

    void print();

    ~List();
};

#include "List.tpp"


