#include <iostream>
#include <cstring>
#include <fstream>
#include "Tree.h"

using namespace std;

bool search(Tree* head, int input);
void printTree(Tree* head, int space);
void treeAdd(Tree* newNode, Tree* current, Tree* & head);
void treeRemove(Tree* current, Tree* &head, Tree* parent, int data);


int main(){
Tree* tree; 
char input[100];
char input2[100];
int input3 = 0;
int spacing = 3;
char input4[100];
bool running = true;
while(running == true){
cout << "Welcome to the Binary Search Tree! You can add numbers to the tree (ADD), print the tree (PRINT), and search numbers in the tree (SEARCH)." << endl; 
cout << "As an aside, make sure you're not entering duplicate numbers (Ones you've already entered or have added via file). Valid entries include anything in the range from 1-999." << endl;    
cin >> input;
    if(strcmp(input, "ADD") == 0){
        cout << "Do you want to add via direct input (INPUT) or via file (FILE)" << endl;
        cin >> input2;
        if(strcmp(input2, "INPUT") == 0){
            cout << "Enter the number that you want to add to the tree." << endl;
            cin >> input3;
            Tree* newNode = new Tree(input3);
            treeAdd(newNode, tree, tree);
        }
        else if(strcmp(input2, "FILE") == 0){
        int temp = 0;
        cout << "Enter a file name: (e.g. filename.txt)" << endl;
        cin >> input4;
        //Opens the file and adds the numbers into an array
	    fstream nums;
        nums.open(input4);
        for(int i = 0; i < 100; i++){
            nums >> temp;
            //Adds the node to the tree
            Tree* newNode = new Tree(temp);
            treeAdd(newNode, tree, tree);
	        }
        }
    } 
    else if(strcmp(input, "PRINT") == 0){
        printTree(tree, spacing);
    }
    else if(strcmp(input, "SEARCH") == 0){
        cout << "What's the number that you want to search for?" << endl;
        cin >> input3;
        search(tree, input3);
        }  
    }
}

void treeAdd(Tree* newNode, Tree* current, Tree* & head){
    if(head == NULL){
    head = newNode;
    return;
    }
    else if(newNode->getData() > current->getData()){ 
        if(current->getRight() == NULL){
        current->setRight(newNode);
        return;
            }
        else{
            treeAdd(head, current->getRight(), newNode);
        }
        }
    else if(newNode->getData() < current->getData()){
        if(current->getLeft() == NULL){
        current->setRight(newNode);
        return;
            }
        else{
            treeAdd(head, current->getLeft(), newNode);
        }
    }
    else {
        if(current->getLeft() == NULL){
            current->setLeft(newNode);
            return;
        }
        else if(current->getRight() == NULL){
            current->setRight(newNode);
            return;
        }
        return;
    }
}
//Print function from heap
void printTree(Tree* head, int space){
if(head == NULL){
        return;
    }
    //This creates space between levels of the tree
    space = space + 10;

    //Start from the right
    printTree(head->getRight(), space);

    //Print the current node after a new line
    cout << endl;
    for(int i = 0; i < space; i++){
        cout << " ";
    }
    cout << head->getData() << '\n';
    //Onto the left
    if(head->getLeft() != NULL){
    printTree(head->getLeft(), space);
    }
}

bool search(Tree* head, int input){
    if(head == NULL){
        cout << "Sorry, but your number isn't in the tree as it's empty." << endl;
        return false;
    }
    else if(head->getData() != input && head != NULL){
        if(head->getData() > input){
            search(head->getLeft(), input);
            }
        else if(head->getData() < input){
            search(head->getRight(), input);
            }
        }
    else if(head->getData() == input){
        cout << "Your number is present in the tree!" << endl;
        return true;
    }
    else{
        cout << "Sorry, your number isn't in the tree." << endl;
        return false;
    }
}