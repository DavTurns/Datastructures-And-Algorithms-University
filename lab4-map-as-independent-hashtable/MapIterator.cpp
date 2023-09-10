#include "Map.h"
#include "MapIterator.h"
#include <exception>

using namespace std;

/*
 * best-case:0(1)
 * worst-case:0(m)
 * average-case:0(m)
 * general-case:O(m)
 * */
MapIterator::MapIterator(const Map &d) : map(d) {
    //TODO - Implementation

    first();
}

/*
 * best-case:0(1)
 * worst-case:0(m)
 * average-case:0(m)
 * general-case:O(m)
 * */
void MapIterator::first() {
    //TODO - Implementation
    currentindex = 0;
    while (map.array[currentindex] == nullptr and currentindex < map.capacity) {
        currentindex++;
    }
    if (!valid()) CurrentNode = nullptr;
    else CurrentNode = map.array[currentindex];
}

/*
 * best-case:0(1)
 * worst-case:0(m)
 * average-case:0(m)
 * general-case:O(m)
 * */
void MapIterator::next() {
    //TODO - Implementation
    if (!valid()) throw exception();
    if (CurrentNode->next == nullptr) {
        currentindex++;
        while (map.array[currentindex] == nullptr and currentindex < map.capacity) {
            currentindex++;
        }

        //wenn noch valid ist
        if (currentindex < map.capacity) CurrentNode = map.array[currentindex];
        else CurrentNode = nullptr;
    } else {
        CurrentNode = CurrentNode->next;
    }
}

//general:0(1)
TElem MapIterator::getCurrent() {
    //TODO - Implementation
    if (!valid()) throw exception();
    return CurrentNode->info;
}

//general:0(1)
bool MapIterator::valid() const {
    //TODO - Implementation
    if (currentindex < map.capacity) return true;
    return false;
}


/*removeCurrent(m,mi)
 *
 * pre:m muss eine Map sein mit Elemente und mi ein gültiger map iterator
 * post: throws exception wenn mi nicht valid ist.
 *      mi' = mi mit next element und gelöschtes element worauf es gezeigt hat.
 *      m' = m / TElEM was von removeCurrent gelöscht wurde
 *
 *
 * pseudoCode:
 * subalgorithm removeCurrent(m,mi) is:
 *  if !mi.valid then
 *      @throw exception
 *  endif
 *  key <- mi.getCurrent().first
 *  currentNode <- map.array[currentindex]
 *
 *  previousNode <- NIL
    while currentNode].info.first != key do
        previousNode <- currentNode
        currentNode <- [currentNode].next
    endwhile

    //wenn currentNode am Anfang steht
    if previousNode == nullptr then
        map.array[currentindex] <- [currentNode].next
        mi.next()
    else
        [previousNode].next = [currentNode].next
        mi.next()
    endif

    delete currentNode
 */


/*worst-case:0(n)
 * best-case:0(1)
 * average-case:0(1)
 * general:O(n)
 * */
void MapIterator::removeCurrent() {

    if (!valid()) throw exception();
    TKey key = getCurrent().first;

    Node *currentNode = map.array[currentindex];
    Node *previousNode = nullptr;
    while (currentNode->info.first != key) {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }


    //wenn currentNode am Anfang steht
    if (previousNode == nullptr) {
        map.array[currentindex] = currentNode->next;
        next();
        delete currentNode;
        return;
    }
    previousNode->next = currentNode->next;
    next();
    delete currentNode;
}


