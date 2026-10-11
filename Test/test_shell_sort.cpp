#include <catch2/catch.hpp>
#include "shell_sort.h"

TEST_CASE("shellSort: normal array", "[lab3][shell_sort]") {
    std::vector<int> arr = {5, 3, 1, 4, 2};
    shellSort(arr);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("shellSort: empty array", "[lab3][shell_sort]") {
    std::vector<int> arr = {};
    shellSort(arr);
    REQUIRE(arr == std::vector<int>{});
}

TEST_CASE("shellSort: one element", "[lab3][shell_sort]") {
    std::vector<int> arr = {42};
    shellSort(arr);
    REQUIRE(arr == std::vector<int>{42});
}

TEST_CASE("shellSort: sorted array", "[lab3][shell_sort]") {
    std::vector<int> arr = {-2, 0, 1, 3, 5};
    shellSort(arr);
    REQUIRE(arr == std::vector<int>{-2, 0, 1, 3, 5});
}

TEST_CASE("shellSort: reverse array", "[lab3][shell_sort]") {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    shellSort(arr);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("shellSort: duplicates and negative numbers", "[lab3][shell_sort]") {
    std::vector<int> arr = {3, -1, 3, 0, -1};
    shellSort(arr);
    REQUIRE(arr == std::vector<int>{-1, -1, 0, 3, 3});
}

TEST_CASE("shellSort: double array", "[lab3][shell_sort]") {
    std::vector<double> arr = {3.14, -1.5, 2.71, 0.0};
    shellSort(arr);
    REQUIRE(arr == std::vector<double>{-1.5, 0.0, 2.71, 3.14});
}
