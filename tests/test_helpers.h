#pragma once
#include <algorithm>
#include <random>
#include <vector>
#include <catch2/catch.hpp>

template <typename Sort>
void check_examples(Sort sort) {
    const std::vector<std::vector<int>> examples{
        {}, {42}, {1, 2, 3, 4, 5}, {5, 4, 3, 2, 1},
        {3, -2, 0, 3, -2, 7, 1}, {4, 4, 4, 4}, {2, 1}, {1, 2}
    };
    for (const auto& example : examples) {
        auto actual = example, expected = example;
        std::sort(expected.begin(), expected.end());
        sort(actual);
        REQUIRE(actual == expected);
    }
}

template <typename Sort>
void check_random(Sort sort, int cases = 40, int maximum_size = 80) {
    std::mt19937 random(20261011);
    std::uniform_int_distribution<int> size(0, maximum_size), value(-100, 100);
    for (int i = 0; i < cases; ++i) {
        std::vector<int> actual(static_cast<std::size_t>(size(random)));
        for (auto& item : actual) item = value(random);
        auto expected = actual;
        std::sort(expected.begin(), expected.end());
        sort(actual);
        REQUIRE(actual == expected);
    }
}

struct Record { int key; int original_position; };
