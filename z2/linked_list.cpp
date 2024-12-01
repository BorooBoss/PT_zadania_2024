// Tema: Zretazeny zoznam
// Autor: Pavol Marak

#include <iostream>

// Definicia potrebnych struktur

// Struktura reprezentujuca uzol
struct Node {
    int data;
    Node *next;
};

// Struktura reprezentujuca zoznam
struct List {
    Node *first; // smernik na prvy uzol zoznamu
};

// Funkcia na vytvorenie noveho uzla (dynamicky)
Node *createNode(const int value) {
    Node *tmp = new Node;
    tmp->data = value;
    tmp->next = nullptr;
    return tmp;
}

// Funkcia na pridanie uzla na zaciatok
void prependNode(List *list, const int value) {
    Node *newNode = createNode(value);
    newNode->next = list->first;
    list->first = newNode;
}

// Funkcia na pridanie uzla na koniec
void appendNode(List *list, const int value) {
    Node *newNode = createNode(value);
    if (!list->first) {
        list->first = newNode;
    } else {
        Node *tmp = list->first;
        while (tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = newNode;
    }
}

// Funkcia na vypis zoznamu
void printList(const List *list) {
    Node *tmp = list->first;
    while (tmp) {
        std::cout << tmp->data << " ";
        tmp = tmp->next;
    }
    std::cout << std::endl;
}

// Funkcia na vyhladanie uzla
Node *findNode(const List *list, const int value) {
    Node *tmp = list->first;
    while (tmp) {
        if (tmp->data == value) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return nullptr;
}

// Funkcia na vyhladanie predchodcu uzla
Node *findPredecessor(const List *list, const int value) {
    Node *pred = nullptr;
    Node *tmp = list->first;
    while (tmp) {
        if (tmp->data == value) {
            return pred;
        }
        pred = tmp;
        tmp = tmp->next;
    }
    return nullptr;
}

// Funkcia na vymazanie uzla
bool removeNode(List *list, const int value) {
    Node *to_remove = findNode(list, value);
    if (!to_remove) {
        return false;
    }
    if (to_remove == list->first) {
        list->first = list->first->next;
    } else {
        Node *pred = findPredecessor(list, value);
        pred->next = to_remove->next;
    }
    delete to_remove;
    return true;
}

// Funkcia na vymazanie vsetkych uzlov zo zoznamu
void clearList(List *list) {
    while (list->first) {
        Node *tmp = list->first->next;
        delete list->first;
        list->first = tmp;
    }
}

// Funkcia na vymazanie celeho zoznamu
void destroyList(List **list) {
    clearList(*list);
    delete (*list);
    (*list) = nullptr;
}

// Testovanie
int main() {

    // 1. uloha - vytvorit prazdny zoznam
    List *list = new List;
    list->first = nullptr;

    // 2. uloha - prepend
    for (int i = 0; i < 10; i++) {
        prependNode(list, 10 - i);
    }

    // 3. uloha - append
    for (int i = 11; i < 20; i++) {
        appendNode(list, i);
    }

    // 4. uloha - vypis zoznamu
    printList(list);

    // 5. uloha - vyhladanie uzla
    Node *to_find = findNode(list, 3);

    // 6. uloha - vyhladanie predchodcu uzla
    Node *pred = findPredecessor(list, 10);

    // 7. uloha - vymazanie uzla
    bool is_removed = removeNode(list, 5);

    // 8. uloha - vymazanie zoznamu
    destroyList(&list);

    return 0;
}
