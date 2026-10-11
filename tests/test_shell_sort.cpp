#include "shell_sort.h"
#include "test_helpers.h"
#include <functional>
#include <string>

TEST_CASE("shell_sort: empty input", "[lab3][shell_sort]") {
    std::vector<int> values;
    sorting::shell_sort(values);
    REQUIRE(values.empty());
}
TEST_CASE("shell_sort: single element", "[lab3][shell_sort]") {
    std::vector<int> values{42};
    sorting::shell_sort(values);
    REQUIRE(values == std::vector<int>{42});
}
TEST_CASE("shell_sort: already sorted", "[lab3][shell_sort]") {
    std::vector<int> values{-3, -1, 0, 2, 8};
    const auto expected = values;
    sorting::shell_sort(values);
    REQUIRE(values == expected);
}
TEST_CASE("shell_sort: reverse order", "[lab3][shell_sort]") {
    std::vector<int> values{8, 2, 0, -1, -3};
    sorting::shell_sort(values);
    REQUIRE(values == std::vector<int>{-3, -1, 0, 2, 8});
}
TEST_CASE("shell_sort: duplicates and boundary examples", "[lab3][shell_sort]") {
    check_examples([](auto& values) { sorting::shell_sort(values); });
}
TEST_CASE("shell_sort: double precision", "[lab3][shell_sort]") {
    std::vector<double> values{3.141592653589793, -0.125, 1.2345678901234567, 0.0, -0.125};
    auto expected = values;
    std::sort(expected.begin(), expected.end());
    sorting::shell_sort(values);
    REQUIRE(values == expected);
}
TEST_CASE("shell_sort: descending comparator", "[lab3][shell_sort]") {
    std::vector<int> values{3, -2, 0, 3, 7, 1};
    auto expected = values;
    std::sort(expected.begin(), expected.end(), std::greater<int>{});
    sorting::shell_sort(values, std::greater<int>{});
    REQUIRE(values == expected);
}
TEST_CASE("shell_sort: randomized reference comparison", "[lab3][shell_sort]") {
    check_random([](auto& values) { sorting::shell_sort(values); }, 40);
}

TEST_CASE("shell_sort: generic string type", "[lab3][shell_sort]") {
    std::vector<std::string> values{"pear", "apple", "banana", "apple"};
    sorting::shell_sort(values);
    REQUIRE(values == std::vector<std::string>{"apple", "apple", "banana", "pear"});
}
