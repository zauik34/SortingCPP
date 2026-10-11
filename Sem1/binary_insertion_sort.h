#pragma once
#include <cstddef>
#include <vector>
#include <utility>

template <typename T>
void binaryInsertionSort(std::vector<T>& arr) {
    for (std::size_t i = 1; i < arr.size(); ++i) {
        T key = arr[i];
        std::size_t left = 0, right = i;
        // Бинарный поиск места после элементов, равных key.
        while (left < right) {
            std::size_t mid = left + (right - left) / 2;
            if (key < arr[mid]) right = mid;
            else left = mid + 1;
        }
        // Поиск стал быстрее, но сдвиг элементов всё равно нужен.
        for (std::size_t j = i; j > left; --j) arr[j] = arr[j - 1];
        arr[left] = key;
    }
}
