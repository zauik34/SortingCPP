#include "quick_sort.h"

// Definitions are in the header so arbitrary template arguments remain supported.
template void sorting::quick_sort<int, std::less<int>>(std::vector<int>&, std::less<int>);
template void sorting::quick_sort<double, std::less<double>>(std::vector<double>&, std::less<double>);
