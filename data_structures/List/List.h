//
// Created by Marat on 14.06.25.
//

#pragma once

#include <iostream>
#include <initializer_list>

template<typename T>
class MyList {
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
        explicit Iterator(Node* p);

        friend class MyList;
    public:
        T& operator * ();
        T* operator -> ();
        Iterator& operator ++ ();
        Iterator operator ++ (int);
        bool operator != (const Iterator& other);
        bool operator == (const Iterator& other);
    };

public:

    MyList();
    explicit MyList(const T& value);
    explicit MyList(size_t count, const T& value);
    MyList(std::initializer_list<T> MyList);
    MyList(const MyList<T>& other);
    MyList(MyList<T>&& other) noexcept;

    void clear();
    Node* insert(Iterator pos, const T& value);
    Node* erase(Iterator pos);
    void push_back(const T& value);
    void pop_back();
    void push_front(const T& value);
    void pop_front();
    void resize(size_t count);
    void swap(MyList<T>& other) noexcept;

    void merge(MyList<T>& other);
    void splice(Iterator pos, MyList<T>& other);
    void remove(const T& value);
    void reverse();
    void unique();

    void mergeForSort(Iterator beginFirst, Iterator endFirst,
                      Iterator beginSecond, Iterator endSecond,
                      Iterator result);
    void sort(Iterator begin, Iterator end);

    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] size_t max_size() const;

    MyList<T>& operator = (const MyList<T>& other);
    bool operator == (const MyList<T>& other) const;
    bool operator != (const MyList<T>& other) const;
    bool operator < (const MyList<T>& other) const;
    bool operator > (const MyList<T>& other) const;
    bool operator <= (const MyList<T>& other) const;
    bool operator >= (const MyList<T>& other) const;

    Iterator begin();
    Iterator cbegin() const;
    Iterator end();
    Iterator cend() const;

    void print();

    ~MyList();
};

#include "List.tpp"