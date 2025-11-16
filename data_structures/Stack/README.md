# Stack

`Stack` is a custom implementation of a **LIFO (Last In, First Out)** container, similar in functionality to `std::stack<template>`. The class is implemented using a singly-linked list with manual memory management through custom allocators. It supports custom allocators, move semantics, perfect forwarding, and follows STL container conventions.

## Implemented Functionality

### Constructors, Destructor, and Assignment Operators

- **Constructor with Allocator**: `explicit Stack(const Alloc& alloc = Alloc())` creates an empty stack with an optional custom allocator.
- **Copy Constructor**: Creates a deep copy of another `Stack` instance, duplicating all nodes. Uses `select_on_container_copy_construction` to properly propagate the allocator.
- **Move Constructor (`noexcept`)**: Transfers ownership of nodes from another `Stack` instance, leaving it in a valid empty state.
- **Destructor**: Frees all dynamically allocated nodes and cleans up the stack upon destruction.
- **Copy Assignment Operator**: Deep copies elements from another stack, replacing existing contents. Respects `propagate_on_container_copy_assignment` trait.
- **Move Assignment Operator (`noexcept`)**: Transfers ownership from another stack, clearing the current stack first. Respects `propagate_on_container_move_assignment` trait.

### Modifiers

- `push(const T& value)`: Adds an element to the top of the stack by copying `value`.
- `push(T&& value)`: Adds an element to the top of the stack by moving `value`.
- `emplace(Args&&... args)`: Constructs an element in-place at the top of the stack using perfect forwarding, avoiding unnecessary copies or moves.
- `pop()`: Removes the top element from the stack. Throws `std::runtime_error` if the stack is empty.
- `swap(Stack& other) noexcept`: Exchanges contents with another stack. Respects `propagate_on_container_swap` trait for allocator swapping.

### Element Access

- `top()`: Returns a reference to the top element. Throws `std::runtime_error` if the stack is empty.
- `top() const`: Returns a const reference to the top element for read-only access.

### Capacity and Size

- `empty() const noexcept`: Returns `true` if the stack has no elements.
- `size() const noexcept`: Returns the number of elements in the stack.

### Allocator Support

- `get_allocator() const noexcept`: Returns a copy of the allocator used by the stack.
- **Custom Allocators**: Supports any allocator type that meets the `Allocator` requirements. Uses `rebind_alloc` to allocate `Node` objects.

## Stack Reference Table

| Category                     | Function / Operator                                      | Description |
|-------------------------------|----------------------------------------------------------|-------------|
| **Type Aliases**             | `allocator_type`                                         | Type alias for the allocator type. |
| **Constructors**             | `Stack(const Alloc& alloc = Alloc())`                   | Creates an empty stack with an optional custom allocator. |
|                               | `Stack(const Stack& other)`                             | Copy constructor. Deep copies another stack. |
|                               | `Stack(Stack&& other) noexcept`                        | Move constructor. Transfers ownership of nodes. |
| **Destructor**                | `~Stack()`                                              | Destroys all nodes and cleans up the stack. |
| **Assignment**                | `operator=(const Stack& other)`                        | Copy assignment operator. Deep copies elements. |
|                               | `operator=(Stack&& other) noexcept`                    | Move assignment operator. Transfers ownership. |
| **Modifiers**                 | `push(const T& value)`                                  | Adds element to the top by copying. |
|                               | `push(T&& value)`                                       | Adds element to the top by moving. |
|                               | `emplace(Args&&... args)`                               | Constructs element in-place at the top using perfect forwarding. |
|                               | `pop()`                                                 | Removes the top element. Throws if empty. |
|                               | `swap(Stack& other) noexcept`                          | Exchanges contents with another stack. |
| **Element Access**            | `top()`                                                 | Returns reference to the top element. Throws if empty. |
|                               | `top() const`                                           | Returns const reference to the top element. |
| **Capacity / Size**           | `empty() const noexcept`                               | Returns `true` if the stack has no elements. |
|                               | `size() const noexcept`                                | Returns the number of elements. |
| **Allocator**                 | `get_allocator() const noexcept`                       | Returns a copy of the allocator. |

## Implementation Details

- **Memory Management**: Uses `std::allocator_traits` for all memory operations to ensure compatibility with custom allocators.
- **Exception Safety**: Basic exception safety is provided. Operations that throw exceptions leave the stack in a valid state.
- **Allocator Propagation**: Properly handles allocator propagation traits:
  - `propagate_on_container_copy_assignment`
  - `propagate_on_container_move_assignment`
  - `propagate_on_container_swap`
  - `select_on_container_copy_construction`
- **Performance**: `transfer()` uses a vector of pointers instead of copying values, reducing memory overhead when copying the stack.


