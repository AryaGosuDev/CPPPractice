//#include "Sales_data.h"

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

using std::endl;
using std::cout;
using std::string;
using std::copy;
using std::for_each;
using std::vector ;

int main ( void ) {
	
  try {
	
	  std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 4, 3, 2, 1, 9, 9};
	  
	  vector<string> inputFileStrings ;
	  
	  vector<int> inputIntStream;
	  
	  std::ostream_iterator<int> out_iter ( std::cout, " " );
	  
	  std::ifstream in ( "textExample.txt", std::ios::in);
	  std::istream_iterator<string> str_it ( in ) , eof, copy_str_in;
	  
	  std::istream_iterator<int> int_in ( std::cin), eof_cin, copy_cin_in ;
	  
	  while ( int_in != eof_cin) {
		  
		  copy_cin_in = int_in ;
		  
		  inputIntStream.push_back ( *int_in++);
		  
		  //cout << *copy_cin_in << endl ;
		  
		  //cout << *(std::prev(str_it)) << endl ;  
	  }
	  
	  std::sort (inputIntStream.begin(), inputIntStream.end() );
	  
	  std::unique_copy ( inputIntStream.begin(), inputIntStream.end(), out_iter ) ;
	  
	  cout << "end of t" ;
	}
	catch ( std::exception ex) {
		cout << "Error : " << ex.what() << endl ;	
	}
  
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
