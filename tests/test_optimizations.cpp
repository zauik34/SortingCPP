#include "insertion_sort.h"
#include "binary_insertion_sort.h"
#include "bubble_sort.h"
#include "optimized_bubble_sort.h"
#include "shaker_sort.h"
#include "quick_sort.h"
#include <catch2/catch.hpp>
#include <algorithm>
#include <numeric>

TEST_CASE("Optimized bubble: sorted input stops after one pass", "[lab1][optimization]") {
    std::vector<int> values(64);
    std::iota(values.begin(), values.end(), 0);
    auto basic = values;
    std::size_t basic_count = 0, optimized_count = 0;
    sorting::bubble_sort(basic, [&](int a, int b) { ++basic_count; return a < b; });
    sorting::optimized_bubble_sort(values, [&](int a, int b) { ++optimized_count; return a < b; });
    REQUIRE(values == basic);
    REQUIRE(optimized_count == 63);
    REQUIRE(basic_count == 64 * 63 / 2);
}

TEST_CASE("Binary insertion: fewer comparisons on reverse input", "[lab2][optimization]") {
    std::vector<int> values(64);
    std::iota(values.rbegin(), values.rend(), 0);
    auto basic = values;
    std::size_t basic_count = 0, binary_count = 0;
    sorting::insertion_sort(basic, [&](int a, int b) { ++basic_count; return a < b; });
    sorting::binary_insertion_sort(values, [&](int a, int b) { ++binary_count; return a < b; });
    REQUIRE(values == basic);
    REQUIRE(binary_count < basic_count / 2);
}

TEST_CASE("Shaker: backward pass quickly moves a small trailing element", "[lab2][optimization]") {
    std::vector<int> values(64);
    std::iota(values.begin(), values.end(), 1);
    values.back() = 0;
    auto bubble = values;
    std::size_t bubble_count = 0, shaker_count = 0;
    sorting::optimized_bubble_sort(bubble, [&](int a, int b) { ++bubble_count; return a < b; });
    sorting::shaker_sort(values, [&](int a, int b) { ++shaker_count; return a < b; });
    REQUIRE(values == bubble);
    REQUIRE(shaker_count < bubble_count / 2);
}

TEST_CASE("Quick sort: equal keys are handled in one partition", "[lab3][optimization]") {
    std::vector<int> values(10000, 7);
    std::size_t comparisons = 0;
    sorting::quick_sort(values, [&](int a, int b) { ++comparisons; return a < b; });
    REQUIRE(comparisons == values.size() * 2);
    REQUIRE(std::all_of(values.begin(), values.end(), [](int value) { return value == 7; }));
}

TEST_CASE("Quick sort: large ordered and reversed inputs", "[lab3][quick_sort]") {
    std::vector<int> values(10000);
    std::iota(values.begin(), values.end(), -5000);
    const auto expected = values;
    sorting::quick_sort(values);
    REQUIRE(values == expected);
    std::reverse(values.begin(), values.end());
    sorting::quick_sort(values);
    REQUIRE(values == expected);
}
