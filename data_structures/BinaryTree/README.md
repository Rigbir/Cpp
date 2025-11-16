# BinaryTree

`BinaryTree` is a custom implementation of a **binary search tree** (BST) that stores elements of type `T` in a hierarchical structure. The class manually manages nodes, dynamic memory, element insertion, deletion, traversal, and other common tree operations without relying on standard containers.

## Node Structure

- **Node**: Represents a tree node containing a value of type `T` and pointers to the left and right child nodes (`left` and `right`). Each node is created via a constructor `Node(T value)`.

## Constructors, Destructor, and Assignment Operators

- **Default Constructor**: Initializes an empty tree with `root = nullptr`.
- **Copy Constructor**: Creates a deep copy of another `BinaryTree` instance, duplicating all nodes.
- **Copy Assignment Operator**: Replaces the current tree with a deep copy of another tree.
- **Move Constructor (`noexcept`)**: Transfers ownership of nodes from another tree, leaving it empty.
- **Move Assignment Operator (`noexcept`)**: Replaces the current tree by transferring nodes from another tree.
- **Destructor**: Frees all dynamically allocated nodes and cleans up the tree.

## Modifiers

- `add(T value)`: Inserts a new element into the tree, maintaining BST property.
- `del(T value)`: Deletes an element from the tree if it exists.
- `clear()`: Removes all nodes, leaving the tree empty.

## Element Access and Queries

- `find(T value) const`: Returns `true` if the element exists in the tree, otherwise `false`.
- `minValue() const`: Returns the minimum value stored in the tree.
- `maxValue() const`: Returns the maximum value stored in the tree.
- `height() const`: Returns the height of the tree (longest path from root to a leaf).

## Traversal

- `inOrder() const`: Performs in-order traversal (left-root-right) and prints elements.
- `preOrder() const`: Performs pre-order traversal (root-left-right) and prints elements.
- `postOrder() const`: Performs post-order traversal (left-right-root) and prints elements.

## Debugging and Printing

- `print() const`: Visualizes the tree structure in a human-readable format.

## BinaryTree Methods Table

| Category                     | Function / Operator                                      | Description |
|-------------------------------|----------------------------------------------------------|-------------|
| **Constructors**             | `BinaryTree()`                                           | Default constructor, creates an empty tree. |
|                               | `BinaryTree(const BinaryTree& other)`                   | Copy constructor. Deep copies another tree. |
|                               | `BinaryTree(BinaryTree&& other) noexcept`              | Move constructor. Transfers ownership of nodes. |
| **Destructor**                | `~BinaryTree()`                                         | Deletes all nodes. |
| **Assignment**                | `operator=(const BinaryTree& other)`                    | Copy assignment operator. |
|                               | `operator=(BinaryTree&& other) noexcept`               | Move assignment operator. |
| **Modifiers**                 | `add(T value)`                                          | Inserts a new element into the tree. |
|                               | `del(T value)`                                          | Deletes a node with the given value. |
|                               | `clear()`                                               | Removes all nodes from the tree. |
| **Element Access / Queries**  | `find(T value) const`                                   | Returns `true` if the element exists in the tree. |
|                               | `minValue() const`                                      | Returns the minimum value stored in the tree. |
|                               | `maxValue() const`                                      | Returns the maximum value stored in the tree. |
|                               | `height() const`                                        | Returns the height of the tree. |
| **Traversal**                 | `inOrder() const`                                       | In-order traversal (left-root-right) and prints elements. |
|                               | `preOrder() const`                                      | Pre-order traversal (root-left-right) and prints elements. |
|                               | `postOrder() const`                                     | Post-order traversal (left-right-root) and prints elements. |
| **Debugging / Printing**      | `print() const`                                         | Visualizes the tree structure in a human-readable format. |

