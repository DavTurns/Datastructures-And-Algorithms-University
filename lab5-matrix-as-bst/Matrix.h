#pragma once

#include<tuple> // for tuple

using namespace std;
//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class MatrixIterator;

struct BSTNode {
    tuple<int, int, TElem> info;
    BSTNode *left;
    BSTNode *right;
};

class Matrix {
    friend class MatrixIterator;

private:
    BSTNode *root;

    int relation(tuple<int, int, TElem> tuple1, tuple<int, int, TElem> tuple2) const;

    int nrOfLines, nrOfCols;

public:

    MatrixIterator iterator();

    //constructor
    Matrix(int nrLines, int nrCols);

    //returns the number of lines
    int nrLines() const;

    //returns the number of columns
    int nrColumns() const;

    //returns the element from line i and column j (indexing starts from 0)
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem element(int i, int j) const;

    //modifies the value from line i and column j
    //returns the previous value from the position
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem modify(int i, int j, TElem e);

    //helping function delete Node
    void deleteNode(BSTNode *Node);

    // destructor
    ~Matrix();


};
