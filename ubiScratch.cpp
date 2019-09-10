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

#define EPS 1e-6

using namespace std ;

void printP ( int  p ) { cout << 1 ;}
void printP ( int * p ) { cout <<2 ; }
void printP ( int ** p ) { cout <<3; }

int solveEggDrop ( int k /* floors*/ , int d /*eggs*/ )  {
  if ( d == 1 ) return k ;
  if ( k == 0 || k == 1 ) return 1 ;
  int res = 0, resMax = INT_MAX ;
  for ( int i = 1 ; i <= k ; ++ i )  {
    res = max ( solveEggDrop ( i, d - 1) , 1+ solveEggDrop ( k - i , d )) ;
    resMax = min ( resMax , res ) ;
  }
  return resMax ;
}

int main(int argc, char *argv[]) {

  /*
  int a = 5 ;
  int * b = (int * ) &a  ;
  printP ( a ) ;
  printP ( b ) ;
  printP ( &b) ;
  */

  cout << solveEggDrop ( 36, 2 ) << endl ;

  return 0; 
} 