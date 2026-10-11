#pragma once
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

// Бинарный файл содержит подряд значения T без разделителей.
// Один и тот же файл нужно читать тем типом, которым он был записан.
template <typename T>
bool readValue(std::istream& in, T& value) {
    static_assert(std::is_arithmetic_v<T>, "Binary files require numeric types");
    if (in.read(reinterpret_cast<char*>(&value), sizeof(T))) return true;
    if (!in.eof() || in.gcount() != 0) throw std::runtime_error("Cannot read record");
    return false;
}

template <typename T>
void writeValue(std::ostream& out, const T& value) {
    static_assert(std::is_arithmetic_v<T>, "Binary files require numeric types");
    out.write(reinterpret_cast<const char*>(&value), sizeof(T));
    if (!out) throw std::runtime_error("Cannot write record");
}

template <typename T>
void writeVectorToFile(const std::string& filename, const std::vector<T>& arr) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) throw std::runtime_error("Cannot open output file");
    for (const T& value : arr) writeValue(out, value);
    out.close();
    if (!out) throw std::runtime_error("Cannot close output file");
}

template <typename T>
std::vector<T> readVectorFromFile(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) throw std::runtime_error("Cannot open input file");
    std::vector<T> arr;
    T value{};
    while (readValue(in, value)) arr.push_back(value);
    return arr;
}

template <typename T>
std::size_t fileElementCount(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary | std::ios::ate);
    if (!in) throw std::runtime_error("Cannot open input file");
    const auto bytes = in.tellg();
    if (bytes < 0 || bytes % sizeof(T) != 0) throw std::runtime_error("Invalid file size");
    return static_cast<std::size_t>(bytes / sizeof(T));
}

// Сливаем ровно одну пару серий. Не читаем элементы следующей серии.
template <typename T>
void mergeSeries(std::istream& left, std::istream& right, std::ostream& out,
                 std::size_t leftCount, std::size_t rightCount) {
    T a{}, b{};
    if (leftCount > 0 && !readValue(left, a)) throw std::runtime_error("Missing left record");
    if (rightCount > 0 && !readValue(right, b)) throw std::runtime_error("Missing right record");
    while (leftCount > 0 || rightCount > 0) {
        if (rightCount == 0 || (leftCount > 0 && a <= b)) {
            writeValue(out, a);
            --leftCount;
            if (leftCount > 0 && !readValue(left, a)) throw std::runtime_error("Missing left record");
        } else {
            writeValue(out, b);
            --rightCount;
            if (rightCount > 0 && !readValue(right, b)) throw std::runtime_error("Missing right record");
        }
    }
}

// Распределяем серии заданной длины попеременно в два файла.
template <typename T>
void splitFixedFile(const std::string& input, const std::string& first,
                    const std::string& second, std::size_t length) {
    if (length == 0) throw std::runtime_error("Zero series length");
    std::ifstream in(input, std::ios::binary);
    std::ofstream out1(first, std::ios::binary), out2(second, std::ios::binary);
    if (!in || !out1 || !out2) throw std::runtime_error("Cannot open split files");
    T value{};
    std::size_t count = 0;
    bool toFirst = true;
    while (readValue(in, value)) {
        writeValue(toFirst ? out1 : out2, value);
        if (++count == length) { count = 0; toFirst = !toFirst; }
    }
    out1.close(); out2.close();
    if (!out1 || !out2) throw std::runtime_error("Cannot close split files");
}

// Если secondOutput пустой, всё пишем в один файл (двухфазная сортировка).
// Иначе результаты серий чередуются между двумя файлами (однофазная).
template <typename T>
void mergeFixedFiles(const std::string& first, const std::string& second,
                     const std::string& firstOutput, const std::string& secondOutput,
                     std::size_t length) {
    if (length == 0) throw std::runtime_error("Zero series length");
    std::size_t leftRemaining = fileElementCount<T>(first);
    std::size_t rightRemaining = fileElementCount<T>(second);
    std::ifstream left(first, std::ios::binary), right(second, std::ios::binary);
    std::ofstream out1(firstOutput, std::ios::binary), out2;
    if (!secondOutput.empty()) out2.open(secondOutput, std::ios::binary);
    if (!left || !right || !out1 || (!secondOutput.empty() && !out2))
        throw std::runtime_error("Cannot open merge files");
    bool toFirst = true;
    while (leftRemaining > 0 || rightRemaining > 0) {
        std::size_t leftCount = std::min(length, leftRemaining);
        std::size_t rightCount = std::min(length, rightRemaining);
        mergeSeries<T>(left, right, toFirst ? out1 : out2, leftCount, rightCount);
        leftRemaining -= leftCount;
        rightRemaining -= rightCount;
        if (!secondOutput.empty()) toFirst = !toFirst;
    }
    out1.close();
    if (!secondOutput.empty()) out2.close();
    if (!out1 || (!secondOutput.empty() && !out2)) throw std::runtime_error("Cannot close merge files");
}
