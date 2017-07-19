
//#include "Sales_data.h"

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <numeric>

using std::endl;
using std::cout;
using std::string;



bool biggies ( int & big )
{

  auto f = [&big] () { if ( big == 0 ) return true; else return biggies(--big);};
  cout << big << " , " << endl;
  return f();

}




int main ( void )
{

  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 4,3, 2, 1, 9,9};
int val = 5;
  bool outb = biggies ( val);


  cout << endl;



  /*
  Sales_data total ;

  std::ostream & obufOut = std::cout;
  std::istream & obufIn  = std::cin;


  if ( read(obufIn , total)){
    Sales_data trans;

    while ( read ( obufIn, trans)){
      if ( total.isbn() == trans.isbn()){
          total = add ( total, trans);
          print(obufOut, trans);
          print(obufOut, total);
        }
      else{

          print ( obufOut, total);

          total = trans ;
        }
    }

  }
  else{
    std::cerr << "No data?!" << std::endl;
    return -1;
  }

  */




  return 0;


}
