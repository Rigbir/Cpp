//
// Created by Marat on 7.11.25.
//

#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T, typename Alloc>
Queue<T, Alloc>::Queue(const Alloc& alloc)
    : q_{nullptr, nullptr}
    , size_(0)
    , alloc_(alloc) {}

template <typename T, typename Alloc>
Queue<T, Alloc>::Queue(const Queue& other)
    : q_{nullptr, nullptr}
    , size_(0)
    , alloc_(std::allocator_traits<Alloc>::select_on_container_copy_construction(other.alloc_))
{
    transfer(other);
}

template<typename T, typename Alloc>
Queue<T, Alloc>::Queue(Queue&& other) noexcept
    : q_{other.q_.head, other.q_.tail}
    , size_(other.size_)
    , alloc_(std::move(other.alloc_))
{
    other.q_.head = other.q_.tail = nullptr;
    other.size_ = 0;
}

template<typename T, typename Alloc>
Queue<T, Alloc>& Queue<T, Alloc>::operator = (const Queue& other) {
    if (this != &other) {
        if constexpr (std::allocator_traits<Alloc>::propagate_on_container_copy_assignment::value) {
            alloc_ = other.alloc_;
        }

        clear();
        transfer(other);
    }
    return *this;
}

template<typename T, typename Alloc>
Queue<T, Alloc>& Queue<T, Alloc>::operator = (Queue&& other) noexcept {
    if (this != &other) {
        clear();

        if constexpr (std::allocator_traits<Alloc>::propagate_on_container_move_assignment::value) {
            alloc_ = std::move(other.alloc_);
        }

        q_.head = other.q_.head;
        q_.tail = other.q_.tail;
        size_ = other.size_;

        other.q_.head = other.q_.tail = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T, typename Alloc>
void Queue<T, Alloc>::push(const T& value) {
    Node_Alloc node_alloc(alloc_);
    Node* new_node = node_alloc.allocate(1);

    std::allocator_traits<Node_Alloc>::construct(node_alloc, new_node, value, nullptr);
    if (!q_.head) {
        q_.head = q_.tail = new_node;
    } else {
        q_.tail->next = new_node;
        q_.tail = new_node;
    }

    ++size_;
}

template <typename T, typename Alloc>
void Queue<T, Alloc>::push(T&& value) {
    Node_Alloc node_alloc(alloc_);
    Node* new_node = node_alloc.allocate(1);

    std::allocator_traits<Node_Alloc>::construct(node_alloc, new_node, std::move(value), nullptr);
    if (!q_.head) {
        q_.head = q_.tail = new_node;
    } else {
        q_.tail->next = new_node;
        q_.tail = new_node;
    }

    ++size_;
}

template <typename T, typename Alloc>
void Queue<T, Alloc>::pop() {
    if (!q_.head) {
        throw std::runtime_error("Queue is empty");
    }

    Node_Alloc node_alloc(alloc_);

    Node* old = q_.head;
    q_.head = q_.head->next;

    std::allocator_traits<Node_Alloc>::destroy(node_alloc, old);
    node_alloc.deallocate(old, 1);

    if (!q_.head) {
        q_.tail = nullptr;
    }

    --size_;
}

template <typename T, typename Alloc>
template <typename... Args>
void Queue<T, Alloc>::emplace(Args&&... args) {
    Node_Alloc node_alloc(alloc_);

    Node* new_node = node_alloc.allocate(1);
    std::allocator_traits<Node_Alloc>::construct(node_alloc, &new_node->value, std::forward<Args>(args)...);
    new_node->next = nullptr;

    if (!q_.head) {
        q_.head = q_.tail = new_node;
    } else {
        q_.tail->next = new_node;
        q_.tail = new_node;
    }

    ++size_;
}

template<typename T, typename Alloc>
T& Queue<T, Alloc>::top() {
    if (!q_.head) {
        throw std::runtime_error("Queue is empty");
    }
    return q_.head->value;
}

template<typename T, typename Alloc>
const T& Queue<T, Alloc>::top() const {
    if (!q_.head) {
        throw std::runtime_error("Queue is empty");
    }
    return q_.head->value;
}

template <typename T, typename Alloc>
void Queue<T, Alloc>::swap(Queue& other) noexcept {
    std::swap(q_, other.q_);
    std::swap(size_, other.size_);
    if constexpr (std::allocator_traits<Alloc>::propagate_on_container_swap::value) {
        std::swap(alloc_, other.alloc_);
    }
}

template<typename T, typename Alloc>
typename Queue<T, Alloc>::allocator_type Queue<T, Alloc>::get_allocator() const noexcept {
    return alloc_;
}

template<typename T, typename Alloc>
bool Queue<T, Alloc>::empty() const noexcept {
    return q_.head == nullptr;
}

template<typename T, typename Alloc>
size_t Queue<T, Alloc>::size() const noexcept {
    return size_;
}

template <typename T, typename Alloc>
void Queue<T, Alloc>::clear() {
    while (q_.head) {
        pop();
    }
}

template<typename T, typename Alloc>
void Queue<T, Alloc>::transfer(const Queue& other) {
    if (!other.q_.head) {
        return;
    }

    Node_Alloc node_alloc(alloc_);
    q_.head = q_.tail = nullptr;
    size_ = 0;

    for (Node* n = other.q_.head; n; n = n->next) {
        Node* new_node = node_alloc.allocate(1);
        std::allocator_traits<Node_Alloc>::construct(node_alloc, new_node, n->value, nullptr);

        if (!q_.head) {
            q_.head = q_.tail = new_node;
        } else {
            q_.tail->next = new_node;
            q_.tail = new_node;
        }
        ++size_;
    }
}

template <typename T, typename Alloc>
Queue<T, Alloc>::~Queue() {
    clear();
}