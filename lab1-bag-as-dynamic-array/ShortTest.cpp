#include "ShortTest.h"
#include <assert.h>
#include "Bag.h"
#include "BagIterator.h"
#include <iostream>
#include <string>

void test_has_same_elements() {
    cout << "test_has_same_elements...";
    Bag b1;
    b1.add(5);
    b1.add(5);
    b1.add(5);
    b1.add(3);
    b1.add(3);
    b1.add(1);

    Bag b2;
    b2.add(5);
    b2.add(5);
    b2.add(3);
    b2.add(1);
    b2.add(5);
    b2.add(3);

    Bag b3;

    //zwei Bags mit selbe Elemente
    assert(b1.has_same_elements(b2));
    //wir entfernen ein Element
    b2.remove(5);
    assert(!b1.has_same_elements(b2));
    //mit einem leeren Bag
    assert(!b1.has_same_elements(b3));
    //mit sich selbst
    assert(b3.has_same_elements(b3));
    cout << "done\n";
}


void testAll() {
    Bag b;
    assert(b.isEmpty() == true);
    assert(b.size() == 0);
    b.add(5);
    b.add(1);
    b.add(10);
    b.add(7);
    b.add(1);
    b.add(11);
    b.add(-3);

    assert(b.size() == 7);
    assert(b.search(10) == true);
    assert(b.search(16) == false);
    assert(b.nrOccurrences(1) == 2);
    assert(b.nrOccurrences(7) == 1);
    assert(b.remove(1) == true);
    assert(b.remove(6) == false);
    assert(b.size() == 6);
    assert(b.nrOccurrences(1) == 1);
    BagIterator it = b.iterator();
    it.first();

    while (it.valid()) {
        TElem e = it.getCurrent();
        it.next();
    }
    cout << "ende";

}


