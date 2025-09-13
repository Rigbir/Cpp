//
// Created by Marat on 10.09.25.
//

#pragma once
#include <string>

template <typename T>
class BinaryTree final {
private:
    struct Node {
        Node* left;
        Node* right;
        T value;

        explicit Node(T v);
    };

    Node* root = nullptr;

public:
    // BinaryTree(const BinaryTree& other);
    // BinaryTree& operator = (const BinaryTree& other);
    // BinaryTree(BinaryTree&& other) noexcept;
    // BinaryTree& operator = (BinaryTree&& other) noexcept;

    void add(T value);
    void del(T value);
    bool find(T value) const;
    void print() const;

    int height() const;
    T minValue() const;
    T maxValue() const;

    ~BinaryTree();

private:
    void addElement(Node*& node, T value);
    void deleteElement(Node*& node, T value);
    Node* findPredeccesor(Node*& node);
    Node* findMin(Node* node) const;
    Node* findMax(Node* node) const;

    static bool searchElement(Node* node, T value);
    void printTree(Node* node, const std::string& prefix, bool isLeft) const;
    int heightTree(Node* node) const;
    void clear(Node*& node);
};

#include "BinaryTree.tpp"