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


class DebugDelete {
  public :
  DebugDelete() = default ;

  template < typename T > inline bool operator() ( T * p ) {
   cout << "Deleting pointer" <<  endl ;
   delete p ;
   return true ;

  }


};


template < typename T, typename U = std::default_delete<T> >
class my_shared_ptr {
  public :
    
    my_shared_ptr<T, U> () : refcount ( new int(1)), thisObj(0),  del ( new std::default_delete<T>()) {} 
    my_shared_ptr<T, U> ( T & t) : refcount ( new int(1)), thisObj(&t), del ( new std::default_delete<T>()) {} 
    my_shared_ptr<T, U> ( T & t,  U & u) : refcount ( new int(1)), thisObj(&t), del ( &u) {} 
    my_shared_ptr<T, U> ( T & t,  U * u) : refcount ( new int(1)), thisObj(&t), del ( u) {} 
    //my_shared_ptr<T, U> ( T & t,  U && u) : refcount ( new int(1)), thisObj(&t), del ( &u) {}
    my_shared_ptr<T, U> ( T * t,  U * u, int * i ) : thisObj ( t) , del ( u), refcount(i) {}

    my_shared_ptr<T, U> ( my_shared_ptr && msp ) : refcount ( msp.refcount) , thisObj(msp.thisObj), del ( msp.del) {
      cout << "Here" ;
      msp.refcount = NULL ;
      msp.thisObj = NULL ;
      msp.del = NULL;
    } 

    ~my_shared_ptr() {
        refcount[0] -- ;
      if ( refcount[0] == 0 && thisObj != NULL )
        (*del) (thisObj);
    }

    int returnRefCount() const { return refcount[0];}

    void incrCount ( ) { this->refcount[0]++;}

    static my_shared_ptr<T,U> my_make_shared ( my_shared_ptr & msp) {

      //cout << "Here" ;

      msp.incrCount();

      return my_shared_ptr<T, U> ( msp.thisObj, msp.del, msp.refcount);
    }

  private :

    int * refcount ;

    T * thisObj;

    U * del ;
};


template < typename T >
class Blob {

  public :

  typedef typename vector<T>::size_type size_type ;

  Blob<T>() = default ;
  Blob<T>(std::initializer_list<T> il );
  
  size_type size() const { return data->size();}
  bool empty() const { return data->emtpy();}

  void push_back( const T &t) { data->push_back(t);}
  void pop_back();

  T & front();
  T & back();

  private :

    //std::shared_ptr<vector<T>> data;

    my_shared_ptr<std::vector<T>> data;

    void check ( size_type i, const T & msg) const ;

};

template < typename T >
class BlobPtr {

  public :

  BlobPtr<T>() : curr(0) {}
  BlobPtr<T>( Blob<T> &a, size_t sz = 0 ) :
    wptr( a.data ) , curr ( sz ) {}

  T & deref() const ;
  BlobPtr<T> & incr ();

  private :

  std::shared_ptr<std::vector<T>>
    check( size_t, const T &) const;

  std::weak_ptr<vector<T>> wptr ;
  size_t curr;
};


int main ( void ) {

  try {

    Blob<string> myBlob ;
    myBlob.push_back ( "hi");
    myBlob.push_back ( "bye");
    return 0;

  	}

	catch ( std::exception ex) {
		cout << "Error : " << ex.what() << endl ;
	}

  return 0;
}
