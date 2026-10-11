#pragma once
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <limits>
#include <locale>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace sorting::file_detail {
namespace fs = std::filesystem;

// Every call owns its files. Cleanup also runs when parsing/IO throws.
class TemporaryDirectory {
    fs::path directory_;
public:
    explicit TemporaryDirectory(const fs::path& parent = fs::temp_directory_path()) {
        static std::atomic<unsigned long long> sequence{0};
        const auto tick = std::chrono::steady_clock::now().time_since_epoch().count();
        for (unsigned attempt = 0; attempt < 100; ++attempt) {
            const auto candidate = parent / ("sorting-labs-" + std::to_string(tick)
                                              + "-" + std::to_string(sequence++));
            std::error_code error;
            if (fs::create_directory(candidate, error)) { directory_ = candidate; return; }
            if (error && error != std::errc::file_exists)
                throw fs::filesystem_error("Cannot create temporary directory", candidate, error);
        }
        throw std::runtime_error("Cannot allocate temporary directory");
    }
    TemporaryDirectory(const TemporaryDirectory&) = delete;
    TemporaryDirectory& operator=(const TemporaryDirectory&) = delete;
    ~TemporaryDirectory() { std::error_code ignored; fs::remove_all(directory_, ignored); }
    fs::path file(const std::string& name) const { return directory_ / name; }
    const fs::path& path() const { return directory_; }
};

inline std::ifstream open_input(const fs::path& path) {
    std::ifstream stream(path);
    if (!stream) throw std::runtime_error("Cannot open input file: " + path.string());
    stream.imbue(std::locale::classic());
    stream.exceptions(std::ios::badbit);
    return stream;
}

template <typename T>
std::ofstream open_output(const fs::path& path) {
    static_assert(std::is_arithmetic_v<T> && !std::is_same_v<T, bool>,
                  "External sorts support arithmetic values except bool");
    std::ofstream stream;
    stream.exceptions(std::ios::failbit | std::ios::badbit);
    stream.open(path, std::ios::trunc);
    stream.imbue(std::locale::classic());
    if constexpr (std::is_floating_point_v<T>)
        stream << std::setprecision(std::numeric_limits<T>::max_digits10);
    return stream;
}

inline bool blank(const std::string& line) {
    return line.find_first_not_of(" \t\r") == std::string::npos;
}

template <typename T>
T parse_value(const std::string& line) {
    std::istringstream parser(line);
    parser.imbue(std::locale::classic());
    T value{};
    if (!(parser >> value)) throw std::runtime_error("Invalid numeric record: " + line);
    parser >> std::ws;
    if (!parser.eof()) throw std::runtime_error("Extra data in numeric record: " + line);
    if constexpr (std::is_floating_point_v<T>)
        if (!std::isfinite(value)) throw std::runtime_error("Non-finite numeric record");
    return value;
}

template <typename T>
std::optional<T> read_flat_value(std::istream& input) {
    std::string line;
    while (std::getline(input, line))
        if (!blank(line)) return parse_value<T>(line);
    return std::nullopt;
}

// Temporary run files separate sorted runs by one blank line.
template <typename T>
class RunReader {
    std::ifstream input_;
public:
    std::optional<T> current;
    explicit RunReader(const fs::path& path) : input_(open_input(path)) {}
    void advance() {
        std::string line;
        current.reset();
        if (std::getline(input_, line) && !blank(line)) current = parse_value<T>(line);
    }
    bool start_run() { advance(); return current.has_value(); }
};

template <typename T>
std::size_t split_fixed(const fs::path& input_path, const fs::path& left_path,
                        const fs::path& right_path, std::size_t length) {
    if (length == 0) throw std::invalid_argument("Run length must be positive");
    auto input = open_input(input_path);
    auto left = open_output<T>(left_path), right = open_output<T>(right_path);
    std::array<std::ofstream*, 2> outputs{&left, &right};
    std::size_t runs = 0, in_run = 0;
    while (const auto value = read_flat_value<T>(input)) {
        if (in_run == 0) ++runs;
        auto& output = *outputs[(runs - 1) % 2];
        output << *value << '\n';
        if (++in_run == length) { output << '\n'; in_run = 0; }
    }
    if (in_run != 0) *outputs[(runs - 1) % 2] << '\n';
    left.close(); right.close();
    return runs;
}

template <typename T, typename Compare>
std::size_t split_natural(const fs::path& input_path, const fs::path& left_path,
                          const fs::path& right_path, Compare& less) {
    auto input = open_input(input_path);
    auto left = open_output<T>(left_path), right = open_output<T>(right_path);
    std::array<std::ofstream*, 2> outputs{&left, &right};
    std::optional<T> previous;
    std::size_t runs = 0;
    while (const auto value = read_flat_value<T>(input)) {
        if (!previous) ++runs;
        else if (less(*value, *previous)) {
            *outputs[(runs - 1) % 2] << '\n';
            ++runs;
        }
        *outputs[(runs - 1) % 2] << *value << '\n';
        previous = value;
    }
    if (previous) *outputs[(runs - 1) % 2] << '\n';
    left.close(); right.close();
    return runs;
}

// One output: flat file for two-phase merging. Two outputs: alternating
// delimited runs for the next pass of one-phase merging.
template <typename T, typename Compare>
std::size_t merge_runs(const fs::path& left_path, const fs::path& right_path,
                       const std::vector<fs::path>& destinations, Compare& less) {
    if (destinations.empty() || destinations.size() > 2)
        throw std::invalid_argument("Merge needs one or two destinations");
    RunReader<T> left(left_path), right(right_path);
    std::vector<std::ofstream> outputs;
    for (const auto& destination : destinations) outputs.push_back(open_output<T>(destination));
    std::size_t runs = 0;
    while (true) {
        const bool has_left = left.start_run(), has_right = right.start_run();
        if (!has_left && !has_right) break;
        auto& output = outputs[runs % outputs.size()];
        while (left.current || right.current) {
            // On equality take the left record first: merging is stable.
            if (!right.current || (left.current && !less(*right.current, *left.current))) {
                output << *left.current << '\n';
                left.advance();
            } else {
                output << *right.current << '\n';
                right.advance();
            }
        }
        if (outputs.size() == 2) output << '\n';
        ++runs;
    }
    for (auto& output : outputs) output.close();
    return runs;
}

template <typename T>
void flatten(const fs::path& input_path, const fs::path& output_path) {
    auto input = open_input(input_path);
    auto output = open_output<T>(output_path);
    while (const auto value = read_flat_value<T>(input)) output << *value << '\n';
    output.close();
}

template <typename T>
void write_values(const fs::path& path, const std::vector<T>& values) {
    auto output = open_output<T>(path);
    for (const auto& value : values) {
        if constexpr (std::is_floating_point_v<T>)
            if (!std::isfinite(value)) throw std::invalid_argument("Non-finite value");
        output << value << '\n';
    }
    output.close();
}

template <typename T>
std::vector<T> read_values(const fs::path& path) {
    auto input = open_input(path);
    std::vector<T> values;
    while (const auto value = read_flat_value<T>(input)) values.push_back(*value);
    return values;
}

enum class Method { two_phase, one_phase, natural };

template <typename T, typename Compare>
void sort_file(const fs::path& input, const fs::path& output, Method method, Compare less) {
    TemporaryDirectory temporary;
    const auto work = temporary.file("work.txt");
    const auto a = temporary.file("a.txt"), b = temporary.file("b.txt");
    // Input remains untouched until a complete result exists, even for input == output.
    fs::copy_file(input, work, fs::copy_options::overwrite_existing);
    fs::path result = work;
    if (method == Method::one_phase) {
        auto first = a, second = b;
        auto third = temporary.file("c.txt"), fourth = temporary.file("d.txt");
        std::size_t runs = split_fixed<T>(work, first, second, 1);
        while (runs > 1) {
            runs = merge_runs<T>(first, second, {third, fourth}, less);
            std::swap(first, third); std::swap(second, fourth);
        }
        result = temporary.file("result.txt");
        flatten<T>(first, result);
    } else {
        std::size_t length = 1;
        while (true) {
            const auto runs = method == Method::natural
                ? split_natural<T>(work, a, b, less)
                : split_fixed<T>(work, a, b, length);
            // Also normalizes/validates empty, singleton and already sorted inputs.
            const auto merged = merge_runs<T>(a, b, {work}, less);
            if (runs <= 1 || merged <= 1) break;
            if (method == Method::two_phase) {
                const auto maximum = std::numeric_limits<std::size_t>::max();
                length = length > maximum / 2 ? maximum : length * 2;
            }
        }
    }
    fs::copy_file(result, output, fs::copy_options::overwrite_existing);
}

template <typename T, typename Compare>
void sort_vector(std::vector<T>& values, Method method, Compare less) {
    TemporaryDirectory temporary;
    const auto input = temporary.file("input.txt"), output = temporary.file("output.txt");
    write_values(input, values);
    sort_file<T>(input, output, method, less);
    values = read_values<T>(output);
}
} // namespace sorting::file_detail
