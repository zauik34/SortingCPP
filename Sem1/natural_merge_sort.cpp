#include "natural_merge_sort.h"

// Создаём библиотечные версии для int и double.
template void naturalMergeSort(std::vector<int>&);
template void naturalMergeSortFile<int>(const std::string&);
template void naturalMergeSort(std::vector<double>&);
template void naturalMergeSortFile<double>(const std::string&);
