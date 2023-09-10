#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;


//General complexity: 0(1)
ListIterator::ListIterator(const SortedIteratedList &list) : list(list) {
    first();
}

//General complexity: 0(1)
void ListIterator::first() {
    currentElement = list.head;
    //d1
}

//General complexity: 0(1)
void ListIterator::next() {
    if (!valid())
        throw exception();
    currentElement = currentElement->next;
}

//General complexity: 0(1)
bool ListIterator::valid() const {
    if (currentElement != NULL)
        return true;
    return false;
}

//General complexity: 0(1)
TComp ListIterator::getCurrent() const {
    if (valid())
        return currentElement->info;
    throw exception();
}



