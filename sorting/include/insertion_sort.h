#pragma once
#include <functional>
#include <utility>
#include <vector>

namespace sorting {
template <typename T, typename Compare = std::less<T>>
void insertion_sort(std::vector<T>& values, Compare less = {}) {
    for (std::size_t i = 1; i < values.size(); ++i) {
        T key = std::move(values[i]);
        std::size_t j = i;
        while (j > 0 && less(key, values[j - 1])) {
            values[j] = std::move(values[j - 1]);
            --j;
        }
        values[j] = std::move(key);
    }
}
} // namespace sorting

// Standard types are instantiated in the separately linked library.
extern template void sorting::insertion_sort<int, std::less<int>>(std::vector<int>&, std::less<int>);
extern template void sorting::insertion_sort<double, std::less<double>>(std::vector<double>&, std::less<double>);
