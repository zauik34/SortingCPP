#pragma once
#include <cstddef>
#include <vector>
#include <utility>

template <typename T>
void insertionSort(std::vector<T>& arr) {
    for (std::size_t i = 1; i < arr.size(); ++i) {
        T key = arr[i];
        std::size_t j = i;
        // Сдвигаем большие элементы вправо, освобождая место для key.
        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = key;
    }
}
