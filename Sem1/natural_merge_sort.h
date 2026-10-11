#pragma once
#include "file_helpers.h"

template <typename T>
void naturalMergeSortFile(const std::string& filename) {
    if (fileElementCount<T>(filename) < 2) return;
    std::string left = filename + ".left.tmp", right = filename + ".right.tmp";
    std::string lengths = filename + ".lengths.tmp";
    while (true) {
        std::size_t runs = 0;
        // Фаза 1: выделяем уже упорядоченные серии.
        {
            std::ifstream in(filename, std::ios::binary);
            std::ofstream out1(left, std::ios::binary), out2(right, std::ios::binary);
            std::ofstream sizes(lengths);
            if (!in || !out1 || !out2 || !sizes) throw std::runtime_error("Cannot open natural split files");
            T current{}, previous{};
            readValue(in, previous);
            bool toFirst = true;
            std::size_t count = 1;
            writeValue(out1, previous);
            while (readValue(in, current)) {
                if (current < previous) {
                    sizes << count << '\n';
                    ++runs;
                    count = 0;
                    toFirst = !toFirst;
                }
                writeValue(toFirst ? out1 : out2, current);
                ++count;
                previous = current;
            }
            sizes << count << '\n';
            ++runs;
            out1.close(); out2.close(); sizes.close();
            if (!out1 || !out2 || !sizes) throw std::runtime_error("Cannot close natural split files");
        }
        if (runs == 1) break;
        // Фаза 2: читаем длины серий и сливаем их попарно.
        {
            std::ifstream in1(left, std::ios::binary), in2(right, std::ios::binary);
            std::ifstream sizes(lengths);
            std::ofstream out(filename, std::ios::binary);
            if (!in1 || !in2 || !sizes || !out) throw std::runtime_error("Cannot open natural merge files");
            std::size_t leftCount = 0, rightCount = 0;
            while (sizes >> leftCount) {
                if (!(sizes >> rightCount)) rightCount = 0;
                mergeSeries<T>(in1, in2, out, leftCount, rightCount);
            }
            out.close();
            if (!out) throw std::runtime_error("Cannot close natural merge file");
        }
    }
    std::remove(left.c_str()); std::remove(right.c_str());
    std::remove(lengths.c_str());
}

template <typename T>
void naturalMergeSort(std::vector<T>& arr) {
    if (arr.size() < 2) return;
    const std::string filename = "temp_natural.bin";
    writeVectorToFile(filename, arr);
    naturalMergeSortFile<T>(filename);
    arr = readVectorFromFile<T>(filename);
    std::remove(filename.c_str());
}
