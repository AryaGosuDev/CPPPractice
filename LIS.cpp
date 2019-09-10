#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <numeric>
#include <list>
#include <algorithm>
#include <iterator>
#include <exception>
#include <fstream>
#include <utility>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <memory>
#include <queue>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <thread>
#include <atomic>

#define EPS 1e-6

using namespace std ;

struct NodeLIS {
  NodeLIS () = default ;
  int valLow ;
  int valHigh ;
  size_t lowI ;
  size_t highI ;
  size_t size ;
};

int getLIS ( vector<int> & v ) {
  int maxL = 0 ;
  for ( size_t i = 0 ; i < v.size() ; ++ i ) {
    int lastVal = v[i] , lastIndex = i, LCnt = 1 ;
    for ( size_t j = i + 1 ; j < v.size() ; ++ j ) {
      if ( v[j] > lastVal and j > lastIndex ) {
        lastIndex = j ;
        lastVal = v[j];
        LCnt ++ ;
      }
    }
    lastVal = v[i] ; lastIndex = i ;
    for ( int j = i - 1 ; j >= 0 ; --j ) {
      if ( lastVal > v[j] and lastIndex > j ) {
        lastIndex = j;
        lastVal = v[j] ;
        LCnt ++;
      }
    }
    maxL = max ( maxL , LCnt) ;
  }
  return maxL ;
}
   
class Node  
{  
    public: 
    int key;  
    Node *left;  
    Node *right;  
    int height;  
};   
int height(Node *N)  {  
    if (N == NULL)  
        return 0;  
    return N->height;  
}
Node* newNode(int key)  {  
    Node* node = new Node(); 
    node->key = key;  
    node->left = NULL;  
    node->right = NULL;  
    node->height = 1; // new node is initially 
                      // added at leaf  
    return node;  
}  
  
// A utility function to right 
// rotate subtree rooted with y  
// See the diagram given above.  
Node *rightRotate(Node *y)  
{  
    Node *x = y->left;  
    Node *T2 = x->right;  
  
    // Perform rotation  
    x->right = y;  
    y->left = T2;  
  
    // Update heights  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
    x->height = max(height(x->left),  
                    height(x->right)) + 1;  
  
    // Return new root  
    return x;  
}  
  
// A utility function to left  
// rotate subtree rooted with x  
// See the diagram given above.  
Node *leftRotate(Node *x)  
{  
    Node *y = x->right;  
    Node *T2 = y->left;  
  
    // Perform rotation  
    y->left = x;  
    x->right = T2;  
  
    // Update heights  
    x->height = max(height(x->left),  
                    height(x->right)) + 1;  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
  
    // Return new root  
    return y;  
}  
    
int getBalance(Node *N)  {  
    if (N == NULL)  
        return 0;  
    return height(N->left) -  
           height(N->right);  
}  
  
Node* insert(Node* node, int key)  
{  
    if (node == NULL)  
        return(newNode(key));  
    if (key < node->key)  
        node->left = insert(node->left, key);  
    else if (key > node->key)  
        node->right = insert(node->right, key);  
    else 
        return node;  
    node->height = 1 + max(height(node->left),  
                           height(node->right));  
  
    int balance = getBalance(node);  
    // Left Left Case  
    if (balance > 1 && key < node->left->key)  
        return rightRotate(node);  
  
    // Right Right Case  
    if (balance < -1 && key > node->right->key)  
        return leftRotate(node);  
  
    // Left Right Case  
    if (balance > 1 && key > node->left->key)  {  
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  
  
    // Right Left Case  
    if (balance < -1 && key < node->right->key)  {  
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }  
    return node;  
}  
  
Node * minValueNode(Node* node)  {  
    Node* current = node;  
  
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)  
        current = current->left;  
  
    return current;  
}  

Node* deleteNode(Node* root, int key)  
{   
    if (root == NULL)  
        return root;  
    if ( key < root->key )  
        root->left = deleteNode(root->left, key);  
    else if( key > root->key )  
        root->right = deleteNode(root->right, key);  
    else{   
        if( (root->left == NULL) || 
            (root->right == NULL) )  
        {  
            Node *temp = root->left ?  
                         root->left :  
                         root->right;  
   
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else // One child case  
                *root = *temp; // Copy the contents of  
                           // the non-empty child  
            free(temp);  
        }  
        else{  
            // node with two children, get the inorder successor (smallest in the right subtree)  
            Node* temp = minValueNode(root->right);  
  
            // Copy the inorder successor's data to this node  
            root->key = temp->key;  
  
            // Delete the inorder successor  
            root->right = deleteNode(root->right, temp->key);  
        }  
    }  
    if (root == NULL)  
    return root;  
  
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE  
    root->height = 1 + max(height(root->left),  height(root->right));  
  
    // STEP 3: GET THE BALANCE FACTOR OF  
    // THIS NODE (to check whether this  
    // node became unbalanced)  
    int balance = getBalance(root);  
  
    // If this node becomes unbalanced,  
    // then there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 &&  
        getBalance(root->left) >= 0)  
        return rightRotate(root);  
  
    // Left Right Case  
    if (balance > 1 &&  
        getBalance(root->left) < 0)  
    {  
        root->left = leftRotate(root->left);  
        return rightRotate(root);  
    }  
  
    // Right Right Case  
    if (balance < -1 &&  
        getBalance(root->right) <= 0)  
        return leftRotate(root);  
  
    // Right Left Case  
    if (balance < -1 &&  
        getBalance(root->right) > 0)  
    {  
        root->right = rightRotate(root->right);  
        return leftRotate(root);  
    }  
  
    return root;  
}  

void preOrder(Node *root)  {  
    if(root != NULL)  {  
        cout << root->key << " ";  
        preOrder(root->left);  
        preOrder(root->right);  
    }  
}  
  
// Driver Code 
int main()  
{  
Node *root = NULL;  
  
    /* Constructing tree given in 
    the above figure */
    root = insert(root, -1);  
    root = insert(root, 0); 
    root = insert(root, 1);  
    root = insert(root, 2);  
    root = insert(root, 5); 
    root = insert(root, 6); 
    root = insert(root, 9); 
    root = insert(root, 10);  
    root = insert(root, 11);  
  
    /* The constructed AVL Tree would be  
         9  
        / \  
       1  10  
      / \   \  
     0   5   11  
    /   / \  
  -1   2   6  
    */
  
    cout << "\nPreorder traversal after"
         << " deletion of 10 \n";  
    preOrder(root);  
    cout << endl;
  
    return 0;  
}