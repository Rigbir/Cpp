//
// Created by Marat on 10.09.25.
//

#pragma once
#include <iostream>

template <typename T>
void BinaryTree<T>::add(T value) {
    addElement(root, value);
}

template <typename T>
void BinaryTree<T>::del(T value) {
    deleteElement(root, value);
}

template <typename T>
bool BinaryTree<T>::find(T value) const {
    return searchElement(root, value);
}

template <typename T>
void BinaryTree<T>::print() const {
    std::cout << root->value << '\n';
    if (root->left)  printTree(root->left, "", true);
    if (root->right) printTree(root->right, "", false);
}

template <typename T>
void BinaryTree<T>::inOrder() const {
    return orderIn(root);
}

template <typename T>
void BinaryTree<T>::preOrder() const {
    return orderPre(root);
}

template <typename T>
void BinaryTree<T>::postOrder() const {
    return orderPost(root);
}

template <typename T>
int BinaryTree<T>::height() const {
    return heightTree(root);
}

template <typename T>
T BinaryTree<T>::minValue() const {
    if (root == nullptr) {
        throw std::runtime_error("Tree is Empty");
    }
    return findMin(root)->value;
}

template <typename T>
T BinaryTree<T>::maxValue() const {
    if (root == nullptr) {
        throw std::runtime_error("Tree is Empty");
    }
    return findMax(root)->value;
}

template <typename T>
BinaryTree<T>::BinaryTree(): root(nullptr) {}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other) {
    if (other == nullptr) return;
    root = copyNode(other.root);
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::operator = (const BinaryTree& other) {
    if (this == &other) return *this;
    clear(root);
    root = copyNode(other.root);
    return *this;
}

template <typename T>
BinaryTree<T>::BinaryTree(BinaryTree&& other) noexcept {
    root = other.root;
    other.root = nullptr;
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::operator = (BinaryTree&& other) noexcept {
    if (this == &other) return *this;
    root = other.root;
    other.root = nullptr;
    return *this;
}

template <typename T>
BinaryTree<T>::Node::Node(T v): left(nullptr), right(nullptr), value(v) {}

template <typename T>
void BinaryTree<T>::addElement(Node*& node, T value) {
    if (node == nullptr) {
        node = new Node(value);
        return;
    }

    if (value == node->value) {
        return;
    }

    if (value < node->value) {
        addElement(node->left, value);
    } else if (value > node->value) {
        addElement(node->right, value);
    }
}

template <typename T>
void BinaryTree<T>::deleteElement(Node*& node, T value) {
    if (node == nullptr) return;

    if (value < node->value) {
        deleteElement(node->left, value);
    } else if (value > node->value) {
        deleteElement(node->right, value);
    } else {
        if (!node->left && !node->right) {
            delete node;
            node = nullptr;
        } else if (!node->left || !node->right) {
            Node* child = (node->left) ? node->left : node->right;
            delete node;
            node = child;
        } else {
            Node* pred = findPredecessor(node);
            node->value = pred->value;
            deleteElement(node->left, pred->value);
        }
    }
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::findPredecessor(Node*& node) {
    Node* pred = node->left;
    while (pred->right) {
        pred = pred->right;
    }
    return pred;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::findMax(Node* node) {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::copyNode(Node* node) {
    if (node == nullptr) return nullptr;
    Node* newNode = new Node(node->value);
    node->left = copyNode(node->left);
    node->right = copyNode(node->right);
    return newNode;
}

template <typename T>
void BinaryTree<T>::orderIn(Node* node) const {
    if (node == nullptr) return;
    orderIn(node->left);
    std::cout << node->value << ' ';
    orderIn(node->right);
}

template <typename T>
void BinaryTree<T>::orderPre(Node* node) const {
    if (node == nullptr) return;
    std::cout << node->value << ' ';
    orderPre(node->left);
    orderPre(node->right);
}

template <typename T>
void BinaryTree<T>::orderPost(Node* node) const {
    if (node == nullptr) return;
    orderPost(node->left);
    orderPost(node->right);
    std::cout << node->value << ' ';
}

template <typename T>
bool BinaryTree<T>::searchElement(Node* node, T value) {
    while (node != nullptr) {
        if (value == node->value) {
            return true;
        }

        if (value < node->value) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return false;
}

template <typename T>
void BinaryTree<T>::printTree(Node* node, const std::string& prefix, bool isLeft) const {
    if (node == nullptr) return;

    std::cout << prefix;
    std::cout << (isLeft ? "├── " : "└── ");
    std::cout << node->value << '\n';

    const std::string childPrefix = prefix + (isLeft ? "│   " : "    ");

    if (node->left) {
        printTree(node->left, childPrefix, true);
    }
    if (node->right) {
        printTree(node->right, childPrefix, false);
    }
}

template <typename T>
int BinaryTree<T>::heightTree(Node* node) const {
    if (node == nullptr) return 0;
    return 1 + std::max(heightTree(node->left), heightTree(node->right));
}

template <typename T>
void BinaryTree<T>::clear(Node*& node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
    clear(root);
}