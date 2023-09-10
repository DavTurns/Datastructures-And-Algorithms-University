#include "Matrix.h"
#include "MatrixIterator.h"
#include <exception>

using namespace std;

//general:0(1)
Matrix::Matrix(int nrLines, int nrCols) {
    if (nrLines <= 0 || nrCols <= 0) {
        throw exception();
    }
    this->nrOfLines = nrLines;
    this->nrOfCols = nrCols;
    root = nullptr;
}
//general:0(1)
int Matrix::relation(tuple<int, int, TElem> tuple1, tuple<int, int, TElem> tuple2) const {
    /*
     * returns -1 if node1 "<" node 2 lexicographically
     * returns 0 if node1 "=" node 2 "
     * returns 1 if node1 "> node 2 "
     * */

    if (get<0>(tuple1) < get<0>(tuple2)) return -1;
    if (get<0>(tuple1) > get<0>(tuple2)) return 1;
    if (get<1>(tuple1) < get<1>(tuple2)) return -1;
    if (get<1>(tuple1) > get<1>(tuple2)) return 1;
    return 0;
}

//general:0(1)
int Matrix::nrLines() const {
    return nrOfLines;
}

//general:0(1)
int Matrix::nrColumns() const {
    return nrOfCols;
}
/*best case: 0(1)
 *worst case: 0(n)
 *average case: 0(log n)
 *general case: O(n)
 * */
TElem Matrix::element(int i, int j) const {

    //check if i and j are valid
    if (i >= nrOfLines || j >= nrOfCols || i < 0 || j < 0) throw exception();

    tuple<int, int, TElem> searchedpos = {i, j, 0};
    BSTNode *currentNode = root;
    while (currentNode != nullptr) {
        int r = relation(searchedpos, currentNode->info);
        switch (r) {
            case -1:
                currentNode = currentNode->left;
                break;
            case 0:
                return get<2>(currentNode->info);
            case 1:
                currentNode = currentNode->right;
                break;
        }
    }
    return NULL_TELEM;
}

/*best case: 0(1)
 *worst case: 0(n)
 *average case: 0(log n)
 *general case: O(n)
 * */
TElem Matrix::modify(int i, int j, TElem e) {
    //check if i and j are valid
    if (i >= nrOfLines || j >= nrOfCols || i < 0 || j < 0) throw exception();

    //EXTRACASE: if no element stored in matrix
    if(root == nullptr){
        BSTNode *newNode = new BSTNode();
        get<0>(newNode->info) = i;
        get<1>(newNode->info) = j;
        get<2>(newNode->info) = e;
        newNode->left = nullptr;
        newNode->right = nullptr;

        root = newNode;
        return NULL_TELEM;
    }

    //init comparison object
    tuple<int, int, TElem> searchedpos = {i, j, 0};
    BSTNode *previousNode = nullptr;
    BSTNode *currentNode = root;
    int r;
    int previous_r;

    //go through bst
    while (currentNode != nullptr) {
        previous_r = r;
        r = relation(searchedpos, currentNode->info);
        previousNode = currentNode;

        if (r == -1) {
            currentNode = currentNode->left;
        }

        if (r == 1) {
            currentNode = currentNode->right;
        }
        if (r == 0) {

            //if mode is delete
            if(e == 0){
                TElem oldvalue = get<2>(currentNode->info);

                //deleting Node by switching with the following node
                BSTNode *foundNode = currentNode;


                if(currentNode->right == nullptr){
                    if(previous_r == -1) previousNode->left = currentNode->left;
                    if(previous_r == 1) previousNode->right = currentNode->left;
                    delete currentNode;
                    return oldvalue;
                }
                previousNode = currentNode;
                currentNode = currentNode->right;

                bool gone_left = false;
                while (currentNode->left != nullptr) {
                    previousNode = currentNode;
                    currentNode = currentNode->left;
                    gone_left = true;
                }

                foundNode->info = currentNode->info;

                if(!gone_left){
                    foundNode->right = currentNode->right;
                } else {
                    previousNode->left = currentNode->right;
                }

                //take the value of the following Node
                delete currentNode;

                return oldvalue;
            }
            TElem oldvalue = get<2>(currentNode->info);
            get<2>(currentNode->info) = e;
            return oldvalue;
        }
    }

    //if position not found
    if(e == 0) return NULL_TELEM;

    //creating new node
    BSTNode *newNode = new BSTNode();
    get<0>(newNode->info) = i;
    get<1>(newNode->info) = j;
    get<2>(newNode->info) = e;
    newNode->left = nullptr;
    newNode->right = nullptr;

    //set connection
    if (r == -1) previousNode->left = newNode;
    if (r == 1) previousNode->right = newNode;

    return NULL_TELEM;
}

MatrixIterator Matrix::iterator() {
    return MatrixIterator(*this);
}

void Matrix::deleteNode(BSTNode *Node) {
    if(Node == nullptr) return;
    deleteNode(Node->right);
    deleteNode(Node->left);
    delete Node;
}

//general 0(n)
Matrix::~Matrix() {
    deleteNode(root);
}








