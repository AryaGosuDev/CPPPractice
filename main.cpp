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

using std::endl;
using std::cout;
using std::string;
using std::copy;
using std::for_each;
using std::vector;
using std::list;

class StrBlob {

public:
	StrBlob() {};
	StrBlob(std::initializer_list<string> li);

	string back() const ;
	string front() const ;

	void print () const  {
		for_each ( data->begin(), data->end(), [](string & vecString) { cout << vecString << endl ;});

	}

private:

	std::shared_ptr<vector<string>> data ;
};

StrBlob::StrBlob(std::initializer_list<string> li) : data(std::make_shared<vector<string>>(li)){

}

string StrBlob::back() const {
	return data->back();

}

string StrBlob::front() const {
	return data->front();
}

int main ( void ) {

  try {

  	StrBlob b1 ;
  	{
  		StrBlob b2 = { "a", "b", "c"} ;
  		b1 = b2 ;



  	}

  	cout << b1.back();

  	b1.print();

  	//for_each ( )

	}
	catch ( std::exception ex) {
		cout << "Error : " << ex.what() << endl ;
	}

  return 0;
}
