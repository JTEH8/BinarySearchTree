//This was done with reference tO: https://www.geeksforgeeks.org/binary-tree-set-1-introduction/
#include <iostream>
#include <cstring>
#include "Tree.h"

using namespace std;
//Constructors
Tree::Tree(int newVal){
    right = NULL;
    left = NULL;
    data = newVal;
}
//Setting methods
void Tree::setRight(Tree* newRight){
    right = newRight;
}

void Tree::setLeft(Tree* newLeft){
    left = newLeft;
}

void Tree::setValue(int newVal){
   data = newVal;
}
//Get methods
Tree* Tree::getRight(){
    return right;
}

int Tree::getData(){
    return data;
}

Tree* Tree::getLeft(){
    return left;
}


//Destructor
Tree::~Tree(){
    
}