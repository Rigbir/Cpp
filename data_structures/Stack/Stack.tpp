//
// Created by Marat on 5.11.25.
//

#pragma once
#include <vector>
#include <stdexcept>

template <typename T, typename Alloc>
Stack<T, Alloc>::Stack(const Alloc& alloc)
    : head_(nullptr)
    , alloc_(alloc)
    , size_(0) {}

template <typename T, typename Alloc>
Stack<T, Alloc>::Stack(const Stack& other)
    : head_(nullptr)
    , alloc_(std::allocator_traits<Alloc>::select_on_container_copy_construction(other.alloc_))
    , size_(0)
{
    transfer(other);
}

template <typename T, typename Alloc>
Stack<T, Alloc>::Stack(Stack&& other) noexcept
    : head_(other.head_)
    , alloc_(std::move(other.alloc_))
    , size_(other.size_)
{
    other.head_ = nullptr;
    other.size_ = 0;
}

template <typename T, typename Alloc>
Stack<T, Alloc>& Stack<T, Alloc>::operator = (const Stack& other) {
    if (this != &other) {
        if constexpr (std::allocator_traits<Alloc>::propagate_on_container_copy_assignment::value) {
            alloc_ = other.alloc_;
        }

        clear();
        transfer(other);
    }
    return *this;
}

template <typename T, typename Alloc>
Stack<T, Alloc>& Stack<T, Alloc>::operator = (Stack&& other) noexcept {
    if (this != &other) {
        if constexpr (std::allocator_traits<Alloc>::propagate_on_container_move_assignment::value) {
            alloc_ = std::move(other.alloc_);
        }

        clear();
        head_ = other.head_;
        size_ = other.size_;

        other.head_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T, typename Alloc>
void Stack<T, Alloc>::push(const T& value) {
    Node_Alloc node_alloc(alloc_);

    Node* new_node = node_alloc.allocate(1);
    std::allocator_traits<Node_Alloc>::construct(node_alloc, new_node, value, head_);
    head_ = new_node;
    ++size_;
}

template <typename T, typename Alloc>
void Stack<T, Alloc>::push(T&& value) {
    Node_Alloc node_alloc(alloc_);

    Node* new_node = node_alloc.allocate(1);
    std::allocator_traits<Node_Alloc>::construct(node_alloc, new_node, std::move(value), head_);
    head_ = new_node;
    ++size_;
}

template <typename T, typename Alloc>
template <typename... Args>
void Stack<T, Alloc>::emplace(Args&&... args) {
    Node_Alloc node_alloc(alloc_);
    
    Node* new_node = node_alloc.allocate(1);
    std::allocator_traits<Node_Alloc>::construct(node_alloc, &new_node->value, std::forward<Args>(args)...);
    new_node->next = head_;
    head_ = new_node;
    ++size_;
}

template <typename T, typename Alloc>
void Stack<T, Alloc>::pop() {
    if (!head_) {
        throw std::runtime_error("Stack is empty");
    }

    Node_Alloc node_alloc(alloc_);

    Node* old = head_;
    head_ = head_->next;

    std::allocator_traits<Node_Alloc>::destroy(node_alloc, old);
    node_alloc.deallocate(old, 1);
    --size_;
}

template <typename T, typename Alloc>
T& Stack<T, Alloc>::top() {
    if (!head_) {
        throw std::runtime_error("Stack is empty");
    }
    return head_->value;
}

template <typename T, typename Alloc>
const T& Stack<T, Alloc>::top() const {
    if (!head_) {
        throw std::runtime_error("Stack is empty");
    }
    return head_->value;
}

template <typename T, typename Alloc>
void Stack<T, Alloc>::swap(Stack& other) noexcept {
    std::swap(head_, other.head_);
    if constexpr (std::allocator_traits<Alloc>::propagate_on_container_swap::value) {
        std::swap(alloc_, other.alloc_);
    } 
    std::swap(size_, other.size_);
}

template <typename T, typename Alloc>
typename Stack<T, Alloc>::allocator_type Stack<T, Alloc>::get_allocator() const noexcept {
    return alloc_;
}

template <typename T, typename Alloc>
bool Stack<T, Alloc>::empty() const noexcept {
    return head_ == nullptr;
}

template <typename T, typename Alloc>
size_t Stack<T, Alloc>::size() const noexcept {
    return size_;
}

template <typename T, typename Alloc>
void Stack<T, Alloc>::clear() {
    while (head_) {
        pop();
    }
}

template <typename T, typename Alloc>
void Stack<T, Alloc>::transfer(const Stack& other) {
    if (!other.head_) {
        return;
    }

    Node_Alloc node_alloc(alloc_);
    std::vector<const Node*> nodes;
    nodes.reserve(other.size_);

    for (const Node* n = other.head_; n; n = n->next) {
        nodes.push_back(n);
    }

    Node* prev = nullptr;
    for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
        Node* new_node = node_alloc.allocate(1);
        std::allocator_traits<Node_Alloc>::construct(node_alloc, new_node, (*it)->value, prev);
        prev = new_node;
    }
    head_ = prev;
    size_ = other.size_;
}

template <typename T, typename Alloc>
Stack<T, Alloc>::~Stack() {
    clear();
}