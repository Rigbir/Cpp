//
// Created by Marat on 14.06.25.
//

#pragma once

template<typename T>
List<T>::Node::Node(const T& value)
        :  _value(value)
        , next(nullptr)
        , prev(nullptr) {}

template<typename T>
List<T>::List()
        : head(nullptr) {}

template<typename T>
List<T>::List(const T& value)
        : head(new Node(value)) {}

template<typename T>
List<T>::List(size_t count, const T& value)
        : head(new Node(value)) {
    Node* current = head;

    for (size_t i = 1; i < count; ++i) {
        Node* newNode = new Node(value);

        newNode->next = nullptr;
        newNode->prev = current;
        current->next = newNode;
        current = newNode;
    }
}

template<typename T>
List<T>::List(std::initializer_list<T> list) {
    if (list.size() == 0) {
        head = nullptr;
        return;
    }

    auto it = list.begin();
    head = new Node(*it);
    Node* current = head;

    ++it;
    for (; it != list.end(); ++it) {
        Node* newNode = new Node(*it);
        newNode->next = nullptr;
        newNode->prev = current;
        current->next = newNode;

        current = newNode;
    }
}

template<typename T>
List<T>::List(const List<T>& other) {
    if (other.head == nullptr) {
        head = nullptr;
        return;
    }

    head = new Node(other.head->_value);
    Node* otherCurrent = other.head->next;
    Node* current = head;

    while (otherCurrent != nullptr) {
        Node* newNode = new Node(otherCurrent->_value);

        newNode->next = nullptr;
        newNode->prev = current;
        current->next = newNode;

        current = newNode;
        otherCurrent = otherCurrent->next;
    }
}

template<typename T>
List<T>::List(List<T>&& other) noexcept
        : head(other.head) {
    other.head = nullptr;
}

template<typename T>
void List<T>::clear() {
    Node* current = head;

    while (current != nullptr) {
        Node* node = current->next;
        delete current;
        current = node;
    }

    head = nullptr;
}

template<typename T>
typename List<T>::Node* List<T>::insert(Node* pos, const T& value) {
    Node* newNode = new Node(value);

    newNode->next = pos->next;
    newNode->prev = (pos ? pos->prev : nullptr);


    return newNode;
}

template<typename T>
typename List<T>::Node* List<T>::erase(List<T>* pos) {

}

template<typename T>
void List<T>::push_back(const T& value) {
    if (head == nullptr) {
        head = new Node(value);
        return;
    }

    Node* current = head;

    while (current->next != nullptr) {
        current = current->next;
    }

    Node* newNode = new Node(value);

    newNode->next = nullptr;
    newNode->prev = current;
    current->next = newNode;
}

template<typename T>
void List<T>::pop_back() {
    if (!head) return;

    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    Node* current = head;

    while (current->next != nullptr) {
        current = current->next;
    }

    current->prev->next = nullptr;
    delete current;
}

template<typename T>
void List<T>::push_front(const T& value) {
    if (head == nullptr) {
        head = new Node(value);
        return;
    }

    Node* newNode = new Node(value);

    newNode->next = head;
    newNode->prev = nullptr;
    head->prev = newNode;
    head = newNode;
}

template<typename T>
void List<T>::pop_front() {
    if (head == nullptr) {
        return;
    }

    Node* current = head;
    head = head->next;
    head->prev = nullptr;

    delete current;
}

template<typename T>
void List<T>::resize(size_t count) {

}

template<typename T>
void List<T>::swap(List<T>& other) noexcept {

}

template<typename T>
bool List<T>::empty() const {
    return head == nullptr;
}

template<typename T>
void List<T>::size() const {

}

template<typename T>
void List<T>::max_size() const {

}

template<typename T>
typename List<T>::Node* List<T>::begin() {
    return head;
}

// template <typename U>
// std::ostream& operator << (std::ostream& os, List<U>* it) {
//     return os <<  *it;
// }

template<typename T>
void List<T>::print() {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->_value << ' ';
        current = current->next;
    }
    std::cout << '\n';
}

template<typename T>
List<T>::~List() {
    clear();
}