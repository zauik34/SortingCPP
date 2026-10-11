#include <catch2/catch.hpp>
#include "exchange_sort.h"

// Индивидуальное задание: вариант 9.
TEST_CASE("exchangeSort: variant 9", "[lab1][exchange_sort][variant9]") {
    std::vector<int> arr = {7, 17, 9, 3, 13, 1, 16, 10};
    exchangeSort(arr);
    REQUIRE(arr == std::vector<int>{1, 3, 7, 9, 10, 13, 16, 17});
}

TEST_CASE("exchangeSort: empty array", "[lab1][exchange_sort]") {
    std::vector<int> arr = {};
    exchangeSort(arr);
    REQUIRE(arr == std::vector<int>{});
}

TEST_CASE("exchangeSort: one element", "[lab1][exchange_sort]") {
    std::vector<int> arr = {42};
    exchangeSort(arr);
    REQUIRE(arr == std::vector<int>{42});
}

TEST_CASE("exchangeSort: sorted array", "[lab1][exchange_sort]") {
    std::vector<int> arr = {-2, 0, 1, 3, 5};
    exchangeSort(arr);
    REQUIRE(arr == std::vector<int>{-2, 0, 1, 3, 5});
}

TEST_CASE("exchangeSort: reverse array", "[lab1][exchange_sort]") {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    exchangeSort(arr);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("exchangeSort: duplicates and negative numbers", "[lab1][exchange_sort]") {
    std::vector<int> arr = {3, -1, 3, 0, -1};
    exchangeSort(arr);
    REQUIRE(arr == std::vector<int>{-1, -1, 0, 3, 3});
}

TEST_CASE("exchangeSort: double array", "[lab1][exchange_sort]") {
    std::vector<double> arr = {3.14, -1.5, 2.71, 0.0};
    exchangeSort(arr);
    REQUIRE(arr == std::vector<double>{-1.5, 0.0, 2.71, 3.14});
}
