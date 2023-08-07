#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

//General complexity: 0(1)
SortedIteratedList::SortedIteratedList(Relation r) {
	//TODO - Implementation
    ordnungsrelation = r;
    head = NULL;
    nrElems = 0;
    //d1
}

//General complexity: 0(1)
int SortedIteratedList::size() const {
	//TODO - Implementation
    return nrElems;
}

//General complexity: 0(1)
bool SortedIteratedList::isEmpty() const {
	//TODO - Implementation
    if (head == NULL)
        return true;
    return false;
    //d1
}

//General complexity: 0(1)
ListIterator SortedIteratedList::first() const {
	//TODO - Implementation
	return ListIterator(*this);
}

//General complexity: 0(1)
TComp SortedIteratedList::getElement(ListIterator poz) const {
	//TODO - Implementation
    if(!poz.valid())
        throw exception();
    return poz.getCurrent();
    //d1
}

/*
 * best case: 0(1)
 * worst case: 0(n)
 * average case:0(n)
 * general complexity:O(n)
 */
TComp SortedIteratedList::remove(ListIterator& poz) {
	//TODO - Implementation
    if(!poz.valid()){
        throw exception();
    }
    //
    nrElems--;

    SLLNode* aux = head;
    TComp removedvalue;

    //EXTRA: wenn wir den Kopf entfernen
    if(poz.currentElement == head){
        head = head->next;
        poz.currentElement->next = NULL;
        removedvalue =aux->info;
        delete aux;
        poz.currentElement = head;
        return removedvalue;
    }


    //SONST
    while(aux->next != poz.currentElement){
        aux = aux->next;
    }

    //EXTRA: wenn wir am ende entfernen möchten
    if(poz.currentElement->next == NULL){
        aux->next = NULL;
    }else{
        aux->next = poz.currentElement->next;
    }

    poz.currentElement->next = NULL;
    removedvalue = poz.currentElement->info;
    delete poz.currentElement;
    poz.currentElement = aux->next;

    if(isEmpty())
        head = NULL;

    return removedvalue;
}

/*
 * best case:0(1)
 * worst case:0(n)
 * average case:0(n)
 * general complexity:O(n)
 */
ListIterator SortedIteratedList::search(TComp e) const{
	//TODO - Implementation
    ListIterator it(*this);
    while(it.valid()&&it.currentElement->info != e) {
        it.next();
    }
	return it;
}

/*
 * best case:0(1)
 * worst case:0(n)
 * average case:0(n)
 * general complexity:O(n)
 */
void SortedIteratedList::add(TComp e) {
	//TODO - Implementation

    nrElems++;

    SLLNode* currentNode = head;
    SLLNode* prevNode = NULL;
    SLLNode* newNode = new SLLNode;
    newNode->info = e;

    if(isEmpty()){
        head = newNode;
        newNode->next = NULL;
        return;
    }

    while(!(ordnungsrelation(e,currentNode->info))) {
        prevNode = currentNode;
        currentNode = currentNode->next;

        //wenn der Node am Ende eingefügt wird
        if(currentNode == NULL) {
            prevNode->next = newNode;
            newNode->next = NULL;
            return;
        }
    }

    //Wenn der Node am Anfang eingefügt wird
    if(prevNode == NULL){
        newNode->next = currentNode;
        head = newNode;
        return;
    }
    newNode->next = currentNode;
    prevNode->next = newNode;
}

//bestcase 0(1) -> k<2
//worstcase 0(n)
//averagecase 0(n)
//generalcase sonst 0(n)

void SortedIteratedList::deleteKElem(int k) {

    if (k < 2){
        throw exception();
    }

    ListIterator it(*this);
    int counter = 1;
    while(it.valid()){

        if(counter % k == 0){
            //delete node
            remove(it);
            counter++;
            if(!it.valid()){
                break;
            }
        }
        counter++;
        it.next();
    }
}


/*
 * general complexity: 0(n)
 */
SortedIteratedList::~SortedIteratedList() {
    SLLNode* currentNode = head;
    while (currentNode != NULL) {
        SLLNode* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
    head = NULL;
	//TODO - Implementation
}
