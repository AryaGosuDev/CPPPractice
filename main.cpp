#include "Sales_data.h"
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
//#include "vec.h"
#include <unordered_set>

using std::endl;
using std::cout;
using std::cin;
using std::string;
using std::copy;
using std::for_each;
using std::vector;
using std::list;

namespace std {

  template <>
  struct hash<Sales_data> {

    typedef size_t result_type ;
    typedef Sales_data argument_type;

    size_t operator() ( const Sales_data & s ) const;

  };

  size_t hash<Sales_data>::operator() ( const Sales_data & s ) const {
      cout << "hash<Sales_data operator()" << endl ;
      return hash<string>()(s.bookNo) ^
             hash<unsigned>()(s.units_sold) ^
             hash<double>()(s.revenue) ;
  }
}

class exceptionType {


};



int main ( void ) {

  try {

    //std::unordered_multiset<Sales_data> SDset ;

    //SDset.insert(Sales_data());

    exceptionType * ex = new exceptionType() ;
    throw ex;
    
    return 0;
  	}
catch ( exceptionType * p ) {} 
	catch ( std::exception ex) {
		cout << "Error : " << ex.what() << endl ;
	}

  return 0;
}
