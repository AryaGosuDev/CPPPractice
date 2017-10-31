#include "Sales_data.h"

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

class StrBlob {
  typedef std::vector<std::string>::size_type size_type;
  StrBlob();
  StrBlob(std::initializer_list<string> il );
  size_type size() const {return data->size();}
  bool empty() const { return data->empty();}

  void push_back(const string &t ) & { data->push_back(t);}
  void push_back( string && rhs ) && { data->push_back(rhs);}
  void pop_back();

  string & front();
  string & back();

  private :
    std::shared_ptr<std::vector<string>> data;

    void check ( size_type i, const string & msg ) const;
};

int main ( void ) {

  try {
    
    return 0;

  	}

	catch ( std::exception ex) {
		cout << "Error : " << ex.what() << endl ;
	}

  return 0;
}
