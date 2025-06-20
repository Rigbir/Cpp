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
typename List<T>::Node* List<T>::insert(Iterator pos, const T& value) {
    Node* nodePos = pos.ptr;

    if (nodePos == nullptr) {
        throw std::invalid_argument("No correct pointer!");
    }

    if (head == nullptr) {
        head = new Node(value);
        return head;
    }

    if (nodePos == head) {
        Node* newNode = new Node(value);

        newNode->next = nodePos;
        nodePos->prev = newNode;
        head = newNode;
        return newNode;
    }

    Node* newNode = new Node(value);

    newNode->next = nodePos;
    newNode->prev = nodePos->prev;

    if (nodePos->prev) {
        nodePos->prev->next = newNode;
    }
    nodePos->prev = newNode;

    return newNode;
}

template<typename T>
typename List<T>::Node* List<T>::erase(Iterator pos) {
    Node* nodePos = pos.ptr;

    if (head == nullptr || nodePos == nullptr) {
        throw std::invalid_argument("List empty!");
    }

    if (nodePos == head) {
        head = nodePos->next;
        if (head) {
            head->prev = nullptr;
        }
    } else if (nodePos->next == nullptr) {
        if (nodePos->prev) {
            nodePos->prev->next = nullptr;
        }
    } else {
        nodePos->prev->next = nodePos->next;
        nodePos->next->prev = nodePos->prev;
    }

    delete nodePos;
    return head;
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
    size_t currentCount = size();

    if (currentCount == count) {
        return;
    }

    if (count < currentCount) {
        Node* current = head;

        for (size_t i = 1; i < count; ++i) {
            current = current->next;
        }

        Node* delNode = current->next;
        current->next = nullptr;

        while (delNode != nullptr) {
            Node* next = delNode->next;
            delete delNode;
            delNode = next;
        }

    } else {
        Node* current = head;

        if (!current) {
            head = new Node(T{});
            currentCount = 1;
            current = head;
        } else {
            while (current->next != nullptr) {
                current = current->next;
            }
        }

        for (size_t i = 0; i < (count - currentCount); ++i) {
            Node* newNode = new Node(T{});

            newNode->next = nullptr;
            newNode->prev = current;
            current->next = newNode;
            current = newNode;
        }
    }
}

template<typename T>
void List<T>::swap(List<T>& other) noexcept {

}

template<typename T>
bool List<T>::empty() const {
    return head == nullptr;
}

template<typename T>
size_t List<T>::size() const {
    size_t count = 0;
    Node* current = head;

    while (current != nullptr) {
        ++count;
        current = current->next;
    }

    return count;
}

template<typename T>
size_t List<T>::max_size() const {
    return std::numeric_limits<size_t>::max() / sizeof(Node);
}

template<typename T>
List<T>::Iterator::Iterator(Node* p)
        : ptr(p) {}

template<typename T>
T& List<T>::Iterator::operator * () {
    return ptr->_value;
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator ++ () {
    ptr = ptr->next;
    return *this;
}

template<typename T>
bool List<T>::Iterator::operator != (const Iterator& other) {
    return ptr != other.ptr;
}

template<typename T>
bool List<T>::Iterator::operator == (const Iterator& other) {
    return ptr == other.ptr;
}


template<typename T>
typename List<T>::Iterator List<T>::begin() {
    return Iterator(head);
}

template<typename T>
typename List<T>::Iterator List<T>::end() {
    return Iterator(nullptr);
}

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