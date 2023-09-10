#include <assert.h>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>
#include <iostream>

using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    } else {
        return false;
    }
}

void testExtra() {
    SortedMultiMap smm = SortedMultiMap(relation1);
    smm.add(1, 2);
    smm.add(2, 5);
    smm.add(1, 3);
    smm.add(1, 8);
    smm.add(2, 2);
    smm.add(3, 4);
    smm.add(2, 8);
    smm.add(3, 13);
    smm.add(5, 2);
    // 1- 3 , 2 - 3 , 3- 2; 5 -1
    vector <pair<TKey, int>> keys = smm.key_count();
    assert(keys[0].first == 1 && keys[0].second == 3);
    assert(keys[1].first == 2 && keys[1].second == 3);
    assert(keys[2].first == 3 && keys[2].second == 2);
    assert(keys[3].first == 5 && keys[3].second == 1);
    std::cout << "Extra Test passed" << endl;

}

void testAll() {
    SortedMultiMap smm = SortedMultiMap(relation1);
    assert(smm.size() == 0);
    assert(smm.isEmpty());
    smm.add(1, 2);
    smm.add(1, 3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector <TValue> v = smm.search(1);
    assert(v.size() == 2);
    v = smm.search(3);
    assert(v.size() == 0);
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()) {
        TElem e = it.getCurrent();
        it.next();
    }
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());
    testExtra();
}

