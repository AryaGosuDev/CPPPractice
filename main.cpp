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
#include <random>
#include "mat3x3.h"
#include "vec3.h"

//typical cmd line compilate : g++ --std=c++14 -O0 -Wall -Wextra -fsanitize=address -g main.cpp -o return

using namespace std ;

struct bst : public std::vector<int> {
  
  struct Node {
    int data ;
    Node * right ; Node * left ;
  };

  Node * root ;

  Node * recBT ( Node * root , const int & val) {
    if ( root == NULL ) return NULL ;
    if ( root->data == val) return root ;
    Node * leftRes = recBT ( root->left , val ) ;
    if ( leftRes != NULL) return leftRes ;
    else {
      Node * rightRes = recBT ( root->right , val ) ;
      if ( rightRes != NULL) return rightRes ;
    }
    return NULL ;
  }
};

int main(int argc, char *argv[]) {
  bst bstRoot ;
  bstRoot.root = new bst::Node() ; bst::Node * root = bstRoot.root;

  root->data = 1;
  root->right = new bst::Node() ; root->left = new bst::Node() ; root->right->data = 2 ; root->left->data = 3 ;
  root->right->left = new bst::Node() ; root->right->right = new bst::Node() ; root->left->right = new bst::Node() ; root->left->left = new bst::Node() ;
  root->right->left->data = 4; root->right->right->data = 5 ; root->left->right->data = 6 ; root->left->left->data = 7 ;
  bst::Node * res = bstRoot.recBT ( root, 4 ) ; cout << ( res ? res : 0 ) << endl; 
}