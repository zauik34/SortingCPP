#include "quick_sort.h"
#include "test_helpers.h"
#include <functional>
#include <string>

TEST_CASE("quick_sort: empty input", "[lab3][quick_sort]") {
    std::vector<int> values;
    sorting::quick_sort(values);
    REQUIRE(values.empty());
}
TEST_CASE("quick_sort: single element", "[lab3][quick_sort]") {
    std::vector<int> values{42};
    sorting::quick_sort(values);
    REQUIRE(values == std::vector<int>{42});
}
TEST_CASE("quick_sort: already sorted", "[lab3][quick_sort]") {
    std::vector<int> values{-3, -1, 0, 2, 8};
    const auto expected = values;
    sorting::quick_sort(values);
    REQUIRE(values == expected);
}
TEST_CASE("quick_sort: reverse order", "[lab3][quick_sort]") {
    std::vector<int> values{8, 2, 0, -1, -3};
    sorting::quick_sort(values);
    REQUIRE(values == std::vector<int>{-3, -1, 0, 2, 8});
}
TEST_CASE("quick_sort: duplicates and boundary examples", "[lab3][quick_sort]") {
    check_examples([](auto& values) { sorting::quick_sort(values); });
}
TEST_CASE("quick_sort: double precision", "[lab3][quick_sort]") {
    std::vector<double> values{3.141592653589793, -0.125, 1.2345678901234567, 0.0, -0.125};
    auto expected = values;
    std::sort(expected.begin(), expected.end());
    sorting::quick_sort(values);
    REQUIRE(values == expected);
}
TEST_CASE("quick_sort: descending comparator", "[lab3][quick_sort]") {
    std::vector<int> values{3, -2, 0, 3, 7, 1};
    auto expected = values;
    std::sort(expected.begin(), expected.end(), std::greater<int>{});
    sorting::quick_sort(values, std::greater<int>{});
    REQUIRE(values == expected);
}
TEST_CASE("quick_sort: randomized reference comparison", "[lab3][quick_sort]") {
    check_random([](auto& values) { sorting::quick_sort(values); }, 40);
}

TEST_CASE("quick_sort: generic string type", "[lab3][quick_sort]") {
    std::vector<std::string> values{"pear", "apple", "banana", "apple"};
    sorting::quick_sort(values);
    REQUIRE(values == std::vector<std::string>{"apple", "apple", "banana", "pear"});
}
