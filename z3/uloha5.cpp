#define LENGTH(array) (sizeof(array)/sizeof(array[0]))
#include <iostream>
#include <iomanip>
/*Meno a priezvisko: Boris Pekarčík
//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada prvky v poli 'data' od najvacsieho prvku po najmensi.
    Pouzite algoritmus merge sort.
    Vytvorte jedno pomocne pole. Pre alokaciu a dealokaciu pomocneho pola pouzite new[] a delete[].

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (1) -> (1)
        () -> ()

    POZNAMKA:
        Ak pouzijete pristup top-down, tak
        - v tejto funkcii zabezpecte vytvorenie a kopirovanie dat do pomocneho pola,
        - vytvorte a zavolajte rekurzivnu funkciu, v ktorej implementujete hlavnu cast algoritmu merge sort.
*/
void merge(const int* data, size_t low, size_t mid, size_t high, int* output) { //to iste co funkcia vyssie
    size_t i = low;
    size_t j = mid;
    size_t k = low;
    while(i < mid && j < high){ //sme v dobrom intervale porovnania
        if (data[i] >= data[j]){ //prve je vacsie/rovne ako druhe
            output[k] = data[i]; //cize na aktualnej pozicii (zcinam od low) ulozim to co bolo vacsie input[i];
            i++; //posuniem sa
        }
        else{ //druhe je vacsie ako prve
            output[k] = data[j]; //na aktualnu poziciu dam to co bolo
            j++;
        }
        k++;
    }
    while (i < mid){
        output[k] = data[i];
        k++;i++;
    }
    while (j < high){
        output[k] = data[j];
        k++;j++;
    }

}

void mergeSort(int *data, const size_t length) {
    if (length < 2){ //mensie ako jedna keby to je praznde pole
        return;
    }

    size_t mid = length/2;
    mergeSort(data, mid);
    mergeSort(data+mid, length-mid);

    int* temp = new int[length];

    merge(data,0,(length/2),length,temp);
    for (size_t i = 0; i < length; i++){
        data[i] = temp[i];
    }
    delete[] temp;
}




void println(const char *label, const int *data, size_t length) {
    std::cout << label << ": ";
    for (size_t i = 0; i < length; ++ i) {
        std::cout << std::setw(3) << data[i] << " ";
    }
    std::cout << std::endl;
}
void printStringArray(const char *label, const char *data[]) {
    std::cout << label << ": ";
    size_t i = 0;
    while (data[i] != nullptr) {
        std::cout << data[i] << " ";
        i++;
    }
    std::cout << std::endl;
}
//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

int main() {

    int data[] = {1,2,2,1,3,5,6,7,4,4,1};
    int length = sizeof(data) / sizeof(data[0]);
    //printf("%d", length);
    mergeSort(data, length);
    const char *label = "uloha5";

    println(label, data, length);
    return 0;
}