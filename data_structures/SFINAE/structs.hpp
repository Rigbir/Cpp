//
// Created by Marat on 10.12.25.
//

#pragma once

#include <type_traits>
#include <iostream>

namespace detail {

//======================================

template <typename T, typename = void>
struct has_value_type
    : std::false_type {};

template <typename T>
struct has_value_type<T, std::void_t<typename T::value_type>>
    : std::true_type {};

//======================================

template <typename T, typename = void>
struct has_size
    : std::false_type {};

template <typename T>
struct has_size<T, std::void_t<decltype(std::declval<T>().size())>>
    : std::true_type {};

//======================================

template <typename T, typename = void>
struct is_container
    : std::false_type {};

template <typename T>
struct is_container<T, std::void_t<typename T::value_type,
                                   decltype(std::declval<T>().begin()),
                                   decltype(std::declval<T>().end())>>
    : std::true_type {};

//======================================

template <typename T, typename = void>
struct is_iterable
    : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin()),
                                  decltype(std::declval<T>().end())>>
    : std::true_type {};

//======================================

template <typename T, typename = void>
struct is_pair_like
    : std::false_type {};

template <typename T>
struct is_pair_like<T, std::void_t<typename std::tuple_size<T>::type,
                                   decltype(std::get<0>(std::declval<T>())),
                                   decltype(std::get<1>(std::declval<T>()))>>
    : std::bool_constant<std::tuple_size_v<T> == 2> {};

//======================================

template <typename T, std::enable_if_t<!is_container<T>::value, int> = 0>
void print (const T& value) {
    std::cout << value << '\n';
}

template <typename T, std::enable_if_t<is_container<T>::value, int> = 0>
void print (const T& cont) {
    for (const auto& c : cont) {
        std::cout << c << ' ';
    }
}

//======================================

}
