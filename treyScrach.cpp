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

#define EPS 1e-6

using namespace std ;

string intToBin ( unsigned int b ) {
  string res = "" ;
  while ( b != 0 ) {
    if ( b & 1) res.push_back('1') ;
    else res.push_back('0') ;
    b = b >> 1 ;
  }
  reverse ( res.begin() , res.end()) ; return res ;
}

int main(int argc, char *argv[]) {

  float b = 3.0 ;
  float bb = b ;
  unsigned int * c = reinterpret_cast<unsigned int *>(&b);
  unsigned int newC = *c ;

  //cout << ++(*(unsigned int *)&b) << endl ;
  //cout << (*(unsigned int *)&b) << endl ;

  //newC = newC << 9 ;
  //newC = newC >> 9 ;
  //cout << newC << endl ;
  //cout << intToBin ( newC) << endl;
  printf("%.20f\n", b);
  cout << b << endl; 
  cout << sizeof ( b ) << endl;

  int a_align = 8 ;
  int memoryFull [1000] ;
  int offset = a_align - 1 ;
  unsigned long q = ((size_t)(memoryFull) + offset) & (~a_align - 1) ;
  cout << memoryFull<< " " <<(void*)q << endl;
  
  return 0; 
} 