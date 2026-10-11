#include "two_phase_merge_sort.h"

// Definitions are in the header so arbitrary template arguments remain supported.
template void sorting::two_phase_merge_sort<int, std::less<int>>(std::vector<int>&, std::less<int>);
template void sorting::two_phase_merge_sort<int, std::less<int>>(const std::filesystem::path&, const std::filesystem::path&, std::less<int>);
template void sorting::two_phase_merge_sort<double, std::less<double>>(std::vector<double>&, std::less<double>);
template void sorting::two_phase_merge_sort<double, std::less<double>>(const std::filesystem::path&, const std::filesystem::path&, std::less<double>);
