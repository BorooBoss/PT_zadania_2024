#include <iostream>
#include <iomanip>

void insertionSort(int *data, size_t length) {
    for (size_t i = 1; i < length; ++ i) {
        int temp = data[i];
        size_t j = i;
        while (j > 0 && data[j-1] > temp) {
            data[j] = data[j-1];
            -- j;
        }
        data[j] = temp;
    }
}

#define LENGTH(array) (sizeof(array)/sizeof(array[0]))

void println(const char *label, const int *data, size_t length) {
    std::cout << label << ": ";
    for (size_t i = 0; i < length; ++ i) {
        std::cout << std::setw(3) << data[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "insertion sort" << std::endl;

    int d1[] = {5, 2, 1, 10, 8, 7, 5};
    insertionSort(d1, LENGTH(d1));
    println("d1", d1, LENGTH(d1));

    int d2[] = {100, -5, 1, 2 };
    insertionSort(d2, LENGTH(d2));
    println("d2", d2, LENGTH(d2));

    insertionSort(d2, 1);
    println("d2", d2, 1);

    insertionSort(d2, 0);
    println("d2", d2, LENGTH(d2));

    return 0;
}
