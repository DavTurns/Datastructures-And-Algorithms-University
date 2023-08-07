//
// Created by Latitude on 09.06.2023.
//

#pragma once
#include "Matrix.h"

class MatrixIterator {
    friend class Matrix;
private:
    const Matrix& matrix;

    MatrixIterator(const Matrix& m);

    //TODO - Representation
    BSTNode* currentNode;
    int line;
    int column;

public:

    void first();
    void next_line();
    void next_column();
    bool valid() const;
    TElem getCurrent() const;
};

