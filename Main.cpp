#include <iostream>
#include <cstring>
#include <fstream>
#include "Tree.h"

/*
Author: Jeffrey Teh
Date Completed: 4/21/2022
This is an implementation of a Binary Search Tree via Right and Left child nodes.
Help for this project came from Jayden Huang
*/

using namespace std;
//Function Prototypes
bool search(Tree* head, int input);
void printTree(Tree* head, int space);
void treeAdd(Tree* newNode, Tree* current, Tree* & head);
void treeRemove(Tree* current, Tree* &head, Tree* parent, int data);

//Main method
int main(){
//Initializing variables
Tree* tree = NULL; 
char input[100];
char input2[100];
int input3 = 0;
int spacing = 3;
char input4[100];
bool running = true;
//While the program is running
while(running == true){
//Prompt text
cout << "Welcome to the Binary Search Tree! You can add numbers to the tree (ADD), print the tree (PRINT), delete numbers from the tree (DELETE), and search numbers in the tree (SEARCH). To quit type QUIT." << endl; 
cout << "As an aside, make sure you're not entering duplicate numbers (Ones you've already entered or have added via file). Valid entries include anything in the range from 1-999." << endl;    
//Read in input
cin >> input;
//When adding numbers to the BST
    if(strcmp(input, "ADD") == 0){
        cout << "Do you want to add via direct input (INPUT) or via file (FILE)" << endl;
        //If the user wants to add directly or by file
        cin >> input2;
        //Direct input
        if(strcmp(input2, "INPUT") == 0){
            cout << "Enter the number that you want to add to the tree." << endl;
            cin >> input3;
        //Prevents duplicates
	    if(search(tree, input3) == true){
	      cout << "No duplicate numbers in the tree! Please enter another number." << endl;
	    }
	    else{
	    Tree* newNode = new Tree(input3);
	    treeAdd(newNode, tree, tree);
	    }
	    }
        else if(strcmp(input2, "FILE") == 0){
        int temp = 0;
        cout << "Enter a file name: (e.g. filename.txt)" << endl;
        cin >> input4;
        //Opens the file and adds the numbers one by one to the tree
	    fstream nums;
        nums.open(input4);
        //Does this 10 times
        for(int i = 0; i < 10; i++){
            nums >> temp;
            //Adds the node to the tree
            Tree* newNode = new Tree(temp);
            treeAdd(newNode, tree, tree);
	        }
        }
    }
    //If the user wants to delete
    else if(strcmp(input, "DELETE") == 0){
        cout << "Enter the number (In the tree) that you want to delete." << endl;
        cin >> input3;
        //Remove the number from the tree, if it's there
        treeRemove(tree, tree, tree, input3);
    } 
    else if(strcmp(input, "PRINT") == 0){
        //Print the tree with spacing 3
        printTree(tree, spacing);
    }
    //Search the tree
    else if(strcmp(input, "SEARCH") == 0){
        cout << "What's the number that you want to search for?" << endl;
        cin >> input3;
        search(tree, input3);
        }
    //Quit BST
    else if(strcmp(input, "QUIT") == 0){
      cout << "Thanks for using BST!" << endl;
      running = false;
    }
    }
}
//Add a number to the tree
void treeAdd(Tree* newNode, Tree* current, Tree* & head){
    //If the tree is empty, make the new one head
    if(head == NULL){
      head = newNode;
    return;
    }
    //Otherwise if the new node's data is bigger
    else if(newNode->getData() > current->getData()){ 
        //And if the current node's right is NULL
        if(current->getRight() == NULL){
            //Add it to the right
            current->setRight(newNode);
            return;
            }
        //Otherwise go onto the right side of the tree
        else{
            treeAdd(newNode, current->getRight(), head);
            }
        }
    //If the node's data is less than the current node's
    else if(newNode->getData() < current->getData()){
        //IF the left space is empty
        if(current->getLeft() == NULL){
            //Add it to the left
            current->setLeft(newNode);
            return;
            }
        //Otherwise go down the left side
        else{
            treeAdd(newNode, current->getLeft(), head);
        }
    }
    //Otherwise (Used for duplicates)
    else {
        //If the left is empty
        if(current->getLeft() == NULL){
            //Add it there
            current->setLeft(newNode);
            return;
        }
        //Otherwise
        else if(current->getRight() == NULL){
            //Add it to the right
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
    space = space + 5;

    //Start from the right
    if(head->getRight() != NULL){
    printTree(head->getRight(), space);
    }
    //Print the current node after a new line
    cout << endl;
    for(int i = 0; i < space; i++){
        cout << " ";
    }
    cout << head->getData() << '\n';
    //Onto the left
    cout << endl;
    if(head->getLeft() != NULL){
    printTree(head->getLeft(), space);
    }
}
//Search for a number (Also helps to prevent duplicates)
bool search(Tree* head, int input){
    //If the tree is empty
    if(head == NULL){
        cout << "Number isn't the tree. It's thus valid to add." << endl;
        return false;
    }
    //If it isn't the head, and head exists
    else if(head->getData() != input && head != NULL){
        //If the input is smaller than the head, go down the left
        if(head->getData() > input){
            search(head->getLeft(), input);
            }
        //Otherwise if the input is larger than the head, go down the right
        else if(head->getData() < input){
            search(head->getRight(), input);
            }
        }
    //If the head has the searched for number
    else if(head->getData() == input){
        cout << "Your number is present in the tree!" << endl;
        return true;
    }
    else{
        //Otherwise if you get to the end (If it's not caught by the top), then the number isn't there
        cout << "Number isn't in the tree. It's thus valid to add." << endl;
        return false;
    }
    return false;
}
//Removing a number from the tree
void treeRemove(Tree* current, Tree* &head, Tree* parent, int data){
    //If there's nothing in the tree to delete
    if(head == NULL){
        return;
    }
    //Otherwise
    if(current != NULL){
        //If the current node's data is equal to the input
        if(current->getData() == data){
            //If the current has no children
            if(current->getLeft() == NULL && current->getRight() == NULL){
                //If current is head (the only node in the tree)
                if(current == head){
                    delete head;
                    head = NULL;
                }
                //If the current is the left child
                else if(parent->getLeft() == current){
                    parent->setLeft(NULL);
                    delete current;
                }
                //Otherwise if the current is the right child
                else{
                    parent->setRight(NULL);
                    delete current;
                }
            }
            //Only right child present
            else if(current->getLeft() == NULL){
                //If current is head (the only node in the tree)
                if(current == head){
                    Tree* temp = head;
                    head = head->getRight();
                    delete temp;
                }
                //If the current is the parent's right child
                else if(parent->getRight() == current){
                    Tree* temp = current;
                    parent->setRight(current->getRight());
                    delete temp;
                }
                //If the current is the parent's left child
                else{
                    Tree* temp = current;
                    parent->setLeft(current->getRight());
                    delete temp;
                }
            }
            //If only the left child is present
            else if(current->getRight() == NULL){
                if(current == head){
                    Tree* temp = head;
                    head = head->getLeft();
                    delete temp;
                }
                //If the current is the parent's right child
                else if(parent->getRight() == current){
                    Tree* temp = current;
                    parent->setRight(current->getLeft());
                    delete temp;
                }
                //If the current is the parent's left child
                else{
                    Tree* temp = current;
                    parent->setLeft(current->getLeft());
                    delete temp;
                }
            }
            //If both children are present
            else{
                //Replace it with the next smallest node, so go left once and right as far as you can
                //Go left
                Tree* temp2 = current->getLeft();
                Tree* temp3 = current;
                //Go right as far as possible
                while(temp2->getRight() != NULL){
                    temp3 = temp2;
                    temp2 = temp2->getRight();
                }
                //Swap data
                int newCurrent = temp2->getData();
                int deleteData = current->getData();
                temp2->setValue(deleteData);
                current->setValue(newCurrent);
                //If the node's left and right are NULL
                if(temp2->getLeft() == NULL && temp2->getRight() == NULL){
                    //If the node is it's parent's left
                    if(temp3->getLeft() == temp2){
                        temp3->setLeft(NULL);
                    }
                    //If the node is it's parent's right                    
                    else{
                        temp3->setRight(NULL);
                    }
                    //Delete the node
                    Tree* temp4 = temp2;
                    delete temp4;
                }
                //If the right is NULL (Only left exists)
                else if(temp2->getRight() == NULL){
                    Tree* temp4 = temp2;
                    temp3->setLeft(temp2->getLeft());
                    delete temp4;
                    
                }
                //Only the left exists (Right is NULL)
                else{
                    Tree* temp4 = temp2;
                    temp3->setRight(temp2->getRight());
                    delete temp4;
                }
            }
        }
        //If the current's data is larger than the inputted data, go left
        else if(current->getData() > data){
            parent = current;
            treeRemove(current->getLeft(),head, parent, data);
        }
        //Otherwise go right
        else{
            parent = current;
            treeRemove(current->getRight(),head, parent, data);
        }
    }
}
