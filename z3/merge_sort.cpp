#include <iostream>
#include <iomanip>
#include <cstring>

void merge(int *output, const int *input, size_t low, size_t middle, size_t high) {
    size_t in1 = low;
    size_t in2 = middle;
    size_t out = low;

    while (in1 < middle && in2 < high) {
        if (input[in1] <= input[in2]) { // stabilne triedenie
            output[out] = input[in1];
            ++ in1;
        }
        else {
            output[out] = input[in2];
            ++ in2;
        }
        ++ out;
    }
    while (in1 < middle) {
        output[out] = input[in1];
        ++ in1;
        ++ out;
    }
    while (in2 < high) {
        output[out] = input[in2];
        ++ in2;
        ++ out;
    }
}

void mergeSortRecursive(int *data1, int *data2, size_t low, size_t high) {
    if (low + 1 < high) {
        size_t middle = (low + high) / 2;
        mergeSortRecursive(data2, data1, low, middle);
        mergeSortRecursive(data2, data1, middle, high);
        ::merge(data1, data2, low, middle, high);
    }
}

void mergeSortTopDown(int *data, size_t length) {
    int *temp = new int[length];
    std::memcpy(temp, data, length * sizeof(int));
    mergeSortRecursive(data, temp, 0, length);
    delete[] temp;
}

void swapPointers(int **a, int **b) {
    int *temp = (*a);
    (*a) = (*b);
    (*b) = temp;
}

void mergeSortBottomUp(int *data, size_t length) {
    int *temp = new int[length];

    int *input = data;
    int *output = temp;
    bool needCopyToOrigin = false;
    for (size_t step = 1; step < length; step *= 2) {
        for (size_t i = 0; i < length; i += 2 * step) {
            size_t low = i;
            size_t middle = std::min(i + step, length);
            size_t high = std::min(i + 2 * step, length);
            ::merge(output, input, low, middle, high);
        }
        needCopyToOrigin = ! needCopyToOrigin;
        swapPointers(&input, &output);
    }
    if (needCopyToOrigin) {
        std::memcpy(data, temp, length * sizeof(int));
    }
    delete[] temp;
}

#define LENGTH(array) (sizeof(array)/sizeof(array[0]))

void println(const char *label, const int *data, size_t length) {
    std::cout << label << ": ";
    for (size_t i = 0; i < length; ++ i) {
        std::cout << std::setw(3) << data[i] << " ";
    }
    std::cout << std::endl;
}

void testMerge() {
    std::cout << "---- test merge ----" << std::endl;
    int input[]  = {100, 200,  1,  3,  5,  7,  2,  4,  6,   8, 300, 400};
    int output[] = { -1,  -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12};
    ::merge(output, input, 2, 6, 10);
    println("input ", input, LENGTH(input));
    println("output", output, LENGTH(output));
}

void testMergeTopDown() {
    std::cout << "---- test merge sort (top-down) ----" << std::endl;
    int d1[] = {5, 2, 1, 10, 8, 7, 5};
    mergeSortTopDown(d1, LENGTH(d1));
    println("d1", d1, LENGTH(d1));
}

void testMergeBottomUp() {
    std::cout << "---- test merge sort (bottom-up) ----" << std::endl;
    int d1[] = {5, 2, 1, 10, 8, 7, 5};
    mergeSortBottomUp(d1, LENGTH(d1));
    println("d1", d1, LENGTH(d1));
}


int main() {
    testMerge();
    testMergeTopDown();
    testMergeBottomUp();
    return 0;
}
