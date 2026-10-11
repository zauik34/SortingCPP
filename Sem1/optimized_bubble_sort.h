#pragma once
#include <cstddef>
#include <vector>
#include <utility>

template <typename T>
void optimizedBubbleSort(std::vector<T>& arr) {
    for (std::size_t end = arr.size(); end > 1; --end) {
        bool swapped = false;
        for (std::size_t j = 0; j + 1 < end; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // Если обменов не было, массив уже отсортирован.
        if (!swapped) break;
    }
}
