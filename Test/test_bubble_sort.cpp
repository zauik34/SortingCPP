#include <catch2/catch.hpp>
#include "bubble_sort.h"

TEST_CASE("bubbleSort: normal array", "[lab1][bubble_sort]") {
    std::vector<int> arr = {5, 3, 1, 4, 2};
    bubbleSort(arr);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("bubbleSort: empty array", "[lab1][bubble_sort]") {
    std::vector<int> arr = {};
    bubbleSort(arr);
    REQUIRE(arr == std::vector<int>{});
}

TEST_CASE("bubbleSort: one element", "[lab1][bubble_sort]") {
    std::vector<int> arr = {42};
    bubbleSort(arr);
    REQUIRE(arr == std::vector<int>{42});
}

TEST_CASE("bubbleSort: sorted array", "[lab1][bubble_sort]") {
    std::vector<int> arr = {-2, 0, 1, 3, 5};
    bubbleSort(arr);
    REQUIRE(arr == std::vector<int>{-2, 0, 1, 3, 5});
}

TEST_CASE("bubbleSort: reverse array", "[lab1][bubble_sort]") {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    bubbleSort(arr);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("bubbleSort: duplicates and negative numbers", "[lab1][bubble_sort]") {
    std::vector<int> arr = {3, -1, 3, 0, -1};
    bubbleSort(arr);
    REQUIRE(arr == std::vector<int>{-1, -1, 0, 3, 3});
}

TEST_CASE("bubbleSort: double array", "[lab1][bubble_sort]") {
    std::vector<double> arr = {3.14, -1.5, 2.71, 0.0};
    bubbleSort(arr);
    REQUIRE(arr == std::vector<double>{-1.5, 0.0, 2.71, 3.14});
}
