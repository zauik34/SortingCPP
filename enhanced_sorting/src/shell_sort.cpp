#include "shell_sort.h"

// Definitions are in the header so arbitrary template arguments remain supported.
template void sorting::shell_sort<int, std::less<int>>(std::vector<int>&, std::less<int>);
template void sorting::shell_sort<double, std::less<double>>(std::vector<double>&, std::less<double>);
