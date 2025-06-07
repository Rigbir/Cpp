MyString
========

`MyString` is a custom implementation of a dynamic string class, designed to mimic core functionality of `std::string`. It manages a dynamically allocated character array and provides support for construction, resizing, element access, string operations, and stream I/O — all done manually without relying on standard containers or `std::string`.

Implemented Functionality
-------------------------

### Constructors, Destructor, and Assignment Operators

*   **Default Constructor**: Initializes an empty string. The internal character pointer is set to nullptr or an empty array.

*   **Size Constructor**: explicit `MyString(size_t size)` allocates space for size characters, plus a null terminator, but does not initialize the characters.

*   **Size and Fill Constructor**: explicit `MyString(size_t size, char c)` creates a string of length size, where every character is initialized to c.

*   **C-string Constructor**: `MyString(const char* str)` creates a string by copying from a null-terminated C-style string.

*   **Initializer List Constructor**: `MyString(std::initializer_list list)` initializes the string from a list of characters.

*   **Copy Constructor**: Performs a deep copy of another `MyString` instance.

*   **Move Constructor (noexcept)**: Transfers ownership of memory from another instance and leaves the source in a valid, empty state.

*   **Destructor**: Releases the dynamically allocated memory used by the string.


### Assignment Operators

*   **Copy Assignment Operator**: `MyString& operator=(const MyString& other)` performs a deep copy, similar to the copy constructor.

*   **Move Assignment Operator (noexcept)**: `MyString& operator=(MyString&& other)` noexcept transfers memory ownership from another object, freeing the current memory.


### Element Access

*   `char& operator[](size_t index) / const char& operator[](size_t index)` const: Provides direct access to a character at the specified index without bounds checking.

*   `char& at(size_t index) / const char& at(size_t index) const`: Provides safe access with bounds checking.

*   `char& front()` const: Returns the first character of the string.

*   `char& back()` const: Returns the last character of the string.


### Modifiers

*   `void clear()`: Clears the contents of the string and resets its size.

*   `void push_back(char c)`: Appends a character to the end of the string.

*   `void pop_back()`: Removes the last character from the string.

*   `void resize(size_t newSize)`: Resizes the string, preserving or trimming characters.

*   `void reserve(size_t newCapacity)`: Pre-allocates capacity without changing the size.

*   `void shrink_to_fit()`: Reduces capacity to match the current size.

*   `void insert(size_t pos, char c)`: Inserts a character at a given position.

*   `void erase(size_t pos)`: Removes the character at a specified index.


### Operators

*   `MyString operator+(const MyString& other) const`: Returns a new string that is the concatenation of this and another string.

*   `MyString& operator+=(const MyString& other)`: Appends another string to this one.

*   `Comparison operators: ==, !=, <, >, <=, >=` to compare string contents lexicographically.


### String Functions

*   `MyString substr(size_t pos, size_t len) const`: Returns a substring starting at position pos with length len.

*   `size_t find(char c, size_t start = 0)` const: Finds the first occurrence of a character starting from position start.

*   `size_t find(const MyString& other, size_t start = 0)` const: Finds the first occurrence of another MyString in this one.

*   `bool contains(const MyString& other)` const: Returns true if this string contains the substring other.


### Iterators

*   `char* begin() / char* end()`: Returns non-const pointers to the start and end of the string for iteration.

*   `const char* begin() const / const char* end() const`: Returns const pointers for read-only iteration.


### Capacity

*   `size_t size() const noexcept`: Returns the number of characters in the string (excluding null terminator).

*   `size_t capacity() const noexcept`: Returns the total allocated capacity.

*   `bool empty() const noexcept`: Returns true if the string is empty.


### Input and Output

*   `void print() const`: Prints the contents of the string (manual debug printing).

*   `friend std::ostream& operator<<(std::ostream& os, const MyString& str)`: Enables output using std::cout << str.

*   `friend std::istream& operator>>(std::istream& is, MyString& str)`: Enables input using std::cin >> str.


### Private Utility Functions

*   `static size_t strlen(const char* start)`: Custom implementation of string length calculation.

*   `void checkEmpty() const`: Utility function to ensure the string isn't empty (for safety checks).

*   `void validIndex(size_t index) const`: Throws or asserts if the index is out of bounds.

*   `void reallocate(size_t newCapacity)`: Resizes the underlying buffer while preserving contents.