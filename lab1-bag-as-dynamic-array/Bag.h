#pragma once

#include <utility>
//DO NOT INCLUDE BAGITERATOR
using namespace std;

//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;

class BagIterator;

class Bag {

private:
    //TODO - Representation
    int capacity;
    int nr_of_pairs;

    //DO NOT CHANGE THIS PART
    friend class BagIterator;

public:
    //constructor
    Bag();

    int get_nr_of_pairs() const;

    const pair<TElem, int> operator[](int position) const;

    //adds an element to the bag
    void add(TElem e);

    //removes one occurence of an element from a bag
    //returns true if an element was removed, false otherwise (if e was not part of the bag)
    bool remove(TElem e);

    //checks if an element appearch is the bag
    bool search(TElem e) const;

    //returns the number of occurrences for an element in the bag
    int nrOccurrences(TElem e) const;


    //returns the number of elements from the bag
    int size() const;

    //returns an iterator for this bag
    BagIterator iterator() const;

    //checks if the bag is empty
    bool isEmpty() const;

    bool has_same_elements(const Bag &other);


    //destructor
    ~Bag();

    pair<TElem, int> *bag;
};