#pragma once
#include <functional>
#include <utility>
#include <vector>

namespace sorting {
template <typename T, typename Compare = std::less<T>>
void shaker_sort(std::vector<T>& values, Compare less = {}) {
    if (values.size() < 2) return;
    std::size_t left = 0, right = values.size() - 1;
    while (left < right) {
        bool swapped = false;
        for (std::size_t j = left; j < right; ++j) {
            if (less(values[j + 1], values[j])) {
                std::swap(values[j], values[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        --right;
        swapped = false;
        for (std::size_t j = right; j > left; --j) {
            if (less(values[j], values[j - 1])) {
                std::swap(values[j], values[j - 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        ++left;
    }
}
} // namespace sorting

// Standard types are instantiated in the separately linked library.
extern template void sorting::shaker_sort<int, std::less<int>>(std::vector<int>&, std::less<int>);
extern template void sorting::shaker_sort<double, std::less<double>>(std::vector<double>&, std::less<double>);
