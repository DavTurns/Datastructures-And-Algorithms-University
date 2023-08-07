#include "Bag.h"

class BagIterator
{
    BagIterator(const Bag *c);

//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
    const Bag *bag;
	//TODO  - Representation
	int index;
	int index_frequenz;
public:
	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};
