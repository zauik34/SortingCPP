#include "optimized_bubble_sort.h"

// Definitions are in the header so arbitrary template arguments remain supported.
template void sorting::optimized_bubble_sort<int, std::less<int>>(std::vector<int>&, std::less<int>);
template void sorting::optimized_bubble_sort<double, std::less<double>>(std::vector<double>&, std::less<double>);
