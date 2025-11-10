//
// Created by Marat on 7.11.25.
//

#pragma once

#include <memory>

template <typename T, typename Alloc = std::allocator<T>>
class Queue {
public:
    using allocator_type = Alloc;

    explicit Queue(const Alloc& alloc = Alloc());
    Queue(const Queue& other);
    Queue(Queue&& other) noexcept;
    Queue& operator = (const Queue& other);
    Queue& operator = (Queue&& other) noexcept;

    void push(const T& value);
    void push(T&& value);
    void pop();

    template <typename... Args>
    void emplace(Args&&... args);

    T& top();
    const T& top() const;

    void swap(Queue& other) noexcept;
    allocator_type get_allocator() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    ~Queue();

private:
    struct Node {
        T value;
        Node* next;
        Node(const T& value, Node* next): value(value), next(next) {}
        Node(T&& value, Node* next): value(std::move(value)), next(next) {}
    };

    struct Data {
        Node* head;
        Node* tail;
    };

    Data q_;
    size_t size_;
    Alloc alloc_;

    void clear();
    void transfer(const Queue& other);

    using Node_Alloc = typename std::allocator_traits<Alloc>::template rebind_alloc<Node>;
};

#include "Queue.tpp"