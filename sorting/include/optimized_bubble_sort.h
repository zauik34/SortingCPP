#pragma once
#include <functional>
#include <utility>
#include <vector>

namespace sorting {
template <typename T, typename Compare = std::less<T>>
void optimized_bubble_sort(std::vector<T>& values, Compare less = {}) {
    std::size_t end = values.size();
    while (end > 1) {
        std::size_t last_swap = 0;
        for (std::size_t j = 1; j < end; ++j) {
            if (less(values[j], values[j - 1])) {
                std::swap(values[j], values[j - 1]);
                last_swap = j;
            }
        }
        // Zero means no swaps; the suffix after the last swap is already sorted.
        end = last_swap;
    }
}
} // namespace sorting

// Standard types are instantiated in the separately linked library.
extern template void sorting::optimized_bubble_sort<int, std::less<int>>(std::vector<int>&, std::less<int>);
extern template void sorting::optimized_bubble_sort<double, std::less<double>>(std::vector<double>&, std::less<double>);
