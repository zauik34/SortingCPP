#include <catch2/catch.hpp>
#include "quick_sort.h"

TEST_CASE("quickSort: normal array", "[lab3][quick_sort]") {
    std::vector<int> arr = {5, 3, 1, 4, 2};
    quickSort(arr);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("quickSort: empty array", "[lab3][quick_sort]") {
    std::vector<int> arr = {};
    quickSort(arr);
    REQUIRE(arr == std::vector<int>{});
}

TEST_CASE("quickSort: one element", "[lab3][quick_sort]") {
    std::vector<int> arr = {42};
    quickSort(arr);
    REQUIRE(arr == std::vector<int>{42});
}

TEST_CASE("quickSort: sorted array", "[lab3][quick_sort]") {
    std::vector<int> arr = {-2, 0, 1, 3, 5};
    quickSort(arr);
    REQUIRE(arr == std::vector<int>{-2, 0, 1, 3, 5});
}

TEST_CASE("quickSort: reverse array", "[lab3][quick_sort]") {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    quickSort(arr);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("quickSort: duplicates and negative numbers", "[lab3][quick_sort]") {
    std::vector<int> arr = {3, -1, 3, 0, -1};
    quickSort(arr);
    REQUIRE(arr == std::vector<int>{-1, -1, 0, 3, 3});
}

TEST_CASE("quickSort: double array", "[lab3][quick_sort]") {
    std::vector<double> arr = {3.14, -1.5, 2.71, 0.0};
    quickSort(arr);
    REQUIRE(arr == std::vector<double>{-1.5, 0.0, 2.71, 3.14});
}
