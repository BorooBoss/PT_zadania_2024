/*
Meno a priezvisko:

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

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Reprezentacia uzla zretazeneho zoznamu
struct Node {
    int data; // hodnota uzla
    Node* next; // adresa nasledujuceho uzla zoznamu
};

// Reprezentacia zretazeneho zoznamu
struct List {
    Node* first; // adresa prveho uzla zoznamu
};

// Uspesnost vykonania funkcie
enum class Result {
    SUCCESS, // funkcia vykonana uspesne
    FAILURE  // chyba pri vykonavani funkcie
};

Node *createNode(const int value) {
    Node *tmp = new Node;
    tmp->data = value;
    tmp->next = nullptr;
    return tmp;
}
//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia prida novy uzol s hodnotou 'val' na zaciatok zoznamu 'list'.

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] val - hodnota uzla pridaneho na zaciatok zoznamu

    PRIKLADY:
        list=() a val=0 ... zoznam po vykonani funkcie ... (0)
        list=(-3) a val=1 ... zoznam po vykonani funkcie ... (1,-3)
        list=(6,6,5,8) a val=10 ... zoznam po vykonani funkcie ... (10,6,6,5,8)
*/

void prependNode(List* list, const int val) {
    Node *new_node = createNode(val);
    new_node->next = list->first;
    list->first = new_node;
}





void prependnode2(List* list, const int value){
    Node* new_node = createNode(value); //vytvorim si novy uzol
    new_node->next = list->first;
    list->first = new_node;

}
//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia prida novy uzol s hodnotou 'val' na koniec zoznamu 'list'.

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] val - hodnota uzla pridaneho na koniec zoznamu

    PRIKLADY:
        list=() a val=7 ... zoznam po vykonani funkcie ... (7)
        list=(0) a val=1 ... zoznam po vykonani funkcie ... (0,1)
        list=(1,2,3,4,5) a val=6 ... zoznam po vykonani funkcie ... (1,2,3,4,5,6)
*/

void appendNode(List* list, const int val) {
    Node *new_node = createNode(val);
    if (!list->first){
        list->first = new_node;
    }
    else {
        Node *tmp = list->first;
        while (tmp->next){
            tmp = tmp->next;
        }
        tmp->next = new_node;

    }
}
void appendnode2(List* list, const int value){
    Node* new_list = createNode(value);
    if (list->first == nullptr){
        list->first = new_list;
    }
    else{
        Node* tmp = list->first;
        while(tmp->next != nullptr){
            tmp = tmp->next;
        }
        tmp->next = new_list;
    }

}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy zretazeny zoznam a vyplni ho vsetkymi cislami (v zachovanom poradi),
    ktore sa nachadzaju vo vstupnom poli 'data', ktore ma dlzku 'n'.

    PARAMETRE:
        [in] data - vstupne pole cisiel
        [in] n - dlzka vstupneho pola

    NAVRATOVA HODNOTA:
        Vytvoreny zretazeny zoznam obsahujuci vsetky hodnoty zo vstupneho pola 'data' (v zachovanom poradi).
        V pripade prazdneho pola (dlzka 0), funkcia vrati prazdny zoznam (prazdny zoznam je taky, kde smernik 'first'
        ukazuje na 'nullptr').

    PRIKLADY:
        data=(1) a n=1 ... vrati zoznam ... (1)
        data=(7,6,41,2) a n=4 ... vrati zoznam ... (7,6,41,2)
        data=(3,2,1) a n=0 ... vrati zoznam ... ()
*/

List* createListFromArray(const int* data, const size_t n) {
   List* newList = new List;
   newList->first = nullptr;
   if (n == 0){
       return newList;
   }
   Node* current; //zatial dame na null bo je tam null
   for (size_t i = 0; i<n; i++){
       Node* newNode = createNode(data[i]);
       if (newList->first == nullptr) {
           newList->first = newNode;
           current = newNode; // Nastavíme current na prvý uzol
       } else {
           current->next = newNode;
           current = newNode; // Posunieme current na nový uzol
       }
       current = newNode; //posuvame sa o prvok dalej
   }
    return newList; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}


List* createListFromArray2(const int* data, const size_t n){
    List* list = new List;
    list->first = nullptr;
    if (n == 0){
        return list;
    }
    Node* current;
    for(size_t i = 0; i<n; i++){
        Node* uzol = createNode(data[i]);
        if (list->first == nullptr){
            list->first = uzol;
            current = uzol;
        }
        else{
            current->next = uzol;
            current = uzol;
        }
    }
    return list;
}
//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy symetricky zretazeny zoznam (vid priklady) podla parametra 'val'.
    Symetricky zoznam ma tvar 0,1,2,...val...2,1,0.

    PARAMETRE:
        [in] val - hodnota uzla podla, ktoreho sa vytvori novy symetricky zretazeny zoznam (uzol v strede zoznamu).

    NAVRATOVA HODNOTA:
        Vytvoreny zretazeny zoznam obsahujuci prvky v takom poradi, aby bol symetricky.
        V pripade 'val'<0, funkcia vrati 'nullptr'.

    PRIKLADY:
        val=-31 ... vrati ... nullptr
        val=0 ... vrati zoznam ... (0)
        val=1 ... vrati zoznam ... (0,1,0)
        val=2 ... vrati zoznam ... (0,1,2,1,0)
        val=3 ... vrati zoznam ... (0,1,2,3,2,1,0)
        val=4 ... vrati zoznam ... (0,1,2,3,4,3,2,1,0)
        val=6 ... vrati zoznam ... (0,1,2,3,4,5,6,5,4,3,2,1,0)
*/

List* createSymmetricList(const int val) {
    if (val < 0) {
        return nullptr;
    }

    List* newList = new List;
    newList->first = nullptr;
    Node* current = nullptr;

    // Vytvorenie prvej polovice (od 0 po val vrátane)
    for (int i = 0; i <= val; i++) {
        Node* newNode = createNode(i);
        if (newList->first == nullptr) {
            newList->first = newNode;  // Nastavíme prvý uzol
        } else {
            current->next = newNode;   // Pripojíme nový uzol za current
        }
        current = newNode;             // Posunieme current na nový uzol
    }

    // Vytvorenie druhej polovice (od val-1 po 0)
    for (int i = val - 1; i >= 0; i--) {
        Node* newNode = createNode(i);
        current->next = newNode;   // Pripojíme nový uzol za current
        current = newNode;         // Posunieme current na nový uzol
    }

    return newList;
}

List* createSymmetricList2(const int value){
    if (value == 0){
        return nullptr;
    }
    List* list = new List;
    list->first = nullptr;
    Node* current;

    for (size_t i = 0; i <= value; i++){
        Node* node = createNode(i);
        if (list->first == nullptr){
            list->first = node;
            current = node;
        }
        else {
            current->next = node;
            current = node;
        }


    }
    for (int j = value-1; j >= 0; j--){
        Node* node = createNode(j);
        current->next = node;
        current = node;
    }
    return list;
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia odstrani (aj spravne uvolni pamat) zo vstupneho zoznamu 'list' prvy uzol.

    PARAMETRE:
        [in,out] list - zretazeny zoznam, z ktoreho funkcia odstrani uzol

    NAVRATOVA HODNOTA:
        Result::SUCCESS, ak bol prvy uzol vymazany
        Result::FAILURE, ak nebol prvy uzol vymazany (vstupny zoznam bol prazdny)

    PRIKLADY:
        list=() ... funkcia vrati Result::FAILURE
        list=(5) ... zoznam po vykonani funkcie ... () a vrati Result::SUCCESS
        list=(10,10,10) ... zoznam po vykonani funkcie ... (10,10) a vrati Result::SUCCESS
        list=(3,2,1) ... zoznam po vykonani funkcie ... (2,1) a vrati Result::SUCCESS
*/

Result removeFirstNode(List* list) {
    if (list->first == nullptr){
        return Result::FAILURE;
    }
    Node *tmp = list->first;
    list->first = tmp->next;
    delete tmp;
    return Result::SUCCESS; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}
 Result removenode2(List* list){
    if (list->first == nullptr){
        return Result::FAILURE;
    }
    Node* tmp = list->first;
    list->first = tmp->next;
    delete tmp;
    return Result::SUCCESS;
}
//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia najde prvy uzol zretazeneho zoznamu 'list', ktory obsahuje hodnotu 'val'.

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] val - hodnota uzla, ktory sa hlada

    NAVRATOVA HODNOTA:
        Funkcia vrati prvy uzol, ktory obsahuje hodnotu 'val'.
        Ak sa taky uzol v zozname nenachadza alebo je vstupny zoznam prazdny, vtedy funkcia vrati 'nullptr'.

    PRIKLADY:
        list=(), val=10 ... funkcia vrati 'nullptr'
        list=(2), val=3 ... funkcia vrati 'nullptr'
        list=(1,2,3,4,5,6), val=-1 ... funkcia vrati 'nullptr'
        list=(1), val=1 ... funkcia vrati uzol s hodnotou 1
        list=(5,9,18), val=9 ... funkcia vrati uzol s hodnotou 9
*/

Node* findNodeInList(List* list, const int val) {
    if (list->first == nullptr){
        return nullptr;
    }
    Node* current = list->first;
    while (current != nullptr){
        if (current->data == val){
            return current;
        }
        current = current->next;
    }
    return nullptr; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}
Node* findnode(List* list, const int value){
    if (list->first == nullptr){
        return nullptr;
    }
    Node* current = list->first;
    while(current != nullptr){
        if (current->data == value){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}
//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia zisti, ci su dva vstupne zoznamy 'list1' a 'list2' rovnake (t.j. rovnako dlhe a obsahujuce
    rovnake hodnoty uzlov v rovnakom poradi).

    PARAMETRE:
        [in] list1 - prvy zretazeny zoznam
        [in] list2 - druhy zretazeny zoznam

    NAVRATOVA HODNOTA:
        'true' - ak su vstupne zoznamy rovnake
        'false' - ak vstupne zoznamy nie su rovnake

    PRIKLADY:
        list1=(1)
        list2=()
        Funkcia vrati 'false'.

        list1=()
        list2=(5,3)
        Funkcia vrati 'false'.

        list1=()
        list2=()
        Funkcia vrati 'true'.

        list1=(1)
        list2=(1)
        Funkcia vrati 'true'.

        list1=(4,-9,2)
        list2=(4,-9,2)
        Funkcia vrati 'true'.

        list1=(3,2,1)
        list2=(1,2,3)
        Funkcia vrati 'false'.

        list1=(2)
        list2=(7,4,5)
        Funkcia vrati 'false'.

        list1=(7,4)
        list2=(7,4,5)
        Funkcia vrati 'false'.
*/

bool areListsEqual(List* list1, List* list2) {
    Node* current1 = list1->first;
    Node* current2 = list2->first;

    // Prechádzame oboma zoznamami súčasne
    while (current1 != nullptr && current2 != nullptr) {
        if (current1->data != current2->data) {
            return false; // Ak sa hodnoty líšia, zoznamy nie sú rovnaké
        }
        current1 = current1->next;
        current2 = current2->next;
    }

    // Zistíme, či obe prešli na koniec zoznamu zároveň
    return current1 == nullptr && current2 == nullptr;
}
    bool areListsEqual2(List* list1, List* list2) {
    Node* current1 = list1->first;
    Node* current2 = list2->first;
    while (current1 != nullptr && current2 != nullptr){
        if (current1->data != current2->data){
            return false;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    return current1 == nullptr && current2 == nullptr;
}
//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy zretazeny zoznam prekopirovanim vsetkych hodnot uzlov vstupneho zoznamu 'list' v obratenom
    poradi.

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam

    NAVRATOVA HODNOTA:
        Zretazeny oznam, ktory vznikne prekopirovanim hodnot uzlov vstupneho zoznamu 'list' v obratenom poradi.

    PRIKLADY:
        list=() ... funkcia vrati ... () t.j. prazdny zoznam
        list=(1) ... funkcia vrati ... (1)
        list=(5,6) ... funkcia vrati ... (6,5)
        list=(8,14,2,3) ... funkcia vrati ... (3,2,14,8)
*/

List* copyListReverse(List* list) {
    List* newList = new List;  // vytvorenie nového zoznamu
    newList->first = nullptr;  // inicializácia prázdneho zoznamu

    Node* current = list->first;  // začiatok na prvom uzle pôvodného zoznamu

    // Prechádzame pôvodný zoznam
    while (current != nullptr) {
        // Vytvoríme nový uzol s rovnakou hodnotou ako má aktuálny uzol
        Node* newNode = createNode(current->data);

        // Pridáme nový uzol na začiatok nového zoznamu
        newNode->next = newList->first;
        newList->first = newNode;

        // Posunieme sa na ďalší uzol v pôvodnom zozname
        current = current->next;
    }

    return newList;  // vrátime nový zoznam v opačnom poradí
}
List* copylistReverse2(List* list){
    List* reverse = new List;
    reverse->first = nullptr;
    Node* current = list->first;
    while (current != nullptr){
        Node* node = createNode(current->data);
        node->next = reverse->first;
        reverse->first = node;
        current = current->next;
    }
    return reverse;
}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vyhlada predchodcu zadaneho uzla 'node' vo vstupnom zretazenom zozname 'list'.

    VSTUPNA PODMIENKA:
        Uzol 'node' je vzdy existujucim uzlom vstupneho zoznamu 'list'.

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] node - uzol zretazeneho zoznamu 'list', ktoreho predchodcu hladame

    NAVRATOVA HODNOTA:
        Uzol, ktory je predchodcom uzla 'node' v zozname 'list'.
        V pripade hladania predchodcu prveho uzla zoznamu, funkcia vrati 'nullptr'.

    PRIKLADY:
        list=(4)
        node=4
        Funkcia vrati 'nullptr'.

        list=(1,2,3,4,5)
        node=1
        Funkcia vrati 'nullptr'.

        list=(-2,-3,56,4,41)
        node=-3
        Funkcia vrati uzol s hodnotou -2.

        list=(10,54,69,82,6)
        node=6
        Funkcia vrati uzol s hodnotou 82.
*/

Node* findPreviousNode(List* list, Node* node) {
    Node *pred = nullptr;
    Node *tmp = list->first;
    while (tmp) {
        if (tmp == node) {
            return pred;
        }
        pred = tmp;
        tmp = tmp->next;
    }
    return nullptr; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}
Node* findPreviousNode2(List* list, Node* node) {
    Node* tmp = list->first;
    Node* previous = nullptr;
    while(tmp != nullptr){
        if (node->data == tmp->data){
            return previous;
        }
        previous = tmp;
        tmp = tmp->next;
    }
    return tmp;
}
//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia zduplikuje vsetky uzly vstupneho zoznamu 'list', ktore obsahuju kladnu hodnotu.

    PARAMETRE:
        [in,out] list - vstupny zretazeny zoznam

    PRIKLADY:
        list=() ... po vykonani funkcie ... ()
        list=(3) ... po vykonani funkcie ... (3,3)
        list=(-1,1) ... po vykonani funkcie ... (-1,1,1)
        list=(-8,-9,-13) ... po vykonani funkcie ... (-8,-9,-13)
        list=(1,0,-2,3,-4) ... po vykonani funkcie ... (1,1,0,-2,3,3,-4)
*/

void duplicatePositiveNodes(List* list) {
    if (list->first == nullptr){
        return;
    }
    Node *tmp = list->first;
    while (tmp != nullptr){
        if (tmp->data > 0){
            Node* newNode = new Node; //alokuj miesto
            newNode->data = tmp->data; //najeb tam toto
            newNode->next = tmp->next; // tam kde smeruje povodnz zoznam, nastav nech novy tam ide
            tmp->next = newNode; //stary nextprehod na novy smernik

            // Preskočíme nový uzol, aby sme prešli na ďalší pôvodný uzol
            tmp = newNode->next;
        } else {
            tmp = tmp->next; // Presúvame sa na ďalší uzol
        }
    }
}
void duplicatePositiveNodes2(List* list) {
    if (list->first == nullptr){
        return;
    }
    Node* current = list->first;
    while (current != nullptr){
        if (current->data > 0){
            Node* newNode = new Node;
            newNode->data = current->data;
            newNode->next = current->next;
            current->next = newNode;
            current = newNode->next;
        }
        else{
            current = current->next;
        }
    }

}

void printList(const List *list) {
    Node *tmp = list->first;
    while (tmp) {
        std::cout << tmp->data << " ";
        tmp = tmp->next;
    }
    std::cout << std::endl;
}
//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury pre testovanie

int main() {

    // tu mozete doplnit vas vlastny testovaci kod
    List* jozef = createSymmetricList2(4);
    printList(jozef);
    return 0;
}
