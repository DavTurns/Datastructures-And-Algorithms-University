//
// Created by Latitude on 09.06.2023.
//

#include "MatrixIterator.h"
#include <exception>

/*
 * pre:m E M, m ist eine matrix
 * post: i E I, wobei i ist ein iterator, welches auf 0,0 zeigt
 *
 *
 * best: 0(1)
 * worst: 0(n)
 * average: 0(logn)
 * general: O(n)
 * */
MatrixIterator::MatrixIterator(const Matrix &m) : matrix(m) {
    first();
}

/*
 * pre: i E I, i ist ein iterator welches auf irgendein element zeigt, oder invalid sein kann
 * post: i' E I, i' ist ein iterator welches auf die das Element von Zeile 0 Spalte 0 zeigt
 *
 * best: 0(1)
 * worst: 0(n)
 * average: 0(logn)
 * general: O(n)
 * */
void MatrixIterator::first() {
    line = 0;
    column = 0;
    BSTNode *tempnode = matrix.root;

    while (tempnode != nullptr) {
        if (get<0>(tempnode->info) == 0 and get<1>(tempnode->info) == 0) {
            break;
        }
        tempnode = tempnode->left;
    }
    currentNode = tempnode;
}

/*
 * pre: i E I das auf element mit (l,c) zeigt von m E M
 * post: i' E I das auf element mit (l+1,c) zeigt von m E M, wirft exception, wenn iterator invalid ist
 *
 * best: 0(1)
 * worst: 0(n)
 * average: 0(logn)
 * general: O(n)
 * */
void MatrixIterator::next_line() {
    if (!valid()) throw std::exception();

    line++;

    tuple<int, int, TElem> searchedpos = {line, column, 0};
    BSTNode *currentNode = matrix.root;
    int r;

    //suche Nach Node mit eigenschaft von Line und column
    while (currentNode != nullptr) {
        r = matrix.relation(searchedpos, currentNode->info);

        if (r == -1) {
            currentNode = currentNode->left;
        }
        if (r == 1) {
            currentNode = currentNode->right;
        }
        if (r == 0) {
            break;

        }

    }
    this->currentNode = currentNode;


    //wenn nicht gefunden dann setze CurrentNode auf NULL
}

/*
 * * pre: i E I das auf element mit (l,c) zeigt von m E M
 * post: i' E I das auf element mit (l,c+1) zeigt von m E M, wirft exception, wenn iterator invalid ist
 *
 *
 * best: 0(1)
 * worst: 0(n)
 * average: 0(logn)
 * general: O(n)
 * */
void MatrixIterator::next_column() {
    if (!valid()) throw std::exception();

    column++;

    tuple<int, int, TElem> searchedpos = {line, column, 0};
    BSTNode *currentNode = matrix.root;
    int r;

    //suche Nach Node mit eigenschaft von Line und column
    while (currentNode != nullptr) {
        r = matrix.relation(searchedpos, currentNode->info);

        if (r == -1) {
            currentNode = currentNode->left;
        }
        if (r == 1) {
            currentNode = currentNode->right;
        }
        if (r == 0) {
            break;

        }

    }
    this->currentNode = currentNode;


    //wenn nicht gefunden dann setze CurrentNode auf NULL

    //suche Nach Node mit eigenschaft von Line und column
}

//general: 0(1)
//pre i E I ist ein iterator
// post returns true, falls i valid, sonst false
bool MatrixIterator::valid() const {
    if (column >= matrix.nrOfCols or line >= matrix.nrOfLines) return false;
    else return true;
}

//general: 0(1)
//pre: i E I, m E M
//post: i E I ,returns e wobei TElem ist, das auf aktuelle Element(l,c)  wiedergibt
TElem MatrixIterator::getCurrent() const {
    if (!valid()) throw std::exception();
    if (currentNode == nullptr) return 0;
    return get<2>(currentNode->info);
}