#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std::chrono;
using namespace std;

// funkcia, ktora nahodne vygeneruje prvky pola
void genArray(int *data, const size_t len) {
    for (size_t i = 0; i < len; i++) {
        data[i] = rand() % 200 - 100;
    }
}

// funkcia, ktora vypise prvky pola
void printArray(const int *data, const size_t len) {
    for (size_t i = 0; i < len; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

// funkcia na vymenu hodnot na dvoch adresach
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// funkcia, ktora zotriedi pole algoritmom Bubble Sort (vzostupne)
void bubbleSort(int *data, const size_t len) {
    for (size_t i = 0; i < len - 1; i++) {
        for (size_t j = 0; j < (len - 1 - i); j++) {
            if (data[j] > data[j + 1]) {
                swap(&data[j], &data[j + 1]);
            }
        }
    }
}

// funkcia, ktora vykona algoritmus partition (strategia Lomuto)
size_t partition(int *data, const size_t pivot_index, const size_t left, const size_t right) {
    size_t insert_index = left;
    // pivota presunieme na pravy okraj pola
    swap(&data[pivot_index], &data[right - 1]);
    for (size_t i = left; i < right; i++) {
        if (data[i] <= data[right - 1]) {
            swap(&data[i], &data[insert_index]);
            insert_index++;
        }
    }
    return insert_index - 1;
}

// funkcia, ktora zotriedi pole algoritmom Quick Sort (vzostupne) - budeme ju volat rekurzivne
// ideme triedit v intervale <left,right)

void quickSort(int *data, const size_t left, const size_t right) {
    if (left + 1 < right) {
        // vyber pivota
        size_t pivot_index = rand() % (right - left) + left;
        // partition
        pivot_index = partition(data, pivot_index, left, right);
        // quickSort aplikovany nalavo od pivota
        quickSort(data, left, pivot_index);
        // quickSort aplikovany napravo od pivota
        quickSort(data, pivot_index + 1, right);
    }
}

// funkcia, ktora zotriedi pole algoritmom Quick Sort (vzostupne) - bude sa volat z funkcie main
void quickSort(int *data, const size_t len) {
    quickSort(data, 0, len);
}

// funkcia, ktora zmeria casovu zlozitost dodaneho triediaceho algoritmu

// Postup testovania:
// Triediaci algoritmus zotriedi polia roznych dlzok (dlzky 100,200,300,...1000)
// a pre kazdu dlzku pola sa odmeria priemerny cas triedenia.
// Nakoniec sa na standardny vystup vypisu priemerne casy triedenia pre jednotlive dlzky pola.
void performance_test(void (*sort_func)(int *, const size_t), const char *sort_name) {
    microseconds::rep avg_sorting_times[10];
    microseconds::rep sum_time;
    int test_data[1000];
    size_t data_len;

    cout << sort_name << ": ";

    // otestuju sa rozne dlzky pola
    for (size_t i = 0; i < 10; i++) {
        sum_time = 0;
        data_len = (i + 1) * 100;
        // pole kazdej dlzky sa zotriedi 100 krat, aby sme ziskali priemerny cas
        for (size_t j = 0; j < 100; j++) {
            genArray(test_data, data_len);
            // zaciatok merania casu
            auto start_time = high_resolution_clock::now();
            // triedenie pola
            sort_func(test_data, data_len);
            // koniec merania casu
            auto stop_time = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop_time - start_time);
            sum_time += duration.count();
        }
        avg_sorting_times[i] = sum_time / 100;
        cout << avg_sorting_times[i] << " ";
    }
    cout << endl;
}

#define TESTING

int main() {
    srand(time(NULL));

    int data[20];
    size_t len = sizeof(data) / sizeof(data[0]);
    genArray(data, len);
    printArray(data, len);
//    bubbleSort(data, len);
    quickSort(data, len);
    printArray(data, len);

    // performance testing
#ifdef TESTING
    performance_test(bubbleSort, "Bubble Sort");
    performance_test(quickSort, "Quick Sort");
#endif

    return 0;
}
