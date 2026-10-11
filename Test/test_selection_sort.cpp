#include <catch2/catch.hpp>
#include "selection_sort.h"

TEST_CASE("selectionSort: normal array", "[lab1][selection_sort]") {
    std::vector<int> arr = {5, 3, 1, 4, 2};
    selectionSort(arr);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("selectionSort: empty array", "[lab1][selection_sort]") {
    std::vector<int> arr = {};
    selectionSort(arr);
    REQUIRE(arr == std::vector<int>{});
}

TEST_CASE("selectionSort: one element", "[lab1][selection_sort]") {
    std::vector<int> arr = {42};
    selectionSort(arr);
    REQUIRE(arr == std::vector<int>{42});
}

TEST_CASE("selectionSort: sorted array", "[lab1][selection_sort]") {
    std::vector<int> arr = {-2, 0, 1, 3, 5};
    selectionSort(arr);
    REQUIRE(arr == std::vector<int>{-2, 0, 1, 3, 5});
}

TEST_CASE("selectionSort: reverse array", "[lab1][selection_sort]") {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    selectionSort(arr);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("selectionSort: duplicates and negative numbers", "[lab1][selection_sort]") {
    std::vector<int> arr = {3, -1, 3, 0, -1};
    selectionSort(arr);
    REQUIRE(arr == std::vector<int>{-1, -1, 0, 3, 3});
}

TEST_CASE("selectionSort: double array", "[lab1][selection_sort]") {
    std::vector<double> arr = {3.14, -1.5, 2.71, 0.0};
    selectionSort(arr);
    REQUIRE(arr == std::vector<double>{-1.5, 0.0, 2.71, 3.14});
}
