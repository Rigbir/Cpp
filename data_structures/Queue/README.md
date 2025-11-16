# Queue

`Queue` is a custom implementation of a **FIFO (First In, First Out)** container, similar in functionality to `std::queue<template>`. The class is implemented using a singly-linked list with manual memory management through custom allocators. It supports custom allocators, move semantics, perfect forwarding, and follows STL container conventions.

## Implemented Functionality

### Constructors, Destructor, and Assignment Operators

- **Constructor with Allocator**: `explicit Queue(const Alloc& alloc = Alloc())` creates an empty queue with an optional custom allocator.
- **Copy Constructor**: Creates a deep copy of another `Queue` instance, duplicating all nodes. Uses `select_on_container_copy_construction` to properly propagate the allocator.
- **Move Constructor (`noexcept`)**: Transfers ownership of nodes from another `Queue` instance, leaving it in a valid empty state.
- **Destructor**: Frees all dynamically allocated nodes and cleans up the queue upon destruction.
- **Copy Assignment Operator**: Deep copies elements from another queue, replacing existing contents. Respects `propagate_on_container_copy_assignment` trait.
- **Move Assignment Operator (`noexcept`)**: Transfers ownership from another queue, clearing the current queue first. Respects `propagate_on_container_move_assignment` trait.

### Modifiers

- `push(const T& value)`: Adds an element to the back of the queue by copying `value`.
- `push(T&& value)`: Adds an element to the back of the queue by moving `value`.
- `emplace(Args&&... args)`: Constructs an element in-place at the back of the queue using perfect forwarding, avoiding unnecessary copies or moves.
- `pop()`: Removes the front element from the queue. Throws `std::runtime_error` if the queue is empty.
- `swap(Queue& other) noexcept`: Exchanges contents with another queue. Respects `propagate_on_container_swap` trait for allocator swapping.

### Element Access

- `top()`: Returns a reference to the front element. Throws `std::runtime_error` if the queue is empty.
- `top() const`: Returns a const reference to the front element for read-only access.

### Capacity and Size

- `empty() const noexcept`: Returns `true` if the queue has no elements.
- `size() const noexcept`: Returns the number of elements in the queue.

### Allocator Support

- `get_allocator() const noexcept`: Returns a copy of the allocator used by the queue.
- **Custom Allocators**: Supports any allocator type that meets the `Allocator` requirements. Uses `rebind_alloc` to allocate `Node` objects.

## Queue Reference Table

| Category                     | Function / Operator                                      | Description |
|------------------------------|----------------------------------------------------------|-------------|
| **Type Aliases**             | `allocator_type`                                         | Type alias for the allocator type. |
| **Constructors**             | `Queue(const Alloc& alloc = Alloc())`                   | Creates an empty queue with an optional custom allocator. |
|                               | `Queue(const Queue& other)`                             | Copy constructor. Deep copies another queue. |
|                               | `Queue(Queue&& other) noexcept`                        | Move constructor. Transfers ownership of nodes. |
| **Destructor**                | `~Queue()`                                              | Destroys all nodes and cleans up the queue. |
| **Assignment**                | `operator=(const Queue& other)`                        | Copy assignment operator. Deep copies elements. |
|                               | `operator=(Queue&& other) noexcept`                    | Move assignment operator. Transfers ownership. |
| **Modifiers**                 | `push(const T& value)`                                  | Adds element to the back by copying. |
|                               | `push(T&& value)`                                       | Adds element to the back by moving. |
|                               | `emplace(Args&&... args)`                               | Constructs element in-place at the back using perfect forwarding. |
|                               | `pop()`                                                 | Removes the front element. Throws if empty. |
|                               | `swap(Queue& other) noexcept`                          | Exchanges contents with another queue. |
| **Element Access**            | `top()`                                                 | Returns reference to the front element. Throws if empty. |
|                               | `top() const`                                           | Returns const reference to the front element. |
| **Capacity / Size**           | `empty() const noexcept`                               | Returns `true` if the queue has no elements. |
|                               | `size() const noexcept`                                | Returns the number of elements. |
| **Allocator**                 | `get_allocator() const noexcept`                       | Returns a copy of the allocator. |

## Implementation Details

- **Memory Management**: Uses `std::allocator_traits` for all memory operations to ensure compatibility with custom allocators.
- **Exception Safety**: Basic exception safety is provided. Operations that throw exceptions leave the queue in a valid state.
- **Allocator Propagation**: Properly handles allocator propagation traits:
  - `propagate_on_container_copy_assignment`
  - `propagate_on_container_move_assignment`
  - `propagate_on_container_swap`
  - `select_on_container_copy_construction`
- **Performance**: `transfer()` method efficiently copies all elements from another queue, maintaining FIFO order.

