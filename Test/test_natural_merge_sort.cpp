#include <catch2/catch.hpp>
#include "natural_merge_sort.h"

// Индивидуальное задание: вариант 9.
TEST_CASE("naturalMergeSort: variant 9", "[lab4][natural_merge_sort][variant9]") {
    std::vector<int> arr = {7, 17, 9, 3, 13, 1, 16, 10};
    naturalMergeSort(arr);
    REQUIRE(arr == std::vector<int>{1, 3, 7, 9, 10, 13, 16, 17});
}

TEST_CASE("naturalMergeSort: empty array", "[lab4][natural_merge_sort]") {
    std::vector<int> arr = {};
    naturalMergeSort(arr);
    REQUIRE(arr == std::vector<int>{});
}

TEST_CASE("naturalMergeSort: one element", "[lab4][natural_merge_sort]") {
    std::vector<int> arr = {42};
    naturalMergeSort(arr);
    REQUIRE(arr == std::vector<int>{42});
}

TEST_CASE("naturalMergeSort: sorted array", "[lab4][natural_merge_sort]") {
    std::vector<int> arr = {-2, 0, 1, 3, 5};
    naturalMergeSort(arr);
    REQUIRE(arr == std::vector<int>{-2, 0, 1, 3, 5});
}

TEST_CASE("naturalMergeSort: reverse array", "[lab4][natural_merge_sort]") {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    naturalMergeSort(arr);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("naturalMergeSort: duplicates and negative numbers", "[lab4][natural_merge_sort]") {
    std::vector<int> arr = {3, -1, 3, 0, -1};
    naturalMergeSort(arr);
    REQUIRE(arr == std::vector<int>{-1, -1, 0, 3, 3});
}

TEST_CASE("naturalMergeSort: double array", "[lab4][natural_merge_sort]") {
    std::vector<double> arr = {3.14, -1.5, 2.71, 0.0};
    naturalMergeSort(arr);
    REQUIRE(arr == std::vector<double>{-1.5, 0.0, 2.71, 3.14});
}

TEST_CASE("naturalMergeSort: sorting a file with uneven series", "[lab4][natural_merge_sort]") {
    const std::string filename = "test_natural_merge_sort.bin";
    writeVectorToFile(filename, std::vector<int>{1, 4, 9, 2, 3, 8, -1, 0, 7});
    naturalMergeSortFile<int>(filename);
    REQUIRE(readVectorFromFile<int>(filename) == std::vector<int>{-1, 0, 1, 2, 3, 4, 7, 8, 9});
    std::remove(filename.c_str());
}

TEST_CASE("naturalMergeSort: empty and single element files", "[lab4][natural_merge_sort]") {
    const std::string filename = "test_natural_merge_sort.bin";
    writeVectorToFile(filename, std::vector<double>{});
    naturalMergeSortFile<double>(filename);
    REQUIRE(readVectorFromFile<double>(filename).empty());
    writeVectorToFile(filename, std::vector<double>{2.5});
    naturalMergeSortFile<double>(filename);
    REQUIRE(readVectorFromFile<double>(filename) == std::vector<double>{2.5});
    std::remove(filename.c_str());
}

TEST_CASE("naturalMergeSort: variant 9 file", "[lab4][natural_merge_sort][variant9]") {
    const std::string filename = "variant9_test_natural_merge_sort.bin";
    writeVectorToFile(filename, std::vector<int>{7, 17, 9, 3, 13, 1, 16, 10});
    naturalMergeSortFile<int>(filename);
    REQUIRE(readVectorFromFile<int>(filename) == std::vector<int>{1, 3, 7, 9, 10, 13, 16, 17});
    std::remove(filename.c_str());
}
