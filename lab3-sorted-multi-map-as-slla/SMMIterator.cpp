#include "SMMIterator.h"
#include "SortedMultiMap.h"

//0(n)
SMMIterator::SMMIterator(const SortedMultiMap &d) : map(d) {
    this->index = map.head;
}

//0(1)
void SMMIterator::first() {
    this->index = map.head;
}

//0(1)
void SMMIterator::next() {
    if (!valid()) {
        throw exception();
    }
    this->index = map.next[index];
}

//0(1)
bool SMMIterator::valid() const {
    if (this->index == -1) {
        return false;
    }
    return true;
}

//0(1)
TElem SMMIterator::getCurrent() const {
    if (valid()) {
        return map.elems[index];
    }
    throw exception();
}


