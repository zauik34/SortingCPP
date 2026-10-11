#include <catch2/catch.hpp>
#include "optimized_bubble_sort.h"

TEST_CASE("optimizedBubbleSort: normal array", "[lab1][optimized_bubble_sort]") {
    std::vector<int> arr = {5, 3, 1, 4, 2};
    optimizedBubbleSort(arr);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("optimizedBubbleSort: empty array", "[lab1][optimized_bubble_sort]") {
    std::vector<int> arr = {};
    optimizedBubbleSort(arr);
    REQUIRE(arr == std::vector<int>{});
}

TEST_CASE("optimizedBubbleSort: one element", "[lab1][optimized_bubble_sort]") {
    std::vector<int> arr = {42};
    optimizedBubbleSort(arr);
    REQUIRE(arr == std::vector<int>{42});
}

TEST_CASE("optimizedBubbleSort: sorted array", "[lab1][optimized_bubble_sort]") {
    std::vector<int> arr = {-2, 0, 1, 3, 5};
    optimizedBubbleSort(arr);
    REQUIRE(arr == std::vector<int>{-2, 0, 1, 3, 5});
}

TEST_CASE("optimizedBubbleSort: reverse array", "[lab1][optimized_bubble_sort]") {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    optimizedBubbleSort(arr);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("optimizedBubbleSort: duplicates and negative numbers", "[lab1][optimized_bubble_sort]") {
    std::vector<int> arr = {3, -1, 3, 0, -1};
    optimizedBubbleSort(arr);
    REQUIRE(arr == std::vector<int>{-1, -1, 0, 3, 3});
}

TEST_CASE("optimizedBubbleSort: double array", "[lab1][optimized_bubble_sort]") {
    std::vector<double> arr = {3.14, -1.5, 2.71, 0.0};
    optimizedBubbleSort(arr);
    REQUIRE(arr == std::vector<double>{-1.5, 0.0, 2.71, 3.14});
}
