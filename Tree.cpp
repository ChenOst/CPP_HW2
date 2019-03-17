#include <iostream>
#include <cstdlib>
#include "Tree.hpp"

using namespace std;

//Constracor
ariel::Tree::Tree(){
    rootValue = NULL;
}
//Create a new leaf to the tree
ariel::Tree::node* ariel::Tree::CreateLeaf(int data){
    node* n = new node;
    n->data = data;
    n->left = NULL;
    n->right = NULL;

    return n;
}
//Accepts as input number i and put it in 
//the appropiate place in the tree
void ariel::Tree::insert(int data){
    insertPrivate(data, rootValue);
}
//Auxiliary function to insert function
void ariel::Tree::insertPrivate(int data, node* ptr){
    if(rootValue == NULL){
        rootValue = CreateLeaf(data);
    }
    else if(data < ptr->data){
        if(ptr->left != NULL){
            insertPrivate(data, ptr->left);
        }
        else{
            ptr->left=CreateLeaf(data);
        }
    }
    else if(data > ptr->data){
        if(ptr->right != NULL){
            insertPrivate(data, ptr->right);
        }
        else{
            ptr->right=CreateLeaf(data);
        }
    }
    else{
        cout << "The data " << data << " is already in the tree\n";
    }
}
//Prints the tree inorder
void ariel::Tree::print(){
    printPrivate(rootValue);
}
//Auxiliary function to print function
void ariel::Tree::printPrivate(node* ptr){
    if(rootValue != NULL){
        //left
        if(ptr->left != NULL){
            printPrivate(ptr->left);
        }
        //parent
        cout << ptr->data <<" ";
        //right
        if(ptr->right != NULL){
            printPrivate(ptr->right);
        }
    }
    else{
        cout << "The tree is empty\n";
    }
}
ariel::Tree::node* ariel::Tree::ReturnNode(int data){
    return ReturnNodePrivate(data, rootValue);
}

ariel::Tree::node* ariel::Tree::ReturnNodePrivate(int data, node* ptr){
    if(ptr != NULL){
        if(ptr->data==data){
            return ptr;
        }
        else{
            if(data < ptr->data){
                return ReturnNodePrivate(data, ptr->left);
            }
            else{
                return ReturnNodePrivate(data, ptr->right);
            }
        }
    }
    else{
        return NULL;
    }
}

//Checks if the tree contains certain data
bool ariel::Tree::contains(int data){
    bool flag = containsPrivate(data, rootValue);
    return flag;
}
//Auxiliary function to contains function
bool ariel::Tree::containsPrivate(int data, node* ptr){
    if(ptr != NULL){
        if(ptr->data==data){
            return true;
        }
        else{
            if(data < ptr->data){
                return ReturnNodePrivate(data, ptr->left);
            }
            else{
                return ReturnNodePrivate(data, ptr->right);
            }
        }
    }
    else{
        return false;
    }
}

//Return the right child of the node with the data
int ariel::Tree::right(int data){
    node* ptr = ReturnNode(data);
    if(ptr != NULL){
        if(ptr->right==NULL){
            return -1;
        }
        else{
            return ptr->right->data;
        }
    }
    else{
        cout << "data " << data << "is not in the tree\n";
        return -1;
    }
}
//Return the left child of the node with the data
int ariel::Tree::left(int data){
    node* ptr = ReturnNode(data);
    if(ptr != NULL){
        if(ptr->left==NULL){
            return -1;
        }
        else{
            return ptr->left->data;
        }
    }
    else{
        cout << "data " << data << "is not in the tree\n";
        return -1;
    }

}

//Return the root value
int ariel::Tree::root(){
    if (rootValue == NULL){
        return -1;
    }
    else{
       return rootValue->data;
    }
}
//Remove a node with the data from the tree
void ariel::Tree::remove(int data){
    removePrivate(data, rootValue);
}
//Auxiliary function to remove function
void ariel::Tree::removePrivate(int data, node* ptr){
    if(rootValue != NULL){
        if (rootValue->data==data) {
            removeRoot();
        }
        else{
            if(data < ptr->data && ptr->left !=NULL){
                if(ptr->left->data == data){
                    removeMatch(ptr, ptr->left, true);
                }
                else{
                    removePrivate(data, ptr->left);
                }
            }
            else if(data > ptr->data && ptr->right !=NULL){
                if(ptr->right->data == data){
                    removeMatch(ptr, ptr->right, true);
                }
                else{
                    removePrivate(data, ptr->right);
                }
            }
            else{
                cout << "The data "<< data << " was not found in the tree\n";
            }
        }
    }
    else{
        cout << "The tree is empty\n";
    }
}
//Auxiliary function to remove function
void ariel::Tree::removeRoot(){
    node* delPtr = rootValue;
    int rootValueData = rootValue->data;
    int smallestInRightSubTrees;

    //0 children
    if(rootValue->left == NULL && rootValue->right == NULL){
        rootValue = NULL;
        delete delPtr;
    }
    //1 child
    else if(rootValue->left == NULL && rootValue->right != NULL){
        rootValue = rootValue->right;
        delPtr->right = NULL;
        delete delPtr;
    }
    else if(rootValue->left != NULL && rootValue->right == NULL){
        rootValue = rootValue->left;
        delPtr->left = NULL;
        delete delPtr;
    }
    //2 children
    else{
        smallestInRightSubTrees = findSmallestPrivate(rootValue->right);
        removePrivate(smallestInRightSubTrees, rootValue);
        rootValue->data = smallestInRightSubTrees;
    }
}
//Auxiliary function to remove function
int ariel::Tree::findSmallest(){
    return findSmallestPrivate(rootValue);
}

//Auxiliary function to remove function
int ariel::Tree::findSmallestPrivate(node* ptr){
    if(rootValue == NULL){
        return -1;
    }
    else{
        if(ptr->left != NULL){
            return findSmallestPrivate(ptr->left);
        }
        else{
            return ptr->data;
        }
    }
}
//Auxiliary function to remove function
void ariel::Tree::removeMatch(node* parent, node* match, bool left){
    if(rootValue != NULL){
        node* delPtr;
        int matchData = match->data;
        int smallestInRightSubTrees;

        //0 children
        if(match->left == NULL && match->right == NULL){
            delPtr = match;
            if (left == true) {
                parent->left = NULL;
            }
            else{
                parent->right = NULL;
            }
            delete delPtr; 
        }

        //1 child
        else if(match->left == NULL && match->right != NULL){
            if ( left == true) {
                parent->left = match->right;
            }
            else{
                parent->right = match->right;
            }
         match->right= NULL;
         delPtr = match;
         delete delPtr;
        }
        else if(match->left != NULL && match->right == NULL){
            if (left == true) {
                parent->left = match->left;
            }
            else{
                parent->right = match->left;
            }
         match->left= NULL;
         delPtr = match;
         delete delPtr;
        }

        //2 children
        else{
            smallestInRightSubTrees = findSmallestPrivate(match->right);
            removePrivate(smallestInRightSubTrees, match);
            match->data = smallestInRightSubTrees;
        }

    }
    else{
        cout << "Cant remove";
    }
}
//Return the size of the tree
int ariel::Tree::size(){
    return sizePrivate(0, rootValue);
}

int ariel::Tree::sizePrivate(int value, node* ptr){
    if(rootValue != NULL){
        if(ptr->left != NULL){
            return sizePrivate(value+1,ptr->left);
        }
        if(ptr->right != NULL){
           return sizePrivate(value+1,ptr->right);
        }
        return value;
    }
    else{
        return 0;
    } 
}
// Return the data of the parent
int ariel::Tree::parent(int data){
    return parentPrivate(data, rootValue);
}

//Auxiliary function to parent function
int ariel::Tree::parentPrivate(int data, node* ptr){
    if(rootValue != NULL && contains(data)){
        if(rootValue->data != data){
            if(data < ptr->data){
                if(ptr->left->data == data){
                    return ptr->data;
                }
                else{
                    return parentPrivate(data, ptr->left);
                }
            }
            else{
                if(ptr->right->data == data){
                    return ptr->data;
                }
                else{
                    return parentPrivate(data, ptr->right);
                }
            }
        }
        else{
            return -1;
             cout << "no parent to "<< data << " its the value of the root\n";
        }
    }
    else{
        return -1;
        cout << "The data "<< data << " was not found in the tree\n";  
    }
}