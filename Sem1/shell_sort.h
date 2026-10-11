#pragma once
#include <cstddef>
#include <vector>
#include <utility>

template <typename T>
void shellSort(std::vector<T>& arr) {
    // Выполняем вставки сначала с большим шагом, затем уменьшаем его.
    for (std::size_t gap = arr.size() / 2; gap > 0; gap /= 2) {
        for (std::size_t i = gap; i < arr.size(); ++i) {
            T key = arr[i];
            std::size_t j = i;
            while (j >= gap && arr[j - gap] > key) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = key;
        }
    }
}
