# SFINAE

This project demonstrates **SFINAE (Substitution Failure Is Not An Error)** techniques. It implements custom type traits and function templates that use SFINAE to enable compile-time type introspection and conditional template instantiation.

## Implemented Functionality

### Type Traits

All type traits are located in the `detail` namespace and use SFINAE to detect type properties at compile time.

- `has_value_type<T>`: Checks if a type `T` has a nested `value_type` typedef (common in STL containers).
- `has_size<T>`: Checks if a type `T` has a `size()` member function.
- `is_container<T>`: Checks if a type `T` satisfies container requirements (has `value_type`, `begin()`, and `end()`).
- `is_iterable<T>`: Checks if a type `T` has `begin()` and `end()` member functions (can be iterated over).
- `is_pair_like<T>`: Checks if a type `T` is tuple-like with exactly 2 elements (similar to `std::pair`).

### Function Templates

- `print(const T& value)`: A polymorphic print function that uses SFINAE to select the appropriate implementation:
  - If `T` is **not** a container: prints the value followed by a newline
  - If `T` **is** a container: prints all elements separated by spaces

## Type Traits Reference Table

| Type Trait | Checks For | Returns |
|------------|------------|---------|
| `has_value_type<T>` | Existence of `T::value_type` | `std::true_type` or `std::false_type` |
| `has_size<T>` | Existence of `T::size()` member function | `std::true_type` or `std::false_type` |
| `is_container<T>` | `T::value_type`, `T::begin()`, `T::end()` | `std::true_type` or `std::false_type` |
| `is_iterable<T>` | `T::begin()`, `T::end()` | `std::true_type` or `std::false_type` |
| `is_pair_like<T>` | Tuple-like with exactly 2 elements | `std::true_type` or `std::false_type` |

## Function Templates Reference Table

| Function | Template Condition | Behavior |
|----------|-------------------|----------|
| `print(const T& value)` | `!is_container<T>::value` | Prints value followed by newline |
| `print(const T& cont)` | `is_container<T>::value` | Prints all elements separated by spaces |

