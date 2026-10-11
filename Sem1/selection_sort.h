#pragma once
#include <cstddef>
#include <vector>
#include <utility>

template <typename T>
void selectionSort(std::vector<T>& arr) {
    for (std::size_t i = 0; i < arr.size(); ++i) {
        std::size_t minIndex = i;
        // Находим минимум в ещё не отсортированной части.
        for (std::size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[minIndex]) minIndex = j;
        }
        if (minIndex != i) std::swap(arr[i], arr[minIndex]);
    }
}
