#pragma once
#include <functional>
#include <utility>
#include <vector>

namespace sorting {
// Direct exchange: compare each element with ALL following elements.
template <typename T, typename Compare = std::less<T>>
void exchange_sort(std::vector<T>& values, Compare less = {}) {
    for (std::size_t i = 0; i < values.size(); ++i)
        for (std::size_t j = i + 1; j < values.size(); ++j)
            if (less(values[j], values[i])) std::swap(values[i], values[j]);
}
} // namespace sorting

// Standard types are instantiated in the separately linked library.
extern template void sorting::exchange_sort<int, std::less<int>>(std::vector<int>&, std::less<int>);
extern template void sorting::exchange_sort<double, std::less<double>>(std::vector<double>&, std::less<double>);
