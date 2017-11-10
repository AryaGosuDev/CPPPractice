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

class StrBlob {

  friend class StrBlobPtr;

  public :
    typedef std::vector<std::string>::size_type size_type ;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il ) : data(std::make_shared<vector<string>>(il)) {};
    size_type size() const { return data->size() ;}
    bool empty() const { return data->empty() ;}

    void push_back( const std::string &t ) {data->push_back(t); }
    void pop_back();

    std::string & front();
    std::string & back();

  private:

    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i , const std::string & msg ) const ;
};

class StrBlobPtr  {
  public :

    StrBlobPtr() : curr ( 0 ) {} 
    StrBlobPtr(StrBlob & a, size_t  sz = 0 ) :
      wptr ( a.data) , curr (sz ) {}

    std::string & deref() const ;
    StrBlobPtr & incr() ;

    StrBlobPtr & operator++();
    StrBlobPtr & operator--();
    StrBlobPtr & operator++(int);
    StrBlobPtr & operator--(int);

    StrBlobPtr & operator+ ( );

    std::string & operator*() const {
      auto p = check ( curr, "deref past end");
      return (*p)[curr];
    }

    std::string * operator->() const {
        return & this->operator*() ;

    }

  private :

    std::shared_ptr<std::vector<std::string>>
      check(std::size_t, const std::string & ) const ;

    std::weak_ptr<std::vector<std::string>> wptr ;
    std::size_t curr ;
};

class StrBlobPtrPtr {

  public :

    StrBlobPtrPtr() {};
    StrBlobPtrPtr(StrBlobPtr & a ) : ptr ( &a) {} ;

    StrBlobPtr & operator*() const {
      return *ptr;

    }

    StrBlobPtr * operator->() const {
      return ptr ;
    }

  private :

    StrBlobPtr * ptr ;
  
};


void StrBlob::check ( size_type i, const string & msg ) const {
  if ( i >= data->size() )
    throw std::out_of_range(msg );
}

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check ( std::size_t i, const std::string & msg ) const {

  auto ret = wptr.lock () ;
  if ( !ret )
    throw std::runtime_error ( "unbound StrBlobPtr") ;
  if ( i >= ret->size())
    throw std::out_of_range(msg) ;
  return ret ;
}

StrBlobPtr & StrBlobPtr::operator++() {
  check( curr, "passed end ");
  ++curr ;
  return *this ;
}

int main ( void ) {

  try {

    StrBlob a1 = {"hi", "bye", "now"};
    StrBlobPtr p ( a1 ) ;
    *p = "okay";
    cout << p->size() << endl;
    cout << (*p).size() << endl;
    cout << *p << endl;

    StrBlobPtrPtr pp1 ( p );

    cout << (*pp1)->size() << endl;
    
    return 0;

  	}

	catch ( std::exception ex) {
		cout << "Error : " << ex.what() << endl ;
	}

  return 0;
}
