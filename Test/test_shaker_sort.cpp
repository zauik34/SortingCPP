#include <catch2/catch.hpp>
#include "shaker_sort.h"

// Индивидуальное задание: вариант 9.
TEST_CASE("shakerSort: variant 9", "[lab2][shaker_sort][variant9]") {
    std::vector<int> arr = {7, 17, 9, 3, 13, 1, 16, 10};
    shakerSort(arr);
    REQUIRE(arr == std::vector<int>{1, 3, 7, 9, 10, 13, 16, 17});
}

TEST_CASE("shakerSort: empty array", "[lab2][shaker_sort]") {
    std::vector<int> arr = {};
    shakerSort(arr);
    REQUIRE(arr == std::vector<int>{});
}

TEST_CASE("shakerSort: one element", "[lab2][shaker_sort]") {
    std::vector<int> arr = {42};
    shakerSort(arr);
    REQUIRE(arr == std::vector<int>{42});
}

TEST_CASE("shakerSort: sorted array", "[lab2][shaker_sort]") {
    std::vector<int> arr = {-2, 0, 1, 3, 5};
    shakerSort(arr);
    REQUIRE(arr == std::vector<int>{-2, 0, 1, 3, 5});
}

TEST_CASE("shakerSort: reverse array", "[lab2][shaker_sort]") {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    shakerSort(arr);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("shakerSort: duplicates and negative numbers", "[lab2][shaker_sort]") {
    std::vector<int> arr = {3, -1, 3, 0, -1};
    shakerSort(arr);
    REQUIRE(arr == std::vector<int>{-1, -1, 0, 3, 3});
}

TEST_CASE("shakerSort: double array", "[lab2][shaker_sort]") {
    std::vector<double> arr = {3.14, -1.5, 2.71, 0.0};
    shakerSort(arr);
    REQUIRE(arr == std::vector<double>{-1.5, 0.0, 2.71, 3.14});
}
