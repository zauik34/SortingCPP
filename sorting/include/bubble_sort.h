#pragma once
#include <functional>
#include <utility>
#include <vector>

namespace sorting {
template <typename T, typename Compare = std::less<T>>
void bubble_sort(std::vector<T>& values, Compare less = {}) {
    for (std::size_t end = values.size(); end > 1; --end)
        for (std::size_t j = 1; j < end; ++j)
            if (less(values[j], values[j - 1])) std::swap(values[j], values[j - 1]);
}
} // namespace sorting

// Standard types are instantiated in the separately linked library.
extern template void sorting::bubble_sort<int, std::less<int>>(std::vector<int>&, std::less<int>);
extern template void sorting::bubble_sort<double, std::less<double>>(std::vector<double>&, std::less<double>);
