//
// Created by Marat on 10.12.25.
//

#pragma once

#include "structs.hpp"
#include <cassert>
#include <utility>
#include <vector>
#include <tuple>

void has_value_type_test() {
    assert(!detail::has_value_type<int>::value);
    assert(detail::has_value_type<std::vector<int>>::value);
}

void has_size_test() {
    assert(!detail::has_size<int>::value);
    assert(detail::has_size<std::vector<int>>::value);
}

void is_container_test() {
    assert(!detail::is_container<int>::value);
    assert(detail::is_container<std::vector<int>>::value);
}

void is_iterable_test() {
    assert(!detail::is_iterable<int>::value);
    assert(detail::is_iterable<std::vector<int>>::value);
}

void is_pair_like_test() {
    assert((detail::is_pair_like<std::pair<int, int>>::value));
    assert((detail::is_pair_like<std::tuple<int, int>>::value));
    assert(!detail::is_pair_like<int>::value);
    assert((!detail::is_pair_like<std::tuple<int, int, int>>::value));
}

void print_test() {
    std::cout << "not a container: "; detail::print(423);
    std::cout << "container: "; detail::print(std::vector{2, 4, 5});
}