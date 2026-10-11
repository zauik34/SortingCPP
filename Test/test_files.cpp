#include <catch2/catch.hpp>
#include "file_helpers.h"
#include <sstream>

TEST_CASE("Merge two series of different lengths", "[lab4][files]") {
    std::stringstream left, right, result;
    for (int value : {1, 4, 9}) writeValue(left, value);
    for (int value : {2, 3}) writeValue(right, value);
    mergeSeries<int>(left, right, result, 3, 2);
    std::vector<int> arr;
    int value = 0;
    while (readValue(result, value)) arr.push_back(value);
    REQUIRE(arr == std::vector<int>{1, 2, 3, 4, 9});
}

TEST_CASE("Merge does not consume the next series", "[lab4][files]") {
    std::stringstream left, right, result;
    for (int value : {1, 4, 100}) writeValue(left, value);
    for (int value : {2, 3, 200}) writeValue(right, value);
    mergeSeries<int>(left, right, result, 2, 2);
    int next = 0;
    REQUIRE(readValue(left, next));
    REQUIRE(next == 100);
    REQUIRE(readValue(right, next));
    REQUIRE(next == 200);
}

TEST_CASE("Double values survive a binary file round trip", "[lab4][files]") {
    const std::string filename = "test_file.bin";
    std::vector<double> arr = {3.141592653589793, -0.125, 1.2345678901234567};
    writeVectorToFile(filename, arr);
    REQUIRE(readVectorFromFile<double>(filename) == arr);
    REQUIRE(fileElementCount<double>(filename) == arr.size());
    std::remove(filename.c_str());
}

TEST_CASE("An incomplete binary record is rejected", "[lab4][files]") {
    const std::string filename = "test_incomplete.bin";
    { std::ofstream out(filename, std::ios::binary); out.put('x'); }
    REQUIRE_THROWS(fileElementCount<int>(filename));
    REQUIRE_THROWS(readVectorFromFile<int>(filename));
    std::remove(filename.c_str());
}
