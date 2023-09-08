#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;
//ADT SortedMultiMap – repräsentiert mithilfe einer SLLA von Paaren der Form (key, value)
// und sortiert mithilfe einer Relation auf den Schlüsseln (key). Ein Schlüssel kann mehrmals vorkommen.
//colectia tuturor cheilor - cheie cu numar de aparitii pt fiecare cheie

//Komplexitat: 0(n)
SortedMultiMap::SortedMultiMap(Relation r) {
	this->capacity = 4;
    this->elems = new TElem[capacity];
    this->next = new int[capacity];
    this->head = -1;
    for(int i=0; i<this->capacity-1; i++){
        this->next[i] = i+1;
    }
    this->next[capacity-1] = -1;
    this->firstEmpty = 0;
    this->nrElems = 0;
    this->relation = r;

}

//Bester Fall:0(1)
//Schlimmster Fall: 0(n)
//Durchschnitt : 0(n)
//Allgemein: O(n)
void SortedMultiMap::add(TKey c, TValue v) {
    //resize
    if(firstEmpty==-1){
        capacity=capacity*2;
        TElem *newElems = new TElem[capacity];
        int *newNext = new int[capacity];
        for(int i = 0; i < nrElems; i++){
            newElems[i] = elems[i];
            newNext[i] = next[i];
        }
        delete[] elems;
        delete[] next;
        next = newNext;
        elems = newElems;
        //markieren alle freien Stellen
        firstEmpty = nrElems;
        for(int i=nrElems; i<this->capacity-1; i++){
            this->next[i] = i+1;
        }
        next[capacity-1] = -1;
    }
    int indexNew = firstEmpty;
    elems[indexNew].first = c;
    elems[indexNew].second = v;
    //wenn kein elem hinzugefugt wurde

    if(head==-1){
        head = firstEmpty;
        firstEmpty = next[firstEmpty];
        next[indexNew] = -1;

    }
    else {
        //wir ändern nur index
        int indexCurrent = head;
        int indexPrevious = -1;
        firstEmpty = next[firstEmpty];

        while (!relation(elems[indexNew].first, elems[indexCurrent].first) and indexCurrent != -1) {
            indexPrevious = indexCurrent;
            indexCurrent = next[indexCurrent];

        }
        //am Anfang einfügen
        if (indexPrevious == -1) {
            next[indexNew] = head;
            head = indexNew;
        } else {
            //normalfall
            next[indexNew] = indexCurrent;
            next[indexPrevious] = indexNew;

        }
    }

    nrElems++;

}
//Best: 0(1)
//Worst: 0(n)
//Durschschnitt & allgemein: O(n)
vector<TValue> SortedMultiMap::search(TKey c) const {

    vector<TValue> values;
    int current = head;
    while(current != -1){
        if(elems[current].first == c){
            values.push_back(elems[current].second);
        }
        current = next[current];
    }
    return vector<TValue>(values.begin(), values.end());
}

//Bester Fall:0(1)
//Schlimmster Fall: 0(n)
//Durschnitt: 0(n)
//Allgemein: O(n)
bool SortedMultiMap::remove(TKey c, TValue v) {

    int current = head;
    int previous = -1;

    while(current!=-1 and (this->elems[current].first != c or this->elems[current].second !=v)){
        previous = current;
        current = next[current];
    }
    if (current!=-1){
        if(current == head){
            this->head = next[head];
        }
        else{
            next[previous] = next[current];
        }
        next[current] = this->firstEmpty;
        this->firstEmpty = current;
        nrElems--;
        return true;
    }
    return false;
}

//Komplexity: 0(1)
int SortedMultiMap::size() const {
	return nrElems;
}
//Komplexity: 0(1)
bool SortedMultiMap::isEmpty() const {
    if(head==-1) return true;
	return false;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}
//Komplexity: 0(1)
SortedMultiMap::~SortedMultiMap() {
	delete[] elems;
    delete[] next;
}
//Best:0(n)
//Worst: 0(n*m)
//Allgemein:O(n*m)
/*function key_count is :
 *pre: slla ist ein slla
 *post: ein neuer vector von pairs wird geschafft, mit jedem key und dessen Frequenz
 *keys[]
 *bool found
 *currentIndex <- head
 *currentKey <- elems[head].first
 *while currentIndex not -1 do:
 *  found <- false
 *  for i <- 0, keys.size(), execute
 *      if keys[i].first == currentKey then
 *          found <- true
 *          keys[i].second += 1
 *       end-if
 *       end-for
 *    if not found do
 *      newpair <- currentKey, 1
 *      keys[] <- newpair
 *    end-if
 * currentIndex = next[currentIndex]
 * currentKey = elems[currentIndex].first
 * end-While
 * return keys
 */
vector<pair<TKey, int>> SortedMultiMap::key_count(){
    vector<pair<TKey , int>> keys;
    bool found;
    TKey currentKey = elems[head].first;
    int currentIndex = head;
    while(currentIndex!=-1){
        found = false;
        for(int i =0; i<keys.size(); i++){
            if(keys[i].first == currentKey){
                found = true;
                keys[i].second++;
            }
        }
        if(!found){
            pair<TKey,int> newpair;
            newpair.first = currentKey;
            newpair.second = 1;
            keys.push_back(newpair);
        }
        currentIndex = next[currentIndex];
        currentKey = elems[currentIndex].first;
    }
    return keys;

}