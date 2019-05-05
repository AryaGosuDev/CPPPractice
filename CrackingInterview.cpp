#include <iostream>
#include <memory>
#include <vector>
#include <thread>

using std::cout;
using std::endl;

int retMax ( int && a, int && b ) {

  int ab[] = { a, b } ;

  int interRes = a - b ;

  int indx = interRes >> ( sizeof ( int) * 8 - 1) ;

  unsigned int UIndx = (unsigned int) interRes ;

  UIndx = UIndx >> ( sizeof ( int) * 8 - 1);

  cout << UIndx << endl ;

  return ab[UIndx];

}

int main () {

  cout << retMax ( 5, 4 ) << endl;


  return 0 ;

}
