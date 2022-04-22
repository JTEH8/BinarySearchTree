//Header guard
#ifndef TREE_H
#define TREE_H
#include <cstring>

//Tree Clas
class Tree{
public:
    //Vairables
    int data;
    Tree* left;
    Tree* right;
    //Constructor and Destructor
    Tree(int newVal);
    ~Tree();
//Function prototypes
void setValue(int newVal);
void setLeft(Tree* newLeft);
void setRight(Tree* newRight);
int getData();
Tree* getRight();
Tree* getLeft();
};

#endif