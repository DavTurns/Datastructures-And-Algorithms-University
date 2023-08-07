#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;


//General complexity: 0(1)
ListIterator::ListIterator(const SortedIteratedList &list) : list(list){
	//TODO - Implementation
    first();
}

//General complexity: 0(1)
void ListIterator::first(){
    //TODO - Implementation
    currentElement = list.head;
    //d1
}

//General complexity: 0(1)
void ListIterator::next(){
	//TODO - Implementation
    if(!valid())
        throw exception();
    currentElement = currentElement->next;
    //d1
}

//General complexity: 0(1)
bool ListIterator::valid() const{
	//TODO - Implementation
    if(currentElement != NULL)
        return true;
	return false;
}

//General complexity: 0(1)
TComp ListIterator::getCurrent() const{
	//TODO - Implementation
    if(valid())
        return currentElement->info;
	throw exception();
}



