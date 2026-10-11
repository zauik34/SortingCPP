#include "one_phase_merge_sort.h"
#include "test_helpers.h"
#include <functional>
#include <string>

TEST_CASE("one_phase_merge_sort: empty input", "[lab4][one_phase_merge_sort]") {
    std::vector<int> values;
    sorting::one_phase_merge_sort(values);
    REQUIRE(values.empty());
}
TEST_CASE("one_phase_merge_sort: single element", "[lab4][one_phase_merge_sort]") {
    std::vector<int> values{42};
    sorting::one_phase_merge_sort(values);
    REQUIRE(values == std::vector<int>{42});
}
TEST_CASE("one_phase_merge_sort: already sorted", "[lab4][one_phase_merge_sort]") {
    std::vector<int> values{-3, -1, 0, 2, 8};
    const auto expected = values;
    sorting::one_phase_merge_sort(values);
    REQUIRE(values == expected);
}
TEST_CASE("one_phase_merge_sort: reverse order", "[lab4][one_phase_merge_sort]") {
    std::vector<int> values{8, 2, 0, -1, -3};
    sorting::one_phase_merge_sort(values);
    REQUIRE(values == std::vector<int>{-3, -1, 0, 2, 8});
}
TEST_CASE("one_phase_merge_sort: duplicates and boundary examples", "[lab4][one_phase_merge_sort]") {
    check_examples([](auto& values) { sorting::one_phase_merge_sort(values); });
}
TEST_CASE("one_phase_merge_sort: double precision", "[lab4][one_phase_merge_sort]") {
    std::vector<double> values{3.141592653589793, -0.125, 1.2345678901234567, 0.0, -0.125};
    auto expected = values;
    std::sort(expected.begin(), expected.end());
    sorting::one_phase_merge_sort(values);
    REQUIRE(values == expected);
}
TEST_CASE("one_phase_merge_sort: descending comparator", "[lab4][one_phase_merge_sort]") {
    std::vector<int> values{3, -2, 0, 3, 7, 1};
    auto expected = values;
    std::sort(expected.begin(), expected.end(), std::greater<int>{});
    sorting::one_phase_merge_sort(values, std::greater<int>{});
    REQUIRE(values == expected);
}
TEST_CASE("one_phase_merge_sort: randomized reference comparison", "[lab4][one_phase_merge_sort]") {
    check_random([](auto& values) { sorting::one_phase_merge_sort(values); }, 12);
}

TEST_CASE("one_phase_merge_sort: file cases and source preservation", "[lab4][one_phase_merge_sort]") {
    sorting::file_detail::TemporaryDirectory temporary;
    const auto input = temporary.file("input.txt"), output = temporary.file("output.txt");
    for (const auto& example : std::vector<std::vector<int>>{
             {}, {42}, {1, 2, 3}, {5, 4, 3, 2, 1},
             {1, 4, 9, 2, 3, 8, -1, 0, 7, 7}, {3, 3, 3}, {2, 1}}) {
        sorting::file_detail::write_values(input, example);
        sorting::one_phase_merge_sort<int>(input, output);
        auto expected = example;
        std::sort(expected.begin(), expected.end());
        REQUIRE(sorting::file_detail::read_values<int>(output) == expected);
        REQUIRE(sorting::file_detail::read_values<int>(input) == example);
    }
}
TEST_CASE("one_phase_merge_sort: file double and descending order", "[lab4][one_phase_merge_sort]") {
    sorting::file_detail::TemporaryDirectory temporary;
    const auto input = temporary.file("input.txt"), output = temporary.file("output.txt");
    std::vector<double> values{1.2345678901234567, -0.25, 9.125, 1.2345678901234567, 0.0};
    sorting::file_detail::write_values(input, values);
    sorting::one_phase_merge_sort<double>(input, output, std::greater<double>{});
    std::sort(values.begin(), values.end(), std::greater<double>{});
    REQUIRE(sorting::file_detail::read_values<double>(output) == values);
}
TEST_CASE("one_phase_merge_sort: same input and output path", "[lab4][one_phase_merge_sort]") {
    sorting::file_detail::TemporaryDirectory temporary;
    const auto input = temporary.file("input.txt");
    sorting::file_detail::write_values(input, std::vector<int>{4, 1, 3, 2});
    sorting::one_phase_merge_sort<int>(input, input);
    REQUIRE(sorting::file_detail::read_values<int>(input) == std::vector<int>{1, 2, 3, 4});
}
TEST_CASE("one_phase_merge_sort: missing input preserves output", "[lab4][one_phase_merge_sort]") {
    sorting::file_detail::TemporaryDirectory temporary;
    const auto input = temporary.file("missing.txt"), output = temporary.file("output.txt");
    sorting::file_detail::write_values(output, std::vector<int>{99});
    REQUIRE_THROWS(sorting::one_phase_merge_sort<int>(input, output));
    REQUIRE(sorting::file_detail::read_values<int>(output) == std::vector<int>{99});
}
TEST_CASE("one_phase_merge_sort: malformed input preserves output", "[lab4][one_phase_merge_sort]") {
    sorting::file_detail::TemporaryDirectory temporary;
    const auto input = temporary.file("input.txt"), output = temporary.file("output.txt");
    for (const auto& text : {"3\ninvalid\n1\n", "3\n1junk\n", "2147483648\n"}) {
        { std::ofstream stream(input); stream << text; }
        sorting::file_detail::write_values(output, std::vector<int>{99});
        REQUIRE_THROWS(sorting::one_phase_merge_sort<int>(input, output));
        REQUIRE(sorting::file_detail::read_values<int>(output) == std::vector<int>{99});
    }
}
TEST_CASE("one_phase_merge_sort: missing destination directory", "[lab4][one_phase_merge_sort]") {
    sorting::file_detail::TemporaryDirectory temporary;
    const auto input = temporary.file("input.txt");
    sorting::file_detail::write_values(input, std::vector<int>{2, 1});
    REQUIRE_THROWS(sorting::one_phase_merge_sort<int>(input, temporary.file("missing/output.txt")));
    REQUIRE(sorting::file_detail::read_values<int>(input) == std::vector<int>{2, 1});
}
TEST_CASE("one_phase_merge_sort: non-finite double rejected", "[lab4][one_phase_merge_sort]") {
    std::vector<double> values{1.0, std::numeric_limits<double>::infinity()};
    REQUIRE_THROWS(sorting::one_phase_merge_sort(values));
    REQUIRE(values[0] == 1.0);
    REQUIRE(std::isinf(values[1]));
}
