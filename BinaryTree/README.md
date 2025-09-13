# BinaryTree

`BinaryTree` is a custom implementation of a **binary search tree (BST)** template class.  
It provides functionality for adding, searching, deleting elements, and printing the tree in a human-readable hierarchical format.  

---

## Implemented Functionality

### Node Structure
- Each `Node` contains:
    - `T value`: Stored value of the node.
    - `Node* left`: Pointer to the left child.
    - `Node* right`: Pointer to the right child.
- A constructor `explicit Node(T v)` initializes the node with the given value.

---

### Internal Utilities

- **`addElement(Node*& node, T value)`**  
  Recursive helper for `add()`. Finds the correct position and inserts a new node.

- **`deleteElement(Node*& node, T value)`**  
  Recursive helper for `del()`. Implements the full BST deletion algorithm.

- **`findPredeccesor(Node*& node)`**  
  Locates the inorder predecessor (maximum value in the left subtree).

- **`searchElement(Node* node, T value)`**  
  Static recursive search helper used by `find()`.

- **`printTree(Node* node, const std::string& prefix, bool isLeft) const`**  
  Recursive helper for `print()`.  
  Uses `prefix` and `isLeft` to generate proper ASCII indentation and branch symbols (`├──`, `└──`, `│`).

---

## Example Usage

```cpp
#include "BinaryTree.h"
#include <iostream>

int main() {
  BinaryTree<int> tree;

  tree.add(5);
  tree.add(3);
  tree.add(6);
  tree.add(1);
  tree.add(4);

  tree.print();

  std::cout << std::boolalpha << tree.find(1) << '\n'; // true
  
  tree.del(1);
  tree.print();
  
  std::cout << std::boolalpha << tree.find(1) << '\n'; // false
}
