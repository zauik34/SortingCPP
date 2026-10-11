#pragma once
#include <cstddef>
#include <vector>
#include <utility>

template <typename T>
void bubbleSort(std::vector<T>& arr) {
    // После прохода самый большой элемент окажется в конце.
    for (std::size_t end = arr.size(); end > 1; --end) {
        for (std::size_t j = 0; j + 1 < end; ++j) {
            if (arr[j] > arr[j + 1]) std::swap(arr[j], arr[j + 1]);
        }
    }
}
