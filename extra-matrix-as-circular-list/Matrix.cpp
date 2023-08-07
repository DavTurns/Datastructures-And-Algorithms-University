#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
    this->nrOfLines = nrLines;
    this->nrOfColumns = nrCols;

    head = new CLLNode;
    head->info = 0;
    head->line = -1;
    head->column = -1;

    CLLNode* prevNode = head;
    CLLNode* newNode;

    //init all columnheadernodes
    for(int i = 0; i<nrOfColumns;i++){

        //new Node init
        newNode = new CLLNode;
        newNode->info = 0;
        newNode->line = -1;
        newNode->column = i;
        newNode->nextLine = newNode;

        //connect
        prevNode->nextColumn = newNode;
        prevNode = newNode;

        //if newNode is the last headernode
        if(i == nrCols-1){
            newNode->nextColumn = head;
        }
    }

    //init all lineheadernodes
    prevNode = head;
    for(int i = 0; i<nrOfLines;i++){

        //new Node init
        newNode = new CLLNode;
        newNode->info = 0;
        newNode->line = i;
        newNode->column = -1;
        newNode->nextColumn = newNode;

        //connect
        prevNode->nextLine = newNode;
        prevNode = newNode;

        //if newNode is the last headernode
        if(i == nrOfLines-1){
            newNode->nextLine = head;
        }
    }
}


int Matrix::nrLines() const {
	return nrOfLines;
}


int Matrix::nrColumns() const {
	return nrOfColumns;
}


TElem Matrix::element(int i, int j) const {

    //check if searched position is valid
    if(i >=nrOfLines or j >=nrOfColumns or i < 0 or j < 0){
        throw exception();
    }
	CLLNode* currentNode = head;

    while(currentNode->column != j) currentNode = currentNode->nextColumn;
    while(currentNode->line != i){
        currentNode = currentNode->nextLine;

        //if not found, -1 means -> Node is headernode
        if(currentNode->line > i or currentNode->line == -1){
            return NULL_TELEM;
        }
    }
    return currentNode->info;
}

TElem Matrix::modify(int i, int j, TElem e) {

    //check if searched position is valid
    if(i >=nrOfLines or j >=nrOfColumns or i < 0 or j < 0){
        throw exception();
    }

    //starting from head
    CLLNode* currentNode = head;
    CLLNode* prevNode;
    CLLNode* deletedNode;

    //travel to column
    while(currentNode->column != j) currentNode = currentNode->nextColumn;

    //travel to line
    while(currentNode->line != i){
        prevNode = currentNode;
        currentNode = currentNode->nextLine;

        //if Node with line found
        if(currentNode->line == i){
            TElem prevValue = currentNode->info;

            //if Node has to be deleted
            if(e == 0){
                //save Node adress
                deletedNode = currentNode;

                prevNode->nextLine = currentNode->nextLine;

                currentNode = head;
                int k;
                //travel to Line
                for(k = 0; k<=i; k++) currentNode = currentNode->nextLine;

                //travel to column
                while(currentNode!=deletedNode){
                    prevNode = currentNode;
                    currentNode = currentNode->nextColumn;
                }
                prevNode->nextColumn = currentNode->nextColumn;
                delete deletedNode;

            } else currentNode->info = e;
            return prevValue;
        }

        //if not found
        if(currentNode->line > i or currentNode->line == -1){

            if(e == 0) return NULL_TELEM;

            CLLNode* newNode = new CLLNode;
            newNode->info = e;
            newNode->line = i;
            newNode->column = j;

            newNode->nextLine = prevNode->nextLine;
            prevNode->nextLine = newNode;

            currentNode = head;
            while(currentNode->line != i) currentNode = currentNode->nextLine;

            //if this is the first added node in this line
            if(currentNode->nextColumn == currentNode){
                currentNode->nextColumn = newNode;
                newNode->nextColumn = currentNode;
                return NULL_TELEM;
            }
            prevNode = currentNode;
            currentNode = currentNode->nextColumn;

            while(currentNode->column < j and currentNode->column != -1){
                prevNode = currentNode;
                currentNode = currentNode->nextColumn;
            }
            prevNode->nextColumn = newNode;
            newNode->nextColumn = currentNode;
            return NULL_TELEM;
        }
    }
    //if already exists an entry
    TElem lastelem = currentNode->info;
    currentNode->info = e;
	return lastelem;
}

Matrix::~Matrix() {
    CLLNode* currentColumnHeader = head;
    CLLNode* currentNode;
    CLLNode* deletedNode;

    //for everycolumnheader, delete its column
    for(int i = 0; i<= nrOfColumns; i++){
        currentNode = currentColumnHeader;
        currentNode = currentNode->nextLine;

        while(currentNode!=currentColumnHeader){
            deletedNode = currentNode;
            currentNode = currentNode->nextLine;
            delete deletedNode;
        }

        deletedNode = currentColumnHeader;
        currentColumnHeader = currentColumnHeader->nextColumn;
        delete deletedNode;
    }
}


