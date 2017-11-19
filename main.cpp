//#include "Sales_data.h"
//#include "StrBlob.h"
//#include "StrBlobPtr.h"

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

using std::endl;
using std::cout;
using std::cin;
using std::string;
using std::copy;
using std::for_each;
using std::vector;
using std::list;

template < typename T > bool compare ( const T a, const T b ) {
  
  return a > b ;

}

template < typename T , typename U> int findThis ( T first, T last, U valToFind ) {
  
  //for_each ( p.begin(), p.end(), [valToFind](T a ) { cout << a << endl; if ( a == valToFind) return 1 ;}  );

  for (  ; first != last; ++ first ) {

    if ( (*first) == valToFind ) return 1 ;
  }
  return 0;
}

template <typename T, unsigned M> int print ( T (&p)[M]) {

  for ( int i = 0; i < M ; i++) cout << p[i] << endl ;
  
  return 1;
}


int main ( void ) {

  try {

    //cout << compare ( 1 , 2 ) << endl ;

    string findS = "g" ;

    vector<string> thisVec = {"fff", "g", "h", "j" };
    //cout << findThis ( thisVec.begin(), thisVec.end(), findS) << endl;
    int p{4444, 3, 4 , 4} ;
    print(p );

    return 0;

  	}

	catch ( std::exception ex) {
		cout << "Error : " << ex.what() << endl ;
	}

  return 0;
}
