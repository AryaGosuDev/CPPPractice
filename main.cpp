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
using std::string;
using std::copy;
using std::for_each;
using std::vector;
using std::list;

void assignInts ( std::vector<int> * _intVec ) {
	int _inputInt ;
	while ( std::cin >> _inputInt){
		_intVec->push_back(_inputInt) ;
	}
}

void printInts ( std::vector<int> * _intVec ) {

	for_each ( _intVec->begin(), _intVec->end(), [](int & _i){ cout << _i << endl;});
	}

	void process(std::shared_ptr<int> ptr)
{
    std::cout << "inside the process function:" << ptr.use_count() << "\n";
}

void end_int ( int * a) {

	delete a ;
	cout << "Delete a";
}

typedef std::unique_ptr<int> IntP ;


int main ( void ) {

  try {
  			int ix = 1024;
  			int * p1 = &ix ;
  			int * pi2 = new int(2048);
  			IntP p0(pi2);
  			IntP p5(p0.get());




	}
	catch ( std::exception ex) {
		cout << "Error : " << ex.what() << endl ;
	}

  return 0;
}
