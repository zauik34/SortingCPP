#include "binary_insertion_sort.h"
#include "test_helpers.h"
#include <functional>
#include <string>

TEST_CASE("binary_insertion_sort: empty input", "[lab2][binary_insertion_sort]") {
    std::vector<int> values;
    sorting::binary_insertion_sort(values);
    REQUIRE(values.empty());
}
TEST_CASE("binary_insertion_sort: single element", "[lab2][binary_insertion_sort]") {
    std::vector<int> values{42};
    sorting::binary_insertion_sort(values);
    REQUIRE(values == std::vector<int>{42});
}
TEST_CASE("binary_insertion_sort: already sorted", "[lab2][binary_insertion_sort]") {
    std::vector<int> values{-3, -1, 0, 2, 8};
    const auto expected = values;
    sorting::binary_insertion_sort(values);
    REQUIRE(values == expected);
}
TEST_CASE("binary_insertion_sort: reverse order", "[lab2][binary_insertion_sort]") {
    std::vector<int> values{8, 2, 0, -1, -3};
    sorting::binary_insertion_sort(values);
    REQUIRE(values == std::vector<int>{-3, -1, 0, 2, 8});
}
TEST_CASE("binary_insertion_sort: duplicates and boundary examples", "[lab2][binary_insertion_sort]") {
    check_examples([](auto& values) { sorting::binary_insertion_sort(values); });
}
TEST_CASE("binary_insertion_sort: double precision", "[lab2][binary_insertion_sort]") {
    std::vector<double> values{3.141592653589793, -0.125, 1.2345678901234567, 0.0, -0.125};
    auto expected = values;
    std::sort(expected.begin(), expected.end());
    sorting::binary_insertion_sort(values);
    REQUIRE(values == expected);
}
TEST_CASE("binary_insertion_sort: descending comparator", "[lab2][binary_insertion_sort]") {
    std::vector<int> values{3, -2, 0, 3, 7, 1};
    auto expected = values;
    std::sort(expected.begin(), expected.end(), std::greater<int>{});
    sorting::binary_insertion_sort(values, std::greater<int>{});
    REQUIRE(values == expected);
}
TEST_CASE("binary_insertion_sort: randomized reference comparison", "[lab2][binary_insertion_sort]") {
    check_random([](auto& values) { sorting::binary_insertion_sort(values); }, 40);
}

TEST_CASE("binary_insertion_sort: generic string type", "[lab2][binary_insertion_sort]") {
    std::vector<std::string> values{"pear", "apple", "banana", "apple"};
    sorting::binary_insertion_sort(values);
    REQUIRE(values == std::vector<std::string>{"apple", "apple", "banana", "pear"});
}

TEST_CASE("binary_insertion_sort: stable ordering of equal keys", "[lab2][binary_insertion_sort]") {
    std::vector<Record> values{{2, 0}, {1, 1}, {2, 2}, {1, 3}, {2, 4}};
    sorting::binary_insertion_sort(values, [](const Record& a, const Record& b) { return a.key < b.key; });
    const std::vector<int> expected{1, 3, 0, 2, 4};
    for (std::size_t i = 0; i < values.size(); ++i)
        REQUIRE(values[i].original_position == expected[i]);
}
