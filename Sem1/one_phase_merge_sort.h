#pragma once
#include "file_helpers.h"
#include <filesystem>
#include <utility>

template <typename T>
void onePhaseMergeSortFile(const std::string& filename) {
    std::size_t total = fileElementCount<T>(filename);
    if (total < 2) return;
    std::string input1 = filename + ".1.tmp", input2 = filename + ".2.tmp";
    std::string output1 = filename + ".3.tmp", output2 = filename + ".4.tmp";
    // Вначале распределяем отдельные элементы между двумя файлами.
    splitFixedFile<T>(filename, input1, input2, 1);
    for (std::size_t length = 1; length < total;) {
        // Сливаем и сразу распределяем результат в два выходных файла.
        mergeFixedFiles<T>(input1, input2, output1, output2, length);
        std::swap(input1, output1);
        std::swap(input2, output2);
        if (length >= total - length) break;
        length *= 2;
    }
    // После последнего прохода одна итоговая серия находится в input1.
    std::filesystem::copy_file(input1, filename, std::filesystem::copy_options::overwrite_existing);
    std::remove(input1.c_str()); std::remove(input2.c_str());
    std::remove(output1.c_str()); std::remove(output2.c_str());
}

template <typename T>
void onePhaseMergeSort(std::vector<T>& arr) {
    if (arr.size() < 2) return;
    const std::string filename = "temp_one_phase.bin";
    writeVectorToFile(filename, arr);
    onePhaseMergeSortFile<T>(filename);
    arr = readVectorFromFile<T>(filename);
    std::remove(filename.c_str());
}
