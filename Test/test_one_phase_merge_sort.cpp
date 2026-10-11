#include <catch2/catch.hpp>
#include "one_phase_merge_sort.h"

// Индивидуальное задание: вариант 9.
TEST_CASE("onePhaseMergeSort: variant 9", "[lab4][one_phase_merge_sort][variant9]") {
    std::vector<int> arr = {7, 17, 9, 3, 13, 1, 16, 10};
    onePhaseMergeSort(arr);
    REQUIRE(arr == std::vector<int>{1, 3, 7, 9, 10, 13, 16, 17});
}

TEST_CASE("onePhaseMergeSort: empty array", "[lab4][one_phase_merge_sort]") {
    std::vector<int> arr = {};
    onePhaseMergeSort(arr);
    REQUIRE(arr == std::vector<int>{});
}

TEST_CASE("onePhaseMergeSort: one element", "[lab4][one_phase_merge_sort]") {
    std::vector<int> arr = {42};
    onePhaseMergeSort(arr);
    REQUIRE(arr == std::vector<int>{42});
}

TEST_CASE("onePhaseMergeSort: sorted array", "[lab4][one_phase_merge_sort]") {
    std::vector<int> arr = {-2, 0, 1, 3, 5};
    onePhaseMergeSort(arr);
    REQUIRE(arr == std::vector<int>{-2, 0, 1, 3, 5});
}

TEST_CASE("onePhaseMergeSort: reverse array", "[lab4][one_phase_merge_sort]") {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    onePhaseMergeSort(arr);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("onePhaseMergeSort: duplicates and negative numbers", "[lab4][one_phase_merge_sort]") {
    std::vector<int> arr = {3, -1, 3, 0, -1};
    onePhaseMergeSort(arr);
    REQUIRE(arr == std::vector<int>{-1, -1, 0, 3, 3});
}

TEST_CASE("onePhaseMergeSort: double array", "[lab4][one_phase_merge_sort]") {
    std::vector<double> arr = {3.14, -1.5, 2.71, 0.0};
    onePhaseMergeSort(arr);
    REQUIRE(arr == std::vector<double>{-1.5, 0.0, 2.71, 3.14});
}

TEST_CASE("onePhaseMergeSort: sorting a file with uneven series", "[lab4][one_phase_merge_sort]") {
    const std::string filename = "test_one_phase_merge_sort.bin";
    writeVectorToFile(filename, std::vector<int>{1, 4, 9, 2, 3, 8, -1, 0, 7});
    onePhaseMergeSortFile<int>(filename);
    REQUIRE(readVectorFromFile<int>(filename) == std::vector<int>{-1, 0, 1, 2, 3, 4, 7, 8, 9});
    std::remove(filename.c_str());
}

TEST_CASE("onePhaseMergeSort: empty and single element files", "[lab4][one_phase_merge_sort]") {
    const std::string filename = "test_one_phase_merge_sort.bin";
    writeVectorToFile(filename, std::vector<double>{});
    onePhaseMergeSortFile<double>(filename);
    REQUIRE(readVectorFromFile<double>(filename).empty());
    writeVectorToFile(filename, std::vector<double>{2.5});
    onePhaseMergeSortFile<double>(filename);
    REQUIRE(readVectorFromFile<double>(filename) == std::vector<double>{2.5});
    std::remove(filename.c_str());
}

TEST_CASE("onePhaseMergeSort: variant 9 file", "[lab4][one_phase_merge_sort][variant9]") {
    const std::string filename = "variant9_test_one_phase_merge_sort.bin";
    writeVectorToFile(filename, std::vector<int>{7, 17, 9, 3, 13, 1, 16, 10});
    onePhaseMergeSortFile<int>(filename);
    REQUIRE(readVectorFromFile<int>(filename) == std::vector<int>{1, 3, 7, 9, 10, 13, 16, 17});
    std::remove(filename.c_str());
}
