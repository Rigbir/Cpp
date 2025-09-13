# MyList

`MyList` is a custom implementation of a doubly-linked list, similar in functionality to `std::list<template>`. The class manually manages nodes, dynamic memory, element access, iteration, and common list operations without relying on standard containers.

## Implemented Functionality

### Node Structure

- **Node**: Represents an element in the list with a value of type `T` and pointers to the next and previous nodes (`next` and `prev`). Each node is created via a constructor `Node(const T& value)`.

### Constructors, Destructor, and Assignment Operator

- **Default Constructor**: Initializes an empty list with no nodes.
- **Single Element Constructor**: `MyList(const T& value)` creates a list containing a single element.
- **Parameterized Constructor**: `MyList(size_t count, const T& value)` creates a list with `count` elements, each initialized to `value`.
- **Initializer List Constructor**: `MyList(std::initializer_list<T> list)` creates a list initialized with the elements from the given initializer list.
- **Copy Constructor**: Creates a deep copy of another `MyList` instance, duplicating its nodes.
- **Move Constructor (`noexcept`)**: Transfers ownership of nodes from another `MyList` instance, leaving it in a valid empty state.
- **Destructor**: Frees all dynamically allocated nodes and cleans up the list upon destruction.
- **Assignment Operator**: Deep copies elements from another list, replacing existing contents.

### Modifiers

- `push_back(const T& value)`: Adds an element to the end of the list.
- `pop_back()`: Removes the last element.
- `push_front(const T& value)`: Adds an element to the beginning of the list.
- `pop_front()`: Removes the first element.
- `insert(Iterator pos, const T& value)`: Inserts `value` at the specified iterator position.
- `erase(Iterator pos)`: Removes the node at the specified iterator position.
- `clear()`: Removes all elements from the list.
- `resize(size_t count)`: Resizes the list to contain `count` elements.
- `swap(MyList<T>& other) noexcept`: Exchanges contents and metadata with another list.
- `merge(MyList<T>& other)`: Merges another list into the current list (assumes sorted lists for correct behavior).
- `splice(Iterator pos, MyList<T>& other)`: Inserts all elements from another list at the specified position.
- `remove(const T& value)`: Removes all elements equal to `value`.
- `reverse()`: Reverses the order of the elements.
- `unique()`: Removes consecutive duplicate elements.
- `sort(Iterator begin, Iterator end)`: Sorts elements in the range using merge sort.
- `mergeForSort(...)`: Internal utility to merge two sorted ranges during sorting.

### Element Access and Iterators

- **Iterator**: Provides pointer-like traversal over the list with operators:
    - `*` / `->`: Access the value of the current node.
    - `++` (prefix and postfix): Move to the next node.
    - `== / !=`: Compare iterators for equality.
- `begin() / end()`: Returns iterators to the first/one-past-last element.
- `cbegin() / cend()`: Returns const iterators for read-only traversal.

### Capacity and Size

- `empty()`: Checks if the list has no elements.
- `size()`: Returns the number of elements.
- `max_size()`: Returns the theoretical maximum number of elements.

### Comparison Operators

- `== / !=`: Checks equality or inequality of two lists.
- `< / > / <= / >=`: Lexicographical comparisons between two lists.

### Debugging

- `print()`: Outputs all elements to `std::cout` for inspection.
## MyList Reference Table

| Category                     | Function / Operator                                      | Description |
|-------------------------------|----------------------------------------------------------|-------------|
| **Constructors**             | `MyList()`                                               | Default constructor, creates an empty list. |
|                               | `MyList(const T& value)`                                 | Creates a list with a single element. |
|                               | `MyList(size_t count, const T& value)`                  | Creates a list with `count` elements, all initialized to `value`. |
|                               | `MyList(std::initializer_list<T> list)`                 | Creates a list from an initializer list. |
|                               | `MyList(const MyList<T>& other)`                        | Copy constructor. Deep copies another list. |
|                               | `MyList(MyList<T>&& other) noexcept`                    | Move constructor. Transfers ownership. |
| **Destructor**                | `~MyList()`                                              | Deletes all nodes. |
| **Assignment**                | `operator=(const MyList<T>& other)`                     | Copy assignment operator. |
| **Element Access**            | `Iterator begin()`                                       | Returns iterator to the first element. |
|                               | `Iterator end()`                                         | Returns iterator to one past the last element. |
|                               | `Iterator cbegin() const`                                | Returns const iterator to the first element. |
|                               | `Iterator cend() const`                                  | Returns const iterator to one past the last element. |
| **Modifiers**                 | `push_back(const T& value)`                              | Adds element to the end. |
|                               | `pop_back()`                                             | Removes the last element. |
|                               | `push_front(const T& value)`                             | Adds element to the beginning. |
|                               | `pop_front()`                                            | Removes the first element. |
|                               | `insert(Iterator pos, const T& value)`                  | Inserts `value` at given iterator position. |
|                               | `erase(Iterator pos)`                                    | Removes element at given iterator position. |
|                               | `clear()`                                                | Removes all elements. |
|                               | `resize(size_t count)`                                   | Resizes the list to `count` elements. |
|                               | `swap(MyList<T>& other) noexcept`                        | Swaps contents with another list. |
|                               | `merge(MyList<T>& other)`                                | Merges another list into current one. |
|                               | `splice(Iterator pos, MyList<T>& other)`                | Inserts all elements from another list at position `pos`. |
|                               | `remove(const T& value)`                                 | Removes all elements equal to `value`. |
|                               | `reverse()`                                              | Reverses the list. |
|                               | `unique()`                                               | Removes consecutive duplicate elements. |
|                               | `sort(Iterator begin, Iterator end)`                     | Sorts elements in the specified range. |
| **Capacity / Size**           | `empty() const`                                         | Returns `true` if the list has no elements. |
|                               | `size() const`                                          | Returns the number of elements. |
|                               | `max_size() const`                                      | Returns the maximum theoretical number of elements. |
| **Iterators**                 | `Iterator::operator* / ->`                                | Access the value of the current node. |
|                               | `Iterator::operator++()`                                 | Move to next node (prefix). |
|                               | `Iterator::operator++(int)`                              | Move to next node (postfix). |
|                               | `Iterator::operator== / !=`                              | Compare iterators for equality or inequality. |
| **Comparison Operators**      | `== / !=`                                                | Check equality/inequality of two lists. |
|                               | `< / > / <= / >=`                                       | Lexicographical comparison of two lists. |
| **Debugging**                 | `print()`                                                | Outputs all elements to `std::cout`. |
