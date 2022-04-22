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
Tree* tree = NULL; 
char input[100];
char input2[100];
int input3 = 0;
int spacing = 3;
char input4[100];
bool running = true;
while(running == true){
cout << "Welcome to the Binary Search Tree! You can add numbers to the tree (ADD), print the tree (PRINT), delete numbers from the tree (DELETE), and search numbers in the tree (SEARCH). To quit type 'Quit'." << endl; 
cout << "As an aside, make sure you're not entering duplicate numbers (Ones you've already entered or have added via file). Valid entries include anything in the range from 1-999." << endl;    
cin >> input;
    if(strcmp(input, "ADD") == 0){
        cout << "Do you want to add via direct input (INPUT) or via file (FILE)" << endl;
        cin >> input2;
        if(strcmp(input2, "INPUT") == 0){
            cout << "Enter the number that you want to add to the tree." << endl;
            cin >> input3;
	    /*
	    if(search(tree, input3) == true){
	      cout << "No duplicate numbers in the tree! Please enter another number." << endl;
	    }
	    else{
	    */
	    Tree* newNode = new Tree(input3);
	    cout << "Does constructor work?" << endl;
	    treeAdd(newNode, tree, tree);
	    //}
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
    else if(strcmp(input, "DELETE") == 0){
        cout << "Enter the number (In the tree) that you want to delete." << endl;
        cin >> input3;
        treeRemove(tree, tree, tree, input3);
    } 
    else if(strcmp(input, "PRINT") == 0){
        printTree(tree, spacing);
    }
    else if(strcmp(input, "SEARCH") == 0){
        cout << "What's the number that you want to search for?" << endl;
        cin >> input3;
        search(tree, input3);
        }
    else if(strcmp(input, "QUIT") == 0){
      cout << "Thanks for using BST!" << endl;
      running = false;
    }
    }
}

void treeAdd(Tree* newNode, Tree* current, Tree* & head){
    if(head == NULL){
      cout << "Did we get here?" << endl;
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
    return false;
}

void treeRemove(Tree* current, Tree* &head, Tree* parent, int data){
    if(head == NULL){
        return;
    }
    if(current != NULL){
        if(current->getData() == data){
            //If the current has no children
            if(current->getLeft() == NULL && current->getRight() == NULL){
                //If current is head (the only node in the tree)
                if(current == head){
                    delete head;
                    head = NULL;
                }
                else if(parent->getLeft() == current){
                    parent->setLeft(NULL);
                    delete current;
                }
                else{
                    parent->setRight(NULL);
                    delete current;
                }
            }
            //Only right child present
            else if(current->getLeft() == NULL){
                if(current == head){
                    Tree* temp = head;
                    head = head->getRight();
                    delete temp;
                }
                //If the current is the parent's right
                else if(parent->getRight() == current){
                    Tree* temp = current;
                    parent->setRight(current->getRight());
                    delete temp;
                }
                //If the current is the parent's left
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
                //If the current is the parent's right
                else if(parent->getRight() == current){
                    Tree* temp = current;
                    parent->setRight(current->getLeft());
                    delete temp;
                }
                //If the current is the parent's left
                else{
                    Tree* temp = current;
                    parent->setLeft(current->getLeft());
                    delete temp;
                }
            }
            //If both children are present
            else{
                //Replace it with the next smallest node, so go left once and right as far as you can
                Tree* temp2 = current->getLeft();
                Tree* temp3 = current;
                //Go right as far as possible
                while(temp2->getRight() != NULL){
                    temp3 = temp2;
                    temp2 = temp2->getRight();
                }
                int newCurrent = temp2->getData();
                int deleteData = current->getData();
                temp2->setValue(deleteData);
                current->setValue(newCurrent);
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
        else{
            parent = current;
            treeRemove(current->getRight(),head, parent, data);
        }
    }
}
