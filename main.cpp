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

class StrVec {

  public :

    StrVec() :
      elements(0), ff(0) , cap(0) { }

    StrVec ( std::initializer_list<string> il ) :
      elements(0), ff(0) , cap(0) {
        for ( const auto & str : il )
          push_back ( str );
      }

    StrVec(  StrVec && ) noexcept ;
    StrVec & operator= ( StrVec && ) ;

    ~StrVec();

  public :

    bool push_back ( const string &);
    void print () {
      for_each ( this->begin(), this->end(), [](string & a ) { cout << a << " : " ;});
      cout << endl;
    }

    size_t capacity() const { return cap - elements ;}
    size_t size() const { return ff - elements ;}
    string * begin() const { return elements ;}
    string * end() const { return ff ; }

    

  private :

    void chk_n_alloc ()
      { if ( size() == capacity()) reallocate() ;}

    void reallocate() ;

  private:
    //data members
    string * elements ;
    string * ff;
    string * cap ;

};

StrVec::StrVec( StrVec && rhs) noexcept {

    cout << "Entered move constructor" << endl;
    elements = rhs.elements ;
    ff = rhs.ff ;
    cap = rhs.cap;

    rhs.cap = rhs.ff = rhs.elements = 0;
}

StrVec & StrVec::operator = ( StrVec && rhs ) {

  cout << "Entered move assignment operator" << endl;
  if ( this != &rhs ){
    std::for_each ( this->begin(), this->end(), [](string & a) { (&a)->~string();}); 
    std::free ( elements );

    elements = rhs.elements ;
    ff = rhs.ff ;
    cap = rhs.cap;

    rhs.cap = rhs.ff = rhs.elements = 0;
  }

  return *this;
}

StrVec::~StrVec () {
  cout << "Entered ~StrVec() : " << endl ;
  if ( elements ) {
    std::for_each ( this->begin(), this->end(), [](string & a) { (&a)->~string();}); 
    std::free ( elements );
    cout << "Destroy successful" << endl;
  }
}

bool StrVec::push_back ( const string & str ) {
  chk_n_alloc();

  cout << "Here : " << ff << " : " << size() << " : " << capacity() << endl;

  ff = new(ff) string (str);
  ++ff;

  cout << "Here4 : " << *ff << endl;

  cout << "Here3" << endl;

  return 1;
}

void StrVec::reallocate() {

  cout << "Entered reallocate()" << endl;

  auto newCapacity = size() ? size() * 2 : 1 ;
  
  string * newData = (string*)std::malloc( newCapacity * sizeof(string ));

  if ( !newData) {
    std::cerr << "Could not allocate memory in reallocate()" << endl;
    return ;
  }

  auto dest = newData ;
  auto startElementsOld = elements ;

  for ( ; ff - startElementsOld > 0 ; ++startElementsOld ) { 
    dest = new(dest) string (*startElementsOld);
    dest++;
    //*dest++ = *startElementsOld;
    cout << "Copied : "<< *dest  << endl;
  }
  
  std::for_each ( this->begin(), this->end(), [](string & a) { (&a)->~string();}); 
  std::free(elements) ;

  elements = newData ;
  ff = dest;

  cap = elements + newCapacity;
}

int main ( void ) {

  try {
    using std::move ;
    StrVec strv1 ( {"Her?", "Him?", "Don't call it that"}) ;
    //if ( strv1.push_back( "Her?") ) std::cerr << "Push successful" << endl << endl;
    //if ( strv1.push_back( "Him?") ) std::cerr << "Push successful" << endl << endl;
    //if ( strv1.push_back( "Don't call it that") ) std::cerr << "Push successful" << endl << endl;

    strv1.print();

    StrVec strv2 ( move(strv1));

    strv2.print ();

    StrVec strv3;
    strv3 = move(strv2) ;

    strv2.print ();

    strv3.print();


    cout << "Size of StrVec : " << strv1.size() << " : Capacity of StrVec : " << strv1.capacity() << endl;

    return 0;

  	}

	catch ( std::exception ex) {
		cout << "Error : " << ex.what() << endl ;
	}

  return 0;
}
