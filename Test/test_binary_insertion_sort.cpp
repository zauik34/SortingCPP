#include <catch2/catch.hpp>
#include "binary_insertion_sort.h"

// Индивидуальное задание: вариант 9.
TEST_CASE("binaryInsertionSort: variant 9", "[lab2][binary_insertion_sort][variant9]") {
    std::vector<int> arr = {7, 17, 9, 3, 13, 1, 16, 10};
    binaryInsertionSort(arr);
    REQUIRE(arr == std::vector<int>{1, 3, 7, 9, 10, 13, 16, 17});
}

TEST_CASE("binaryInsertionSort: empty array", "[lab2][binary_insertion_sort]") {
    std::vector<int> arr = {};
    binaryInsertionSort(arr);
    REQUIRE(arr == std::vector<int>{});
}

TEST_CASE("binaryInsertionSort: one element", "[lab2][binary_insertion_sort]") {
    std::vector<int> arr = {42};
    binaryInsertionSort(arr);
    REQUIRE(arr == std::vector<int>{42});
}

TEST_CASE("binaryInsertionSort: sorted array", "[lab2][binary_insertion_sort]") {
    std::vector<int> arr = {-2, 0, 1, 3, 5};
    binaryInsertionSort(arr);
    REQUIRE(arr == std::vector<int>{-2, 0, 1, 3, 5});
}

TEST_CASE("binaryInsertionSort: reverse array", "[lab2][binary_insertion_sort]") {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    binaryInsertionSort(arr);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("binaryInsertionSort: duplicates and negative numbers", "[lab2][binary_insertion_sort]") {
    std::vector<int> arr = {3, -1, 3, 0, -1};
    binaryInsertionSort(arr);
    REQUIRE(arr == std::vector<int>{-1, -1, 0, 3, 3});
}

TEST_CASE("binaryInsertionSort: double array", "[lab2][binary_insertion_sort]") {
    std::vector<double> arr = {3.14, -1.5, 2.71, 0.0};
    binaryInsertionSort(arr);
    REQUIRE(arr == std::vector<double>{-1.5, 0.0, 2.71, 3.14});
}
