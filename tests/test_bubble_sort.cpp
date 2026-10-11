#include "bubble_sort.h"
#include "test_helpers.h"
#include <functional>
#include <string>

TEST_CASE("bubble_sort: empty input", "[lab1][bubble_sort]") {
    std::vector<int> values;
    sorting::bubble_sort(values);
    REQUIRE(values.empty());
}
TEST_CASE("bubble_sort: single element", "[lab1][bubble_sort]") {
    std::vector<int> values{42};
    sorting::bubble_sort(values);
    REQUIRE(values == std::vector<int>{42});
}
TEST_CASE("bubble_sort: already sorted", "[lab1][bubble_sort]") {
    std::vector<int> values{-3, -1, 0, 2, 8};
    const auto expected = values;
    sorting::bubble_sort(values);
    REQUIRE(values == expected);
}
TEST_CASE("bubble_sort: reverse order", "[lab1][bubble_sort]") {
    std::vector<int> values{8, 2, 0, -1, -3};
    sorting::bubble_sort(values);
    REQUIRE(values == std::vector<int>{-3, -1, 0, 2, 8});
}
TEST_CASE("bubble_sort: duplicates and boundary examples", "[lab1][bubble_sort]") {
    check_examples([](auto& values) { sorting::bubble_sort(values); });
}
TEST_CASE("bubble_sort: double precision", "[lab1][bubble_sort]") {
    std::vector<double> values{3.141592653589793, -0.125, 1.2345678901234567, 0.0, -0.125};
    auto expected = values;
    std::sort(expected.begin(), expected.end());
    sorting::bubble_sort(values);
    REQUIRE(values == expected);
}
TEST_CASE("bubble_sort: descending comparator", "[lab1][bubble_sort]") {
    std::vector<int> values{3, -2, 0, 3, 7, 1};
    auto expected = values;
    std::sort(expected.begin(), expected.end(), std::greater<int>{});
    sorting::bubble_sort(values, std::greater<int>{});
    REQUIRE(values == expected);
}
TEST_CASE("bubble_sort: randomized reference comparison", "[lab1][bubble_sort]") {
    check_random([](auto& values) { sorting::bubble_sort(values); }, 40);
}

TEST_CASE("bubble_sort: generic string type", "[lab1][bubble_sort]") {
    std::vector<std::string> values{"pear", "apple", "banana", "apple"};
    sorting::bubble_sort(values);
    REQUIRE(values == std::vector<std::string>{"apple", "apple", "banana", "pear"});
}

TEST_CASE("bubble_sort: stable ordering of equal keys", "[lab1][bubble_sort]") {
    std::vector<Record> values{{2, 0}, {1, 1}, {2, 2}, {1, 3}, {2, 4}};
    sorting::bubble_sort(values, [](const Record& a, const Record& b) { return a.key < b.key; });
    const std::vector<int> expected{1, 3, 0, 2, 4};
    for (std::size_t i = 0; i < values.size(); ++i)
        REQUIRE(values[i].original_position == expected[i]);
}
