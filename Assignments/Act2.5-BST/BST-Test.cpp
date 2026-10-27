#include <iostream>
using namespace std;

#include "BST.h"

int main() {

    BST<int> bst;
    //bst.insert(50);
    //bst.insert(30);
    //bst.insert(70);
    bst.insert(40);
    bst.insert(20);
    //bst.insert(35);
    bst.insert(10);
    bst.insert(60);
    bst.print();
    bst.visit("preOrder");
    bst.visit("inOrder");
    bst.visit("postOrder");
    bst.remove(20);
    bst.print();


    return 0;
}