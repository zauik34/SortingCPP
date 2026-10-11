#pragma once
#include <functional>
#include <utility>
#include <vector>

namespace sorting {
template <typename T, typename Compare = std::less<T>>
void binary_insertion_sort(std::vector<T>& values, Compare less = {}) {
    for (std::size_t i = 1; i < values.size(); ++i) {
        // Avoid binary search and shifts when the next item is already in place.
        if (!less(values[i], values[i - 1])) continue;
        T key = std::move(values[i]);
        std::size_t left = 0, right = i;
        while (left < right) {
            const std::size_t middle = left + (right - left) / 2;
            // Upper bound keeps equivalent items in their original order.
            if (less(key, values[middle])) right = middle;
            else left = middle + 1;
        }
        for (std::size_t j = i; j > left; --j)
            values[j] = std::move(values[j - 1]);
        values[left] = std::move(key);
    }
}
} // namespace sorting

// Standard types are instantiated in the separately linked library.
extern template void sorting::binary_insertion_sort<int, std::less<int>>(std::vector<int>&, std::less<int>);
extern template void sorting::binary_insertion_sort<double, std::less<double>>(std::vector<double>&, std::less<double>);
