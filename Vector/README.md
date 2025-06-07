# MyVector

`MyVector` is a custom implementation of a dynamic array of integers, mimicking the core functionality of `std::vector<int>`. The class is manually managing dynamic memory allocation, element access, resizing, and copy operations. It is implemented using raw pointers without relying on standard containers.

## Implemented Functionality

### Constructors, destructor, and assignment operator

- **Default Constructor**: Initializes an empty vector with zero size and capacity.
- **Parameterized Constructor**: `MyVector(size_t size, int value)` creates a vector containing `size` elements, each initialized to `value`.
- **Initializer List Constructor**: `MyVector(std::initializer_list<int> list)` creates a vector initialized with the elements from the given initializer list. The size is set to the number of elements in the list, and the capacity is allocated as twice the size to allow room for growth.
- **Copy Constructor**: Creates a deep copy of another `MyVector` instance, duplicating its elements and capacity.
- **Move Constructor (`noexcept`)**: Transfers ownership of resources from another `MyVector` instance, leaving it in a valid but empty state. Marked `noexcept` to guarantee no exceptions will be thrown during the move.
- **Destructor**: Frees all dynamically allocated memory and cleans up the vector upon object destruction.

### Modifiers

- `push_back(int value)`: Adds an element to the end of the vector. Reallocates memory if the size equals capacity.
- `pop_back()`: Removes the last element of the vector.
- `insert(size_t pos, int value)`: Inserts `value` at position `pos`, shifting all elements to the right. Reallocates if needed.
- `erase(size_t pos)`: Removes the element at position `pos`, shifting all subsequent elements to the left.
- `clear()`: Resets the size to 0 but retains the allocated memory.
- `resize(size_t newSize)`: Changes the logical size of the vector. Reallocates memory if necessary. New elements are zero-initialized.
- `reserve(size_t newCapacity)`: Ensures at least `newCapacity` elements can be stored without reallocation.
- `shrink_to_fit()`: Reduces capacity to match the current size, freeing unused memory.
- `swap(MyVector& other)`: Exchanges the contents and metadata (pointer, size, capacity) with another vector.

### Element Access

- `at(size_t index)`: Access the index of elements. Throw an error if the vector is empty.
- `operator[](size_t index)`: Provides mutable and const access to elements by index. Out-of-bounds access is not prevented in this method but can be manually guarded using `checkValidIndex()`.
- `front() / back()`: Access the first and last elements. 

### Capacity and Size

- `size()`: Returns the number of elements in the vector.
- `capacity()`: Returns the currently allocated memory capacity.
- `empty()`: Checks if the vector has no elements.

### Debugging

- `print()`: Outputs all elements of the vector to `std::cout`.

### Internal Utilities

- `checkEmpty()`: Throws an exception if the vector is empty (used in `pop_back()`, `front()`, `back()`).
- `checkValidIndex(size_t index)`: Throws an exception if the index is out of bounds.
- `reallocate(size_t newCapacity)`: Allocates a new array, copies over existing elements, and replaces the internal pointer.

