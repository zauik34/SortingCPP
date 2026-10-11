#pragma once
#include <functional>
#include <utility>
#include <vector>

namespace sorting {
template <typename T, typename Compare = std::less<T>>
void shell_sort(std::vector<T>& values, Compare less = {}) {
    // Shell's original gaps: n/2, n/4, ..., 1.
    for (std::size_t gap = values.size() / 2; gap > 0; gap /= 2) {
        for (std::size_t i = gap; i < values.size(); ++i) {
            T key = std::move(values[i]);
            std::size_t j = i;
            while (j >= gap && less(key, values[j - gap])) {
                values[j] = std::move(values[j - gap]);
                j -= gap;
            }
            values[j] = std::move(key);
        }
    }
}
} // namespace sorting

// Standard types are instantiated in the separately linked library.
extern template void sorting::shell_sort<int, std::less<int>>(std::vector<int>&, std::less<int>);
extern template void sorting::shell_sort<double, std::less<double>>(std::vector<double>&, std::less<double>);
