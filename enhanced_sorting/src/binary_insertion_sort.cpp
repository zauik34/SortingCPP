#include "binary_insertion_sort.h"

// Definitions are in the header so arbitrary template arguments remain supported.
template void sorting::binary_insertion_sort<int, std::less<int>>(std::vector<int>&, std::less<int>);
template void sorting::binary_insertion_sort<double, std::less<double>>(std::vector<double>&, std::less<double>);
