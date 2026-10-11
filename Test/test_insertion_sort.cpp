#include <catch2/catch.hpp>
#include "insertion_sort.h"

TEST_CASE("insertionSort: normal array", "[lab1][insertion_sort]") {
    std::vector<int> arr = {5, 3, 1, 4, 2};
    insertionSort(arr);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("insertionSort: empty array", "[lab1][insertion_sort]") {
    std::vector<int> arr = {};
    insertionSort(arr);
    REQUIRE(arr == std::vector<int>{});
}

TEST_CASE("insertionSort: one element", "[lab1][insertion_sort]") {
    std::vector<int> arr = {42};
    insertionSort(arr);
    REQUIRE(arr == std::vector<int>{42});
}

TEST_CASE("insertionSort: sorted array", "[lab1][insertion_sort]") {
    std::vector<int> arr = {-2, 0, 1, 3, 5};
    insertionSort(arr);
    REQUIRE(arr == std::vector<int>{-2, 0, 1, 3, 5});
}

TEST_CASE("insertionSort: reverse array", "[lab1][insertion_sort]") {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    insertionSort(arr);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("insertionSort: duplicates and negative numbers", "[lab1][insertion_sort]") {
    std::vector<int> arr = {3, -1, 3, 0, -1};
    insertionSort(arr);
    REQUIRE(arr == std::vector<int>{-1, -1, 0, 3, 3});
}

TEST_CASE("insertionSort: double array", "[lab1][insertion_sort]") {
    std::vector<double> arr = {3.14, -1.5, 2.71, 0.0};
    insertionSort(arr);
    REQUIRE(arr == std::vector<double>{-1.5, 0.0, 2.71, 3.14});
}
