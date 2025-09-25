# unique_ptr

`unique_ptr` is a custom implementation of a **smart pointer** that provides **exclusive ownership** of a dynamically allocated object. It ensures automatic resource management by deleting the managed object when the `unique_ptr` goes out of scope. This implementation also supports a custom deleter.

## Member Variables

- `T* ptr_`: Pointer to the managed object.
- `Deleter del_`: Callable deleter object used to destroy the managed object. Default is `std::default_delete<T>`.

## Constructors, Destructor, and Assignment Operators

- **Default Constructor**: Initializes an empty `unique_ptr` with `ptr_ = nullptr`.
- **Constructor from `nullptr`**: Explicitly creates an empty `unique_ptr`.
- **Constructor from pointer**: Takes ownership of a raw pointer.
- **Constructor from pointer and deleter**: Takes ownership of a raw pointer and stores a custom deleter.
- **Destructor**: Calls the deleter on the managed object if it exists.
- **Deleted Copy Constructor / Assignment**: Copying is disabled to enforce exclusive ownership.
- **Move Constructor (`noexcept`)**: Transfers ownership of the managed object from another `unique_ptr`, leaving it empty.
- **Move Assignment Operator (`noexcept`)**: Transfers ownership from another `unique_ptr`, destroying the current object if it exists.

## Modifiers

- `release() noexcept`: Releases ownership of the managed object and returns the raw pointer. The `unique_ptr` becomes empty.
- `reset(T* ptr = nullptr) noexcept`: Replaces the managed object with a new pointer, calling the deleter on the old object.
- `swap(unique_ptr& other) noexcept`: Swaps the managed objects and deleters with another `unique_ptr`.

## Observers

- `get() noexcept / const`: Returns the raw pointer to the managed object.
- `get_deleter() noexcept / const`: Returns a reference to the deleter.
- `operator bool() const noexcept`: Returns `true` if the `unique_ptr` manages an object, otherwise `false`.
- `operator*() / const`: Dereferences the managed object.
- `operator->() / const`: Accesses members of the managed object.

## Comparison Operators

- `operator==(const unique_ptr& other) const`: Compares managed pointers for equality.
- `operator!=(const unique_ptr& other) const`: Compares managed pointers for inequality.
- `operator==(std::nullptr_t) const`: Checks if the `unique_ptr` is empty.
- `operator!=(std::nullptr_t) const`: Checks if the `unique_ptr` is not empty.

## Helper Functions

- `make_unique<T>(Args&&... args)`: Creates a `unique_ptr` managing a newly constructed object of type `T` with forwarded constructor arguments.

## unique_ptr Methods Table

| Category                     | Function / Operator                                      | Description |
|-------------------------------|----------------------------------------------------------|-------------|
| **Constructors**             | `unique_ptr()`                                           | Default constructor, creates an empty smart pointer. |
|                               | `unique_ptr(std::nullptr_t)`                             | Creates an empty smart pointer. |
|                               | `unique_ptr(T* ptr)`                                     | Takes ownership of a raw pointer. |
|                               | `unique_ptr(T* ptr, Deleter del)`                        | Takes ownership of a raw pointer with a custom deleter. |
|                               | `unique_ptr(unique_ptr&& other) noexcept`               | Move constructor, transfers ownership from another `unique_ptr`. |
| **Destructor**                | `~unique_ptr()`                                         | Deletes the managed object using the deleter. |
| **Assignment**                | `operator=(const unique_ptr&) = delete`                 | Copy assignment is deleted. |
|                               | `operator=(unique_ptr&& other) noexcept`               | Move assignment, transfers ownership from another `unique_ptr`. |
| **Modifiers**                 | `release() noexcept`                                    | Releases ownership and returns the raw pointer. |
|                               | `reset(T* ptr = nullptr) noexcept`                      | Replaces the managed object, deleting the old one. |
|                               | `swap(unique_ptr& other) noexcept`                      | Swaps the managed objects and deleters with another `unique_ptr`. |
| **Observers**                 | `get() / const`                                         | Returns the raw pointer. |
|                               | `get_deleter() / const`                                 | Returns a reference to the deleter. |
|                               | `operator bool() const noexcept`                        | Returns `true` if managing an object. |
|                               | `operator*() / const`                                   | Dereferences the managed object. |
|                               | `operator->() / const`                                  | Accesses members of the managed object. |
| **Comparison**                | `operator==(const unique_ptr&) const`                   | Checks pointer equality. |
|                               | `operator!=(const unique_ptr&) const`                   | Checks pointer inequality. |
|                               | `operator==(std::nullptr_t) const`                      | Checks if empty. |
|                               | `operator!=(std::nullptr_t) const`                      | Checks if not empty. |
| **Helpers**                   | `make_unique<T>(Args&&... args)`                         | Creates a `unique_ptr` managing a new object of type `T`. |
