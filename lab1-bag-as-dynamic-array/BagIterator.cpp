#include "BagIterator.h"
#include "Bag.h"
#include <iostream>

using namespace std;

//general:0(1)
BagIterator::BagIterator(const Bag *c) : bag(c) {
    this->index = 0;
    this->index_frequenz = 1;
    //TODO - Implementation
}

//general:0(1)
void BagIterator::first() {

    this->index = 0;
    this->index_frequenz = 1;
    if (!this->valid()) {
        throw exception();
    }

    //TODO - Implementation
}

//general:0(1)
void BagIterator::next() {
    //TODO - Implementation
    if (!this->valid()) {
        throw exception();
    }
    if (this->index_frequenz < this->bag->bag[index].second) {
        this->index_frequenz++;
    } else {
        this->index++;
        this->index_frequenz = 1;
    }
}

//general:0(1)
bool BagIterator::valid() const {
    //TODO - Implementation
    if (this->index < this->bag->get_nr_of_pairs()) {
        return true;
    }
    return false;
}

//general:0(1)
TElem BagIterator::getCurrent() const {
    if (!this->valid()) {
        throw exception();
    }
    return this->bag->bag[this->index].first;
}

