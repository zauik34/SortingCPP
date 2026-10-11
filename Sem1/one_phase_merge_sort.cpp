#include "one_phase_merge_sort.h"

// Создаём библиотечные версии для int и double.
template void onePhaseMergeSort(std::vector<int>&);
template void onePhaseMergeSortFile<int>(const std::string&);
template void onePhaseMergeSort(std::vector<double>&);
template void onePhaseMergeSortFile<double>(const std::string&);
