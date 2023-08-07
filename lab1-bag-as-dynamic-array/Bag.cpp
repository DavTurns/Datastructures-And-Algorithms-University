#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <utility>

using namespace std;

//general 0(1)
Bag::Bag() {
	//TODO - Implementation
    this->capacity = 4;
    this->nr_of_pairs = 0;
    this->bag = new pair<TElem, int>[this->capacity];
}

/* n = this->nr_of_pairs, m = other.nr_of_pairs
 * worst-case: 0(m*n) => 0(n²)??
 * best-case: 0(m)
 *
 * general-case:O(m*n)
 */
bool Bag::has_same_elements(const Bag &other) {
    //TODO - Implementation
    for(int i = 0; i<this->nr_of_pairs; i++){
        pair<TElem,int> currentpair = this->bag[i];
        bool dasselbe_gefunden = false;
        for(int j = 0; j < this->nr_of_pairs; j++) {
            if(currentpair==other.bag[j]){
                dasselbe_gefunden = true;
            }
        }
        if(!dasselbe_gefunden) {
            return false;
        }
    }
    return true;

}


const pair<TElem,int> Bag::operator[](int position) const {
    return this->bag[position];
}

//general:0(1)
int Bag::get_nr_of_pairs() const {
    return this->nr_of_pairs;
}

//bestcase: 0(1) amortisiert
//worstcase: 0(n)
//average: 0(n)
//general O(n)
void Bag::add(TElem elem) {

     //egal was passiert, es wird in jedem fall ein Element hinzugefügt
    for(int i = 0; i<this->nr_of_pairs; i++) {
		if (this->bag[i].first == elem) {
			bag[i].second++;
			return;
		}
	}

	//verify if current array is full occupied with pairs
	if (this->nr_of_pairs == this->capacity) {
		this->capacity = this->capacity*2;
		pair<TElem, int> *neuesarray;
		neuesarray = new pair<TElem, int>[this->capacity];

        //copy all values into new array
		for(int i = 0; i<this->nr_of_pairs; i++) {
			neuesarray[i] = this->bag[i];
		}
        //delete old array
		delete[] this->bag;
        //set pointer of bag to new array
		this->bag = neuesarray;
	}

    //add new tuple with (TElem, 1) at the end of array
	this->bag[this->nr_of_pairs].first = elem;
	this->bag[this->nr_of_pairs].second = 1;
    this->nr_of_pairs++;

}

//bestcase: 0(1) amortisiert
//worstcase: 0(n)
//average: 0(n)
//general O(n)
bool Bag::remove(TElem elem) {
	for(int i = 0; i<this->nr_of_pairs; i++) {
		if (this->bag[i].first == elem) {
			//wenn das gefundene Element nicht das letzte Tupel ist
            if (this->bag[i].second > 1) {
                this->bag[i].second--;
            } else {
                //if frequency of found tuple is 1 before removing, remove the tuple from array
                if(i < this->nr_of_pairs - 1) {
                    this->bag[i] = this->bag[this->nr_of_pairs - 1];
                }
                this->nr_of_pairs--;
            }

			//wenn gefundene Element doch das letzte Tupel ist, passiert nichts und es wird nur nr_of_elems dekrementiert
            if(this->nr_of_pairs*4 == this->capacity) {
                this->capacity = this->capacity/2;
                pair<TElem, int> *neuesarray;
                neuesarray = new pair<TElem, int>[this->capacity];

                //copy all values into new array
                for(int i = 0; i<this->nr_of_pairs; i++) {
                    neuesarray[i] = this->bag[i];
                }
                //delete old array
                delete[] this->bag;
                //set pointer of bag to new array
                this->bag = neuesarray;
            }
			return true;
		}
	}
	return false;
}

/*
 * bestcase:0(1)
 * worstcase: 0(n)
 * average case:0(n/2) = 0(n)
 * general: O(n)
  */
bool Bag::search(TElem elem) const {
	//TODO - Implementation
	for(int i = 0; i< this->nr_of_pairs; i++) {
		if (this->bag[i].first == elem) {
			return true;
		}
	}
	return false;
}

/*
 * bestcase:0(1)
 * worstcase: 0(n)
 * average case:0(n/2) = 0(n)
 * general: O(n)
  */
int Bag::nrOccurrences(TElem elem) const {
	//TODO - Implementation
	for(int i = 0; i< this->nr_of_pairs; i++) {
		if (this->bag[i].first == elem) {
			return this->bag[i].second;
		}
	}
	return 0;
}


/*
 * general case: 0(n)
 * */
int Bag::size() const {
	//TODO - Implementation
	int total_number_of_elements = 0;
    //cout << "\n";
	for(int i = 0; i<this->nr_of_pairs;i++) {
		total_number_of_elements += this->bag[i].second;
        //cout << this->bag[i].first << ", freq: " << this->bag[i].second << "\n";
	}
	return total_number_of_elements;
}

//general:0(1)
bool Bag::isEmpty() const {
	//TODO - Implementation
	if(this->nr_of_pairs == 0){
		return 1;
	}
	return 0;
}
//general:0(1)
BagIterator Bag::iterator() const {
	return BagIterator(this);
}
//general:0(1)
Bag::~Bag() {
    delete[] this->bag;
}

