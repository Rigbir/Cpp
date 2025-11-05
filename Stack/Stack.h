//
// Created by Marat on 5.11.25.
//

#pragma once
#include <memory>

template <typename T, typename Alloc = std::allocator<T>>
class Stack {
public:
    using allocator_type = Alloc;
    
    explicit Stack(const Alloc& alloc = Alloc());
    
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    Stack& operator = (const Stack& other);
    Stack& operator = (Stack&& other) noexcept;

    void push(const T& value);
    void push(T&& value);
    void pop();

    template <typename... Args>
    void emplace(Args&&... args);

    T& top();
    const T& top() const;

    void swap(Stack& other) noexcept;
    allocator_type get_allocator() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    ~Stack();

private:
    struct Node {
        T value;
        Node* next;
        Node(const T& value, Node* next): value(value), next(next) {}
    };

    Node* head_;
    Alloc alloc_;
    size_t size_;

    void clear();
    void transfer(const Stack& other);

    using Node_Alloc = typename std::allocator_traits<Alloc>::template rebind_alloc<Node>;
};

#include "Stack.tpp"