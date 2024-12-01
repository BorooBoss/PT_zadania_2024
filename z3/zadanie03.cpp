#define LENGTH(array) (sizeof(array)/sizeof(array[0]))
#include <iostream>
#include <iomanip>
/*Meno a priezvisko: Boris Pekarčík

POKYNY:
(1)  Implementujte funkcie tak, aby splnali popis pri ich deklaraciach.
(2)  Cela implementacia musi byt v tomto jednom subore.
(3)  Odovzdajte len tento zdrojovy subor (s vypracovanymi rieseniami).
(4)  Program musi byt kompilovatelny.
(5)  Globalne a staticke premenne su zakazane.
(6)  V ziadnom pripade nemente deklaracie funkcii, ktore mate za ulohu naprogramovat
     (nemente nazvy, navratove hodnoty, ani typ a pocet parametrov v zadanych funkciach).
     Nemente implementacie zadanych datovych typov, ani implementacie hotovych pomocnych funkcii
     (ak nie je v zadani ulohy uvedene inak).
(7)  V pripade potreby mozete kod doplnit o dalsie pomocne funkcie alebo datove typy.
(8)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(9)  Funkcia 'main' musi byt v zdrojovom kode posledna.
*/

#include <iostream>
#include <cstring>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol zretazeneho zoznamu
struct Node {
    int data; // hodnota uzla
    Node* next; // smernik na dalsi uzol zoznamu
};

// Zretazeny zoznam
struct List {
    Node* first; // smernik na prvy uzol zoznamu
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada pole 'data' od najvacsieho prvku po najmensi prvok.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'length' moze mat lubovolnu hodnotu
        'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (1) -> (1)
        () -> ()
*/
void insertionSort(int *data, size_t length) {
    for (size_t i = 1; i < length; ++ i) {
        int temp = data[i];
        size_t j = i;
        while (j > 0 && data[j-1] < temp) {
            data[j] = data[j-1];
            -- j;
        }
        data[j] = temp;
    }
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada textove retazce v poli 'data' od najvacsieho prvku po najmensi (lexikograficky).
    Preusporiadajte smerniky v poli.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada.
                Pole obsahuje smerniky na textove retazce.
                Kazdy textovy retazec je ukonceny '\0'.
                Posledny smernik ma hodnotu 'nullptr'. Podla toho urcite pocet prvkov pola (pocet textovych retazcov).

    VSTUPNE PODMIENKY:
        'data' obsahuje minimalne jeden smernik.
        Posledny smernik ma hodnotu 'nullptr'.

    PRIKLADY:
        ("Juraj", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj", "Andrej", nullptr)
        ("Juraj", "Anabela", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj", "Andrej", "Anabela", nullptr)
        ("Andrej", "Juraj", "Andrej", nullptr) -> ("Juraj", "Andrej", "Andrej", nullptr)
        ("Andrej", nullptr) -> ("Andrej", nullptr)
        (nullptr) -> (nullptr)

    POZNAMKY:
        Pri testovani mozete jednoducho pole vytvorit nasledovnym sposobom:
        const char *mena[] = {"Juraj", "Peter", "Andrej", nullptr};

        Na porovnanie obsahu textovych retazcov vyuzite prislusnu funkciu zo standardnej kniznice.
*/
void insertionSort(const char *data[]) {
    size_t length = 0;
    while (data[length] != nullptr) {
        length++;
    }
    for (size_t i = 1; i < length; ++ i) {
        size_t j = i;
        const char* tmp = data[i];
        while (j > 0 && strcmp(data[j-1], tmp) < 0) {
            data[j] = data[j-1];
            -- j;
        }
        data[j] = tmp;
    }
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada zretazeny zoznam 'list' od najvacsieho prvku po najmensi.
    Preusporiadajte uzly v zozname (nekopirujte hodnoty v uzloch).
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] list - zretazeny zoznam, ktory funkcia usporiada

    VSTUPNE PODMIENKY:
        'list' obsahuje lubovolny pocet uzlov (moze byt prazdny)
        'list' nie je 'nullptr'

    PRIKLADY:
        vstup: 2->1->3,        vystup: 3->2->1
        vstup: 1->2->2->1,     vystup: 2->2->1->1
        vstup: prazdny zoznam, vystup: prazdny zoznam
*/
void insertionSort(List * list) {
    if (list->first == nullptr){
        return;
    }
    Node* current = list->first;
    Node* sort = nullptr;
    while (current != nullptr) {
        Node* next = current->next;
        if (sort == nullptr || sort->data <= current->data) {
            current->next = sort;
            sort = current;
        }
        else{
            Node* temp = sort;
            while (temp->next != nullptr && temp->next->data > current->data) {
                temp = temp->next;
            }

            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
        // Nakoniec aktualizujeme začiatok zoznamu
        list->first = sort;
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vykona algoritmus merge (cast algoritmu merge sort), ktory ma linearnu vypoctovu zlozitost.
    Kombinuje dve susedne, usporiadane casti v poli 'input', do jednej usporiadanej casti v poli 'output'.
    Usporiadanie je od najvacsieho prvku po najmensi prvok!

    PARAMETRE:
        [out] output - vystupne pole, ktoreho cast output[low]...output[high-1] bude po vykonani funkcie usporiadana
        [in]  input  - vstupne pole, ktoreho casti input[low]...input[middle-1] a input[middle]...input[high-1]
                         musia byt pri volani funkcie usporiadane od najvacsieho prvku po najmensi
        [in]  low    - index 1. prvku lavej usporiadanej casti pola 'input'
        [in]  middle - index 1. prvku pravej usporiadanej casti pola 'input'
        [in]  high   - index za poslednym prvkom pravej usporiadanej casti pola 'input'

    VYSTUPNE PODMIENKY:
        Obsah 'input' je nezmeneny.
        output[low] ... output[high-1] obsahuje usporiadane prvky z input[low] ... input[high-1].
        Prvky s indexami mensimi ako 'low' sa nemenia (ani v jednom poli).
        Prvky s indexami vacsimi alebo rovnymi ako 'high' sa nemenia (ani v jednom poli).

    PRIKLAD:
        low: 4
        middle: 8
        hight: 12
        input:                         (10, 10, 10, 10,  7,  5,  2,  0,  8,  4,  2,  1, 10, 10, 10, 10)
        output pred vykonanim funkcie: (20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20)
        output po vykonani funkcie:    (20, 20, 20, 20,  8,  7,  5,  4,  2,  2,  1,  0, 20, 20, 20, 20)
*/
void mergeNeighbours(int *output, const int *input, const size_t low, const size_t middle, const size_t high) {
    size_t i = low;
    size_t j = middle;
    size_t k = low;
    while(i < middle && j < high){ //sme v dobrom intervale porovnania
        if (input[i] >= input[j]){ //prve je vacsie/rovne ako druhe
            output[k] = input[i]; //cize na aktualnej pozicii (zcinam od low) ulozim to co bolo vacsie input[i];
            i++; //posuniem sa
        }
        else{ //druhe je vacsie ako prve
            output[k] = input[j]; //na aktualnu poziciu dam to co bolo
            j++;
        }
        k++;
    }
    while (i < middle) { //cize tie zvysne zmenia 10 na 20
        output[k] = input[i];
        i++;
        k++;
    }
    while (j < high) {
        output[k] = input[j];
        j++;
        k++;
    }

}

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
void merge(int *data, int *tmp, size_t left, size_t mid, size_t right) {
    size_t i = left;
    size_t j = left;
    size_t k = mid + 1;
    while (i <= mid && k <= right) {
        if (data[i] >= data[k]) {
            tmp[j++] = data[i++];
        } else {
            tmp[j++] = data[k++];
        }
    }
    while (i <= mid) {
        tmp[j++] = data[i++];
    }
    while (k <= right) {
        tmp[j++] = data[k++];
    }
    for (i = left; i <= right; ++i) {
        data[i] = tmp[i];
    }
}

void mergeSortR(int *data, int *temp, size_t left, size_t right) {
    if (left < right) {
        size_t mid = (left + (right - left) / 2);
        mergeSortR(data, temp, left, mid);
        mergeSortR(data, temp, mid + 1, right);
        merge(data, temp, left, mid, right);
    }
}

void mergeSort(int *data, const size_t length) {
    if (length < 2) {
        return; }
    int *tmp = new int[length];
    mergeSortR(data, tmp, 0, length - 1);
    delete[] tmp;
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

    //const char* d1[4] = {"Juraj", "Peter", "Andrej", nullptr};
    //insertionSort(d1);
    //printStringArray("d1", d1);
    // tu mozete doplnit testovaci kod
    /*
    int data[] = {1,2,2,1,3,5,6,7,4,4,1};
    int length = sizeof(data) / sizeof(data[0]);
    //printf("%d", length);
    mergeSort(data, length);
    const char *label = "uloha5";

    println(label, data, length);
    int data3[] = {10, 10, 10, 10,  7,  5,  2,  0,  8,  4,  2,  1, 10, 10, 10, 10};
    int data4[] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
    mergeNeighbours(data4, data3, 4, 8, 12);
    int length2 = sizeof(data3) / sizeof(data3[0]);
    println(label, data4, length2);
     */
    return 0;


}
