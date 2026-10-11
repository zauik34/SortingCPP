#pragma once
#include "detail/file_sort_support.h"
#include <functional>

namespace sorting {
template <typename T, typename Compare = std::less<T>>
void natural_merge_sort(const std::filesystem::path& input,
                        const std::filesystem::path& output, Compare less = {}) {
    file_detail::sort_file<T>(input, output, file_detail::Method::natural, less);
}
template <typename T, typename Compare = std::less<T>>
void natural_merge_sort(std::vector<T>& values, Compare less = {}) {
    file_detail::sort_vector(values, file_detail::Method::natural, less);
}
} // namespace sorting

// Standard types are instantiated in the separately linked library.
extern template void sorting::natural_merge_sort<int, std::less<int>>(std::vector<int>&, std::less<int>);
extern template void sorting::natural_merge_sort<int, std::less<int>>(const std::filesystem::path&, const std::filesystem::path&, std::less<int>);
extern template void sorting::natural_merge_sort<double, std::less<double>>(std::vector<double>&, std::less<double>);
extern template void sorting::natural_merge_sort<double, std::less<double>>(const std::filesystem::path&, const std::filesystem::path&, std::less<double>);
