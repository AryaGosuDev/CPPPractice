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

class StrBlobPtr ;

class StrBlob {

public:
	StrBlob() {};
	StrBlob(std::initializer_list<string> li);
	
	friend class StrBlobPtr ;
	
	StrBlobPtr begin() ;
	StrBlobPtr end();

	string back() const ;
	string front() const ;
	
	void print () const  {
		for_each ( data->begin(), data->end(), [](string & vecString) { cout << vecString << endl ;});
	}

private:
	std::shared_ptr<vector<string>> data ;
};

class StrBlobPtr {
	
	public :
		StrBlobPtr () : current(0)  {} ;
		StrBlobPtr ( StrBlob &a, size_t _curr = 0 ) : wptr ( a.data) , current ( _curr) {	
		}
		std::string & deref () const ;
		StrBlobPtr & incr() ;
		
		size_t current ;
		
	private :
	
		std::shared_ptr<std::vector<string>>
		check ( size_t i) const ;
	
		std::weak_ptr<vector<std::string>> wptr ;
		
		
};

bool operator!=(const StrBlobPtr & lhs, const StrBlobPtr & rhs){
			return lhs.current != rhs.current;
		}

StrBlob::StrBlob(std::initializer_list<string> li) : data(std::make_shared<vector<string>>(li)){
}

string StrBlob::back() const {
	return data->back();
}
string StrBlob::front() const {
	return data->front();
}

StrBlobPtr StrBlob::begin () {
	return StrBlobPtr ( *this);
}

StrBlobPtr StrBlob::end () {
	return StrBlobPtr ( *this, data->size() );
}

std::shared_ptr<std::vector<string>> StrBlobPtr::check( size_t i ) const {
	auto ret = wptr.lock() ;
	if ( !ret )
		throw std::runtime_error ( "unbound StrBlob");
	if ( i >= ret->size() )
		throw std::out_of_range ( "Out of range StrBlob");
	return ret ;
}

std::string &  StrBlobPtr::deref() const {
	auto ptr = check ( current);
	return (*ptr)[current];
}

StrBlobPtr & StrBlobPtr::incr() {
	
	check ( current  ) ;
	++current ;
	return *this ;
} 

int main ( void ) {

  try {

  	StrBlob b1 { "a", "b", "c"} ;
	
	for ( StrBlobPtr beg = b1.begin() ; beg != b1.end() ; beg.incr()) {
		//cout << beg.deref() << endl;
		
	}
	
	string strInput ;
	
	size_t charArraySize = 20 ;
	
	char * inputCharStringArray = new char[charArraySize] ;
	char * tempCharArray ;
	
	int currentArrayIndx = 0;
	
	while ( std::cin >> strInput) {
		
		if ( strInput.size() + currentArrayIndx > charArraySize ) {
			//we need a bigger array to store the new string
			tempCharArray = inputCharStringArray ;
			charArraySize *= 2 ;
			inputCharStringArray = new char[charArraySize] ;
			cout << "Deleting old string of size" << charArraySize / 2  << endl ;
			delete [] tempCharArray ;
		}
		
		for ( int i = 0 ; i < strInput.size() ; i++  ) 
			inputCharStringArray[currentArrayIndx++] = strInput[i] ;

	}
	
	
	
	//cout << "test" ;
	}
	catch ( std::exception ex) {
		cout << "Error : " << ex.what() << endl ;
	}

  return 0;
}
