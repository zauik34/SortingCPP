#include "two_phase_merge_sort.h"

// Создаём библиотечные версии для int и double.
template void twoPhaseMergeSort(std::vector<int>&);
template void twoPhaseMergeSortFile<int>(const std::string&);
template void twoPhaseMergeSort(std::vector<double>&);
template void twoPhaseMergeSortFile<double>(const std::string&);
