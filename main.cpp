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

class Sales_data {

  friend std::istream & read (std::istream &, Sales_data & ); 
  friend std::ostream & print ( std::ostream &, const Sales_data & );

  public :
    Sales_data() = default ;
    Sales_data ( const string &s ) : bookNo(s) {}
    Sales_data (std::istream & );
    string isbn() const { return bookNo;}
    Sales_data & combine ( const Sales_data & ) ;

  private :
    double avg_price() const { return units_sold ? rev / units_sold : 0 ;}
    string bookNo;
    unsigned units_sold = 0;
    double rev = 0.0 ;
    double price = 0;
    
};


std::istream & read ( std::istream & is , Sales_data & item ){

  is >> item.bookNo >> item.units_sold >> item.price ;
  //if ( is )
    item.rev = item.units_sold * item.price ;
  //else
    //item = Sales_data();

  return is;
}


std::ostream & print ( std::ostream &os, const Sales_data & item){
  os << item.isbn() << " " << item.units_sold << " " << item.price <<
   " " << item.rev << " " << item.avg_price() << std::endl ;
   return os;
}



int main ( void ) {

  try {
    Sales_data d1 ;
    read ( std::cin , d1 );

    print ( cout , d1 );

    
    return 0;

  	}

	catch ( std::exception ex) {
		cout << "Error : " << ex.what() << endl ;
	}

  return 0;
}
