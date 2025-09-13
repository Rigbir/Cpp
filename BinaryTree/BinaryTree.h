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

private:
    void addElement(Node*& node, T value);
    void deleteElement(Node*& node, T value);
    Node* findPredeccesor(Node*& node);

    static bool searchElement(Node* node, T value);
    void printTree(Node* node, const std::string& prefix, bool isLeft) const;

public:
    void add(T value);
    void del(T value);
    bool find(T value) const;
    void print() const;

};

#include "BinaryTree.tpp"