//
// Created by Marat on 14.06.25.
//

#pragma once

template<typename T>
MyList<T>::Node::Node(const T& value)
        :  _value(value)
        , next(nullptr)
        , prev(nullptr) {}

template<typename T>
MyList<T>::MyList()
        : head(nullptr) {}

template<typename T>
MyList<T>::MyList(const T& value)
        : head(new Node(value)) {}

template<typename T>
MyList<T>::MyList(size_t count, const T& value)
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
MyList<T>::MyList(std::initializer_list<T> MyList) {
    if (MyList.size() == 0) {
        head = nullptr;
        return;
    }

    auto it = MyList.begin();
    head = new Node(*it);
    Node* current = head;

    ++it;
    for (; it != MyList.end(); ++it) {
        Node* newNode = new Node(*it);
        newNode->next = nullptr;
        newNode->prev = current;
        current->next = newNode;

        current = newNode;
    }
}

template<typename T>
MyList<T>::MyList(const MyList<T>& other) {
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
MyList<T>::MyList(MyList<T>&& other) noexcept
        : head(other.head) {
    other.head = nullptr;
}

template<typename T>
void MyList<T>::clear() {
    Node* current = head;

    while (current != nullptr) {
        Node* node = current->next;
        delete current;
        current = node;
    }

    head = nullptr;
}

template<typename T>
typename MyList<T>::Node* MyList<T>::insert(Iterator pos, const T& value) {
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
typename MyList<T>::Node* MyList<T>::erase(Iterator pos) {
    Node* nodePos = pos.ptr;

    if (head == nullptr || nodePos == nullptr) {
        throw std::invalid_argument("MyList empty!");
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
void MyList<T>::push_back(const T& value) {
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
void MyList<T>::pop_back() {
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
void MyList<T>::push_front(const T& value) {
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
void MyList<T>::pop_front() {
    if (head == nullptr) {
        return;
    }

    Node* current = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }

    delete current;
}

template<typename T>
void MyList<T>::resize(size_t count) {
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
void MyList<T>::swap(MyList<T>& other) noexcept {
    Node* temp = this->head;
    this->head = other.head;
    other.head = temp;
}

template<typename T>
void MyList<T>::merge(MyList<T>& other) {
    if (other.head == nullptr) {
        return;
    }

    if (head == nullptr) {
        head = other.head;
        other.head = nullptr;
        return;
    }

    Node* current = head;
    Node* otherCurrent = other.head;
    Node* mergedHead = nullptr;
    Node* mergedTail = nullptr;

    if (current->_value <= otherCurrent->_value) {
        mergedHead = current;
        mergedTail = current;
        current = current->next;
    } else {
        mergedHead = otherCurrent;
        mergedTail = otherCurrent;
        otherCurrent = otherCurrent->next;
    }

    while (current != nullptr && otherCurrent != nullptr) {
        if (current->_value <= otherCurrent->_value) {
            mergedTail->next = current;
            current->prev = mergedTail;
            mergedTail = current;
            current = current->next;
        } else {
            mergedTail->next = otherCurrent;
            otherCurrent->prev = mergedTail;
            mergedTail = otherCurrent;
            otherCurrent = otherCurrent->next;
        }
    }

    if (current != nullptr) {
        mergedTail->next = current;
        current->prev = mergedTail;
    } else if (otherCurrent != nullptr) {
        mergedTail->next = otherCurrent;
        otherCurrent->prev = mergedTail;
    }

    head = mergedHead;
    other.head = nullptr;
}

template<typename T>
void MyList<T>::splice(Iterator pos, MyList<T>& other) {
    if (other.head == nullptr) {
        return;
    }

    Node* insertPos = pos.ptr;

    if (head == nullptr) {
        head = other.head;
        other.head = nullptr;
        return;
    }

    if (insertPos == head) {
        Node* lastOther = other.head;
        while (lastOther->next != nullptr) {
            lastOther = lastOther->next;
        }

        lastOther->next = head;
        head->prev = lastOther;
        head = other.head;
        other.head = nullptr;
        return;
    }

    if (insertPos == nullptr) {
        Node* lastCurrent = head;
        while (lastCurrent->next != nullptr) {
            lastCurrent = lastCurrent->next;
        }

        lastCurrent->next = other.head;
        other.head->prev = lastCurrent;
        other.head = nullptr;
        return;
    }

    Node* prevNode = head;
    while (prevNode != nullptr && prevNode->next != insertPos) {
        prevNode = prevNode->next;
    }

    if (prevNode == nullptr) {
        Node* lastCurrent = head;
        while (lastCurrent->next != nullptr) {
            lastCurrent = lastCurrent->next;
        }

        lastCurrent->next = other.head;
        other.head->prev = lastCurrent;
        other.head = nullptr;
        return;
    }

    Node* lastOther = other.head;
    while (lastOther->next != nullptr) {
        lastOther = lastOther->next;
    }

    prevNode->next = other.head;
    other.head->prev = prevNode;

    lastOther->next = insertPos;
    insertPos->prev = lastOther;

    other.head = nullptr;
}

template<typename T>
void MyList<T>::remove(const T& value) {
    Node* current = head;

    while (current != nullptr) {
        if (current->_value == value) {
            Node* delNode = current;
            Node* nextNode = current->next;

            if (delNode->prev) {
                delNode->prev->next = delNode->next;
            } else {
                head = delNode->next;
            }

            if (delNode->next) {
                delNode->next->prev = delNode->prev;
            }

            delete delNode;
            current = nextNode;
        } else {
            current = current->next;
        }
    }
}

template<typename T>
void MyList<T>::reverse() {
    Node* current = head;
    Node* temp = nullptr;

    while (current != nullptr) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;

        current = current->prev;
    }

    if (temp != nullptr) {
        head = temp->prev;
    }
}

template<typename T>
void MyList<T>::unique() {
    Node* current = head;

    while (current->next != nullptr) {
        if (current->_value == current->next->_value) {
            Node* delNode = current->next;

            current->next = delNode->next;
            if (delNode->next) {
                delNode->next->prev = current;
            }

            delete delNode;
        } else {
            current = current->next;
        }
    }
}

template<typename T>
void MyList<T>::mergeForSort(Iterator beginFirst, Iterator endFirst,
                           Iterator beginSecond, Iterator endSecond,
                           Iterator result) {
    Node* first = beginFirst.ptr;
    Node* firstEnd = endFirst.ptr;
    Node* second = beginSecond.ptr;
    Node* secondEnd = endSecond.ptr;
    Node* output = result.ptr;

    while (first != firstEnd && second != secondEnd) {
        if (first->_value < second->_value) {
            output->_value = first->_value;
            first = first->next;
        } else {
            output->_value = second->_value;
            second = second->next;
        }
        output = output->next;
    }

    while (first != firstEnd) {
        output->_value = first->_value;
        first = first->next;
        output = output->next;
    }

    while (second != secondEnd) {
        output->_value = second->_value;
        second = second->next;
        output = output->next;
    }
}


template<typename T>
void MyList<T>::sort(Iterator begin, Iterator end) {
    if (begin == end) return;
    Node* nodeBegin = begin.ptr;
    Node* nodeEnd = end.ptr;

    Iterator nextBegin = begin;
    ++nextBegin;
    if (nextBegin == end) return;

    Node* slow = begin.ptr;
    Node* fast = begin.ptr;
    while (fast != end.ptr && fast->next != end.ptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Iterator mid(slow);
    sort(begin, mid);
    sort(mid, end);
    mergeForSort(begin, mid, mid, end, begin);
}

template<typename T>
bool MyList<T>::empty() const {
    return head == nullptr;
}

template<typename T>
size_t MyList<T>::size() const {
    size_t count = 0;
    Node* current = head;

    while (current != nullptr) {
        ++count;
        current = current->next;
    }

    return count;
}

template<typename T>
size_t MyList<T>::max_size() const {
    return std::numeric_limits<size_t>::max() / sizeof(Node);
}

template<typename T>
MyList<T>& MyList<T>::operator = (const MyList<T>& other) {
    if (this == &other) return *this;

    this->clear();

    Node* current = other.head;
    while (current) {
        push_back(current->_value);
        current = current->next;
    }

    return *this;
}

template<typename T>
bool MyList<T>::operator == (const MyList<T>& other) const {
    Node* first = this->head;
    Node* second = other.head;

    while (first != nullptr) {
        if (first->_value != second->_value) {
            return false;
        }

        first = first->next;
        second = second->next;
    }

    return first == nullptr && second == nullptr;
}

template<typename T>
bool MyList<T>::operator != (const MyList<T>& other) const {
    return !(*this == other);
}

template<typename T>
bool MyList<T>::operator < (const MyList<T>& other) const {
    Node* first = this->head;
    Node* second = other.head;

    while (first != nullptr && second != nullptr) {
        if (first->_value > second->_value) return false;
        if (first->_value < second->_value) return true;

        first = first->next;
        second = second->next;
    }

    return first == nullptr && second != nullptr;
}

template<typename T>
bool MyList<T>::operator > (const MyList<T>& other) const {
    return other < *this;
}

template<typename T>
bool MyList<T>::operator <= (const MyList<T>& other) const {
    return !(other < *this);
}

template<typename T>
bool MyList<T>::operator >= (const MyList<T>& other) const {
    return !(*this < other);
}

template<typename T>
MyList<T>::Iterator::Iterator(Node* p)
        : ptr(p) {}

template<typename T>
T& MyList<T>::Iterator::operator * () {
    return ptr->_value;
}

template<typename T>
T *MyList<T>::Iterator::operator -> () {
    return ptr;
}

template<typename T>
typename MyList<T>::Iterator& MyList<T>::Iterator::operator ++ () {
    ptr = ptr->next;
    return *this;
}

template<typename T>
typename MyList<T>::Iterator MyList<T>::Iterator::operator ++ (int) {
    Iterator copy = *this;
    ptr = ptr->next;
    return copy;
}

template<typename T>
bool MyList<T>::Iterator::operator != (const Iterator& other) {
    return ptr != other.ptr;
}

template<typename T>
bool MyList<T>::Iterator::operator == (const Iterator& other) {
    return ptr == other.ptr;
}

template<typename T>
typename MyList<T>::Iterator MyList<T>::begin() {
    return Iterator(head);
}

template<typename T>
typename MyList<T>::Iterator MyList<T>::cbegin() const {
    return Iterator(head);
}

template<typename T>
typename MyList<T>::Iterator MyList<T>::end() {
    return Iterator(nullptr);
}

template<typename T>
typename MyList<T>::Iterator MyList<T>::cend() const {
    return Iterator(nullptr);
}

template<typename T>
void MyList<T>::print() {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->_value << ' ';
        current = current->next;
    }
    std::cout << '\n';
}

template<typename T>
MyList<T>::~MyList() {
    clear();
}