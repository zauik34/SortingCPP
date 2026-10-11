#pragma once
#include "file_helpers.h"

template <typename T>
void twoPhaseMergeSortFile(const std::string& filename) {
    std::size_t total = fileElementCount<T>(filename);
    if (total < 2) return;
    std::string left = filename + ".left.tmp";
    std::string right = filename + ".right.tmp";
    for (std::size_t length = 1; length < total;) {
        // Фаза 1: распределение серий длины 1, 2, 4, ...
        splitFixedFile<T>(filename, left, right, length);
        // Фаза 2: слияние пар серий обратно в исходный файл.
        mergeFixedFiles<T>(left, right, filename, "", length);
        if (length >= total - length) break;
        length *= 2;
    }
    std::remove(left.c_str());
    std::remove(right.c_str());
}

template <typename T>
void twoPhaseMergeSort(std::vector<T>& arr) {
    if (arr.size() < 2) return;
    const std::string filename = "temp_two_phase.bin";
    writeVectorToFile(filename, arr);
    twoPhaseMergeSortFile<T>(filename);
    arr = readVectorFromFile<T>(filename);
    std::remove(filename.c_str());
}
