#include "detail/file_sort_support.h"
#include <catch2/catch.hpp>
#include <functional>

namespace file = sorting::file_detail;

TEST_CASE("External merge: unequal run lengths and leftover run", "[lab4][merge]") {
    file::TemporaryDirectory temporary;
    const auto left = temporary.file("left.txt"), right = temporary.file("right.txt");
    const auto output = temporary.file("output.txt");
    { std::ofstream stream(left); stream << "1\n4\n9\n\n-3\n8\n\n100\n\n"; }
    { std::ofstream stream(right); stream << "2\n3\n\n0\n5\n7\n\n"; }
    auto less = std::less<int>{};
    REQUIRE(file::merge_runs<int>(left, right, {output}, less) == 3);
    REQUIRE(file::read_values<int>(output) == std::vector<int>{1, 2, 3, 4, 9, -3, 0, 5, 7, 8, 100});
}

TEST_CASE("External merge: alternating outputs retain run boundaries", "[lab4][merge]") {
    file::TemporaryDirectory temporary;
    const auto left = temporary.file("left.txt"), right = temporary.file("right.txt");
    const auto a = temporary.file("a.txt"), b = temporary.file("b.txt");
    const auto result = temporary.file("result.txt");
    { std::ofstream stream(left); stream << "1\n7\n\n3\n8\n\n"; }
    { std::ofstream stream(right); stream << "2\n6\n\n4\n5\n\n"; }
    auto less = std::less<int>{};
    REQUIRE(file::merge_runs<int>(left, right, {a, b}, less) == 2);
    REQUIRE(file::merge_runs<int>(a, b, {result}, less) == 1);
    REQUIRE(file::read_values<int>(result) == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});
}

TEST_CASE("External merge: empty file and duplicate records", "[lab4][merge]") {
    file::TemporaryDirectory temporary;
    const auto left = temporary.file("left.txt"), right = temporary.file("right.txt");
    const auto result = temporary.file("result.txt");
    { std::ofstream stream(left); stream << "-1\n2\n2\n\n"; }
    { std::ofstream stream(right); }
    auto less = std::less<int>{};
    REQUIRE(file::merge_runs<int>(left, right, {result}, less) == 1);
    REQUIRE(file::read_values<int>(result) == std::vector<int>{-1, 2, 2});
}

TEST_CASE("Natural split: maximal nondecreasing runs", "[lab4][natural]") {
    file::TemporaryDirectory temporary;
    const auto input = temporary.file("input.txt"), left = temporary.file("left.txt");
    const auto right = temporary.file("right.txt");
    file::write_values(input, std::vector<int>{1, 2, 2, 8, -1, 0, 9, 3, 4});
    auto less = std::less<int>{};
    REQUIRE(file::split_natural<int>(input, left, right, less) == 3);
    file::RunReader<int> reader(left);
    REQUIRE(reader.start_run());
    std::vector<int> first;
    while (reader.current) { first.push_back(*reader.current); reader.advance(); }
    REQUIRE(first == std::vector<int>{1, 2, 2, 8});
    REQUIRE(reader.start_run());
    std::vector<int> last;
    while (reader.current) { last.push_back(*reader.current); reader.advance(); }
    REQUIRE(last == std::vector<int>{3, 4});
    REQUIRE_FALSE(reader.start_run());
}

TEST_CASE("Temporary directory cleanup on successful return and exception", "[lab4][files]") {
    std::filesystem::path successful, failed;
    {
        file::TemporaryDirectory temporary;
        successful = temporary.path();
        file::write_values(temporary.file("data.txt"), std::vector<int>{1});
        REQUIRE(std::filesystem::exists(successful));
    }
    REQUIRE_FALSE(std::filesystem::exists(successful));
    try {
        file::TemporaryDirectory temporary;
        failed = temporary.path();
        file::write_values(temporary.file("data.txt"), std::vector<int>{1});
        throw std::runtime_error("test exception");
    } catch (const std::runtime_error&) {}
    REQUIRE_FALSE(std::filesystem::exists(failed));
}

TEST_CASE("File format: blank lines CRLF and exact double round trip", "[lab4][files]") {
    file::TemporaryDirectory temporary;
    const auto input = temporary.file("input.txt");
    { std::ofstream stream(input, std::ios::binary); stream << "\r\n 1.5 \r\n\t\r\n-0.125\r\n"; }
    REQUIRE(file::read_values<double>(input) == std::vector<double>{1.5, -0.125});
    const std::vector<double> values{std::numeric_limits<double>::max(),
                                    std::numeric_limits<double>::min(),
                                    std::numeric_limits<double>::denorm_min(),
                                    1.2345678901234567};
    file::write_values(input, values);
    REQUIRE(file::read_values<double>(input) == values);
}
