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

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class A {
public :
  class B ;

  void query ( B b) {

    int i = b.i;
  }

private :

};

class A::B {

public :

  B () { i = 4 ;}
  int i ;

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
