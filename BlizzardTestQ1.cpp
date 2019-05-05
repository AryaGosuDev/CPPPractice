//Arya Mahini
//time spent 1hr
//compiled using g++ -std=c++11
//approach : this is a problem that is similar to a bit shifting problem.
//shifting bits to the right or left signifies the multiplication of 2 or
//the division of 2. similarly dividing by 10 shifts a base 10 number right
//then checking the number if it has been found prior in a bit vector. shifting
//a number right as a non-float will throw away least significant digits.
//runtime : O ( n )
//future / advancement : error checking the input

#include <iostream>

using std::cout ;
using std::endl;

inline bool AllDigitsUniqueRec ( unsigned int & val, unsigned int * bitV ){
  if ( val == 0 ) return 1;
  else {
    if ( bitV[val % 10] == 1 ) return 0;
    bitV[val % 10] = 1 ;
    val /= 10;
    return AllDigitsUniqueRec ( val , bitV );
  }
}

bool AllDigitsUnique(unsigned int value) {
  unsigned int bitV[10] = {}  ;
  return AllDigitsUniqueRec ( value , bitV) ;
}

int main() {
  unsigned int val1 = 550'924'7 ;
  cout << val1 << " : " << AllDigitsUnique ( val1) << endl ;
  unsigned int val2 = 1 ;
  cout << val2 << " : " << AllDigitsUnique ( val2) << endl ;
  unsigned int val3 = -4 ;
  cout << val3 << " : " << AllDigitsUnique ( val3) << endl ;
  unsigned int val4 = 509'247 ;
  cout << val4 << " : " << AllDigitsUnique ( val4) << endl ;
  return 0;
}
