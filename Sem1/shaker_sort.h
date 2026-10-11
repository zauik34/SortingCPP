#pragma once
#include <cstddef>
#include <vector>
#include <utility>

template <typename T>
void shakerSort(std::vector<T>& arr) {
    if (arr.size() < 2) return;
    std::size_t left = 0, right = arr.size() - 1;
    while (left < right) {
        bool swapped = false;
        // Проход вправо: переносим максимум в конец.
        for (std::size_t j = left; j < right; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        --right;
        swapped = false;
        // Проход влево: переносим минимум в начало.
        for (std::size_t j = right; j > left; --j) {
            if (arr[j - 1] > arr[j]) {
                std::swap(arr[j - 1], arr[j]);
                swapped = true;
            }
        }
        if (!swapped) break;
        ++left;
    }
}
