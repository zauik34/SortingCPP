#pragma once
#include <cstddef>
#include <vector>
#include <utility>

template <typename T>
void quickSortRecursive(std::vector<T>& arr, std::ptrdiff_t left, std::ptrdiff_t right) {
    if (left >= right) return;
    std::ptrdiff_t i = left, j = right;
    T pivot = arr[left + (right - left) / 2];
    // Разделяем элементы относительно опорного значения.
    while (i <= j) {
        while (arr[i] < pivot) ++i;
        while (arr[j] > pivot) --j;
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            ++i;
            --j;
        }
    }
    // Сортируем полученные части тем же способом.
    if (left < j) quickSortRecursive(arr, left, j);
    if (i < right) quickSortRecursive(arr, i, right);
}

template <typename T>
void quickSort(std::vector<T>& arr) {
    if (arr.empty()) return;
    quickSortRecursive(arr, 0, static_cast<std::ptrdiff_t>(arr.size()) - 1);
}
