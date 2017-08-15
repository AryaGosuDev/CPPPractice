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

using std::endl;
using std::cout;
using std::string;
using std::copy;
using std::for_each;
using std::vector;
using std::list;

bool addFamily ( std::map<string, vector<string>>  & familyMap, const string  & familyName) {
		return (&familyMap[familyName]) != NULL  ;
}


int main ( void ) {

  try {

	  std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 4, 3, 2, 1, 9, 9};

		std:vector<std::pair<string,int>> thisPairMap ;

	  vector<int> inputIntStream;

	  std::ostream_iterator<int> out_iter ( std::cout, " " );

	  //std::istream_iterator<string> int_in ( std::cin), eof_cin, copy_cin_in ;
		int number ;
		string word;

	  while ( std::cin >> word ) {
			cout << "Adding number" << endl;
			std::cin >> number ;
			cout << "Adding to vector pair" << endl;
			thisPairMap.push_back ( std::pair<string, int> ( word, number ));
	  }




		for ( auto &a : thisPairMap){
			cout << a.first << endl;
		}

		//for_each ( thisPairMap.begin(), thisPairMap.end(), [](std::pair<string, int> a) { cout << a.first << " " << a.second << endl;});


	}
	catch ( std::exception ex) {
		cout << "Error : " << ex.what() << endl ;
	}

  return 0;
}
