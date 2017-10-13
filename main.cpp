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

//vector to store each line in the file
//istringstream to break each line into words

//result set, holds the lines that each found word is on
//map to associate the set of line numbers

typedef std::set<int> setQueryType ;
typedef std::map<string, setQueryType> mapQueryType ;

class QResult {
//return the result of a query operation from textq
//needs a print function

  public :

    int timesOccured ;
    std::vector <int> lineNumbers ;
    std::vector <string> lines ;


};

class TextQ {

public :
	TextQ ();
	TextQ ( std::ifstream & inputFile ) {



    if (!inputFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    std::string line ;
    std::string token ;
    int lineNumber = 0 ;

    while ( std::getline ( inputFile, line )){
      ++lineNumber ;
      fileLines.push_back ( line ) ;
      std::istringstream ss ( line ) ;
      while ( std::getline ( ss, token, ' ' )) {

        //cout << token << endl ;

        if ( token == "the") cout << lineNumber << " " << line << endl << endl;
        //setQueryType thisSet { lineNumber} ;

        auto retSubMap = mainWordMap.insert ( { token, setQueryType ( {lineNumber}) }) ;
        if ( !retSubMap.second) {
          //cout << "Not a success" << endl ;
          retSubMap.first->second.insert ( lineNumber);
          //if ( token == "the") cout << "Insterted : " << *(retSubMap.first->second.end() - 1) << endl ;
          if ( token == "the") cout << "Insterted : " << *(std::prev(retSubMap.first->second.end())) << endl ;
          
        }
      }
    }	
	}
//constructor : reads in the input ifstream file and makes each line into an element in the vector. Then it builds a map of every single word and a set for the line numbers on which is appears
//holds vector for each line
//hold map for each set

//query operation = look inside map to see if the word is there
//if found = how often it occured, line numbers, and corresponding text

	QResult query ( string & searchString  ) {

    QResult qr ;

    cout << "Search String : " << searchString << endl;

    auto retSubMap = mainWordMap.find ( searchString) ;

    if ( retSubMap != mainWordMap.end()) {
      qr.timesOccured = retSubMap->second.size () ;
      //cout << qr.timesOccured << retSubMap->second[0]  ;


      std::for_each ( retSubMap->second.begin(), retSubMap->second.end(), [&, this](int a ) { cout << "Query Line Number : " << a << endl ; qr.lineNumbers.push_back(a); qr.lines.push_back(fileLines[a - 1]);} );
    } 
    else {
      cout << "Word does not exist" << endl;


    }



    return qr ;


	}

	private :

		mapQueryType mainWordMap ; 
    std::vector<string> fileLines ; 

//use a shared pointer because both classes will refer to the same data. Also must make sure that the TextQ object is still alive if a query is being performed

};


std::ostream & print ( std::ostream &os, const QResult & qr){
  int lineNumber = 0;
  os << qr.timesOccured <<  endl << std::for_each ( qr.lines.begin(), qr.lines.end(), [] ( string a ) { cout << "line : " << a << endl << endl ;})  ;
   return os;
}

int main ( void ) {

  try {
  	std::ifstream ifs ("robot.txt", std::ifstream::in);

  	//infile is an ifstream

  	//TextQ tq ( ifs) ;

    auto p = std::make_shared < TextQ > ( TextQ(ifs) ) ;
  	while ( true ) {
  		cout << "enter word to look for, or q to quit : " ;

      cout << endl <<  "QUERY RESULT :: " << endl ;
  		string s ;
  		if ( !(cin >> s) || s == "q" ) break;
  		//run the query and print the results
  		print ( cout , p->query ( s ) ) << endl ;
  	}

    ifs.close();


  	}

	catch ( std::exception ex) {
		cout << "Error : " << ex.what() << endl ;
	}

  return 0;
}
