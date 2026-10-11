#pragma once
#include <functional>
#include <utility>
#include <vector>

namespace sorting {
namespace detail {
template <typename T, typename Compare>
void quick_sort_range(std::vector<T>& values, std::size_t begin,
                      std::size_t end, Compare& less) {
    while (end - begin > 1) {
        const T pivot = values[begin + (end - begin) / 2];
        std::size_t lower = begin, current = begin, upper = end;
        // Three-way partition: < pivot | equivalent | > pivot.
        while (current < upper) {
            if (less(values[current], pivot)) {
                std::swap(values[lower++], values[current++]);
            } else if (less(pivot, values[current])) {
                std::swap(values[current], values[--upper]);
            } else {
                ++current;
            }
        }
        // Recurse only into the smaller partition: O(log n) stack even
        // when time degenerates to O(n^2). Process the larger one in a loop.
        if (lower - begin < end - upper) {
            quick_sort_range(values, begin, lower, less);
            begin = upper;
        } else {
            quick_sort_range(values, upper, end, less);
            end = lower;
        }
    }
}
} // namespace detail
template <typename T, typename Compare = std::less<T>>
void quick_sort(std::vector<T>& values, Compare less = {}) {
    detail::quick_sort_range(values, 0, values.size(), less);
}
} // namespace sorting

// Standard types are instantiated in the separately linked library.
extern template void sorting::quick_sort<int, std::less<int>>(std::vector<int>&, std::less<int>);
extern template void sorting::quick_sort<double, std::less<double>>(std::vector<double>&, std::less<double>);
