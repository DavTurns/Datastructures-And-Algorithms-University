#include "Map.h"
#include "MapIterator.h"
#include <stdlib.h>

//general 0(1)
Map::Map() {
    //TODO - Implementation
    capacity = 5;
    nrElems = 0;
    this->array = new Node *[capacity]{nullptr};
}

//general 0(1)
int Map::hashfunction(TKey keyValue, int capacity) const {
    return abs(keyValue) % capacity;
}

int Map::nextprimenumber(int number) {
    int nextnumber = number + 1;
    while (true) {
        int z = 2;
        while (nextnumber % z != 0 && z < nextnumber) z++;
        if (z == nextnumber) return nextnumber;
        nextnumber++;
    }
}

//general 0(n)
Map::~Map() {
    for(int i = 0; i<capacity; i++){
        Node* currentNode = array[i];
        Node* nextNode = nullptr;
        while(currentNode!= nullptr){
            nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }
    }
    delete[] array;
}

//worst-case:0(n)
//best-case:0(1)
//average-case: 0(1) amortisiert
//general-case: 0(n)

TValue Map::add(TKey c, TValue v) {
    //TODO - Implementation
    if (nrElems == capacity) {

        //resize and rehashing
        int oldcapacity = capacity;
        capacity = nextprimenumber(capacity);

        Node **newarray = new Node *[capacity]{nullptr};
        Node *currentNode;
        Node *nextNode;
        int newindex;

        //durchlaufe den alten array und kopiere jedes TElem in das neue array
        for (int i = 0; i < oldcapacity; i++) {
            if (array[i] != nullptr) {
                currentNode = array[i];
                while (currentNode != nullptr) {
                    nextNode = currentNode->next;

                    newindex = hashfunction(currentNode->info.first, capacity);
                    currentNode->next = newarray[newindex];
                    newarray[newindex] = currentNode;

                    currentNode = nextNode;
                }
            }
        }
        delete[] array;
        array = newarray;
    }

    //add element
    int position = hashfunction(c, capacity);

    //durchlaufe die SLL and position und ersetze TValue wenn TKey schon vorhanden,
    Node* currentNode = array[position];
    while(currentNode != nullptr){
        if(currentNode->info.first == c){
            TValue oldvalue = currentNode->info.second;
            currentNode->info.second = v;
            return oldvalue;
        }
        currentNode = currentNode->next;
    }

    Node* newNode = new Node;
    newNode->info.first = c;
    newNode->info.second = v;

    newNode->next = array[position];
    array[position] = newNode;
    nrElems++;
    return NULL_TVALUE;
}

/*bestcase:0(1)
 * worstcase:0(n)
 * average:0(1) amortisiert
 * general:O(n)
 * */
TValue Map::search(TKey c) const {
    //TODO - Implementation
    int position = hashfunction(c, capacity);
    Node *CurrentNode = array[position];
    while (CurrentNode != nullptr) {
        if (CurrentNode->info.first == c) {
            return CurrentNode->info.second;
        }
        CurrentNode = CurrentNode->next;
    }
    return NULL_TVALUE;
}

/*
 * best-case: 0(1)
 * worst-case:0(n)
 * average-case:0(1) amortisiert
 * general-case:O(n)
 * */

TValue Map::remove(TKey c) {
    int position = hashfunction(c, capacity);
    Node *PreviousNode = nullptr;
    Node *CurrentNode = array[position];

    //wenn kein Node auf der Position exsistiert
    if(array[position] == nullptr) return NULL_TVALUE;

    //wenn Node am Anfang steht können wir nicht mit PreviousNode arbeiten
    if(array[position]->info.first == c){
        TValue deletedvalue = array[position]->info.second;
        CurrentNode = array[position];
        array[position] = array[position]->next;
        delete CurrentNode;
        nrElems--;
        return deletedvalue;
    }
    while (CurrentNode != nullptr) {
        if (CurrentNode->info.first == c) {
            PreviousNode->next = CurrentNode->next;
            delete CurrentNode;
            nrElems--;
            return CurrentNode->info.second;
        }
        PreviousNode = CurrentNode;
        CurrentNode = CurrentNode->next;
    }

    //wenn kein schlüssel gefunden wurde
    return NULL_TVALUE;
}

//general: 0(1)
int Map::size() const {
    return nrElems;
}

//general:0(1)
bool Map::isEmpty() const {
    if(nrElems == 0) return true;
    return false;
}


MapIterator Map::iterator() const {
    return MapIterator(*this);
}



