#include <assert.h>
#include "Matrix.h"
#include "MatrixIterator.h"
#include <string>
#include <iostream>

using namespace std;


void testIterator() {
    cout << "testIterator...";

    Matrix m(4, 4);
    m.modify(0, 0, 5);
    m.modify(0, 1, 3);
    m.modify(0, 2, 6);
    m.modify(1, 1, 2);
    m.modify(2, 0, 1);
    m.modify(2, 2, 8);
    m.modify(3, 3, 4);

    MatrixIterator it = m.iterator();
    //
    int c = 0;
    while (it.valid()) {
        it.next_column();
        c++;
    }
    assert(c == 4);
    it.first();

    c = 0;
    while (it.valid()) {
        it.next_line();
        c++;
    }
    assert(c == 4);

    it.first();
    assert(it.getCurrent() == 5);

    it.next_column();
    assert(it.getCurrent() == 3);
    it.next_column();
    assert(it.getCurrent() == 6);
    it.next_column();
    assert(it.getCurrent() == 0);

    it.next_line();
    assert(it.getCurrent() == 0);
    it.next_line();
    assert(it.getCurrent() == 0);
    it.next_line();
    assert(it.getCurrent() == 4);

    it.first();
    it.next_line();
    assert(it.getCurrent() == 0);

    it.next_column();
    assert(it.getCurrent() == 2);

    it.next_line();
    assert(it.getCurrent() == 0);

    it.next_column();
    assert(it.getCurrent() == 8);


    cout << "done\n";

}

void testAll() {
    Matrix m(4, 4);
    assert(m.nrLines() == 4);
    assert(m.nrColumns() == 4);
    m.modify(1, 1, 5);
    assert(m.element(1, 1) == 5);
    m.modify(1, 1, 6);
    assert(m.element(1, 2) == NULL_TELEM);
    testIterator();
}
