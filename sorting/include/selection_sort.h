#pragma once
#include <functional>
#include <utility>
#include <vector>

namespace sorting {
template <typename T, typename Compare = std::less<T>>
void selection_sort(std::vector<T>& values, Compare less = {}) {
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::size_t minimum = i;
        for (std::size_t j = i + 1; j < values.size(); ++j)
            if (less(values[j], values[minimum])) minimum = j;
        if (minimum != i) std::swap(values[i], values[minimum]);
    }
}
} // namespace sorting

// Standard types are instantiated in the separately linked library.
extern template void sorting::selection_sort<int, std::less<int>>(std::vector<int>&, std::less<int>);
extern template void sorting::selection_sort<double, std::less<double>>(std::vector<double>&, std::less<double>);
