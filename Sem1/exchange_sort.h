#pragma once
#include <cstddef>
#include <vector>
#include <utility>

template <typename T>
void exchangeSort(std::vector<T>& arr) {
    for (std::size_t i = 0; i < arr.size(); ++i) {
        // Сравниваем arr[i] со всеми следующими элементами.
        for (std::size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[i]) std::swap(arr[i], arr[j]);
        }
    }
}
