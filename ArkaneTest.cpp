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
#include <queue>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <thread>
#include <atomic>
#include <random>

using namespace std ;
using dictV = vector<pair<string,string>> ;

struct prefixTreeNode {
	prefixTreeNode() { for ( size_t i = 0 ; i < 26 ; ++ i ) key[i] = NULL ; }
	~prefixTreeNode() {}
	prefixTreeNode * key[26];
	vector<int> endingKeyStringIndex ;
};

bool buildPrefixTree ( prefixTreeNode * root , dictV & dV ) {
	if ( root == NULL || dV.size() == 0 ) return false;
	for( size_t i = 0 ; i < dV.size() ; ++ i ) {
		string & sortedWord = dV[i].first ; prefixTreeNode * tempLevel = root ;
		for ( size_t k = 0 ; k < sortedWord.length() ; ++ k ) {
			if ( tempLevel != NULL and tempLevel->key[sortedWord[k] - 'a'] != NULL ) tempLevel = tempLevel->key[sortedWord[k] - 'a'] ;
			else { tempLevel->key[sortedWord[k] - 'a'] = new prefixTreeNode () ; tempLevel = tempLevel->key[sortedWord[k] - 'a'] ; }
		}
		tempLevel->endingKeyStringIndex.push_back ( i );
	}
	return true ;
}

inline bool checkLegitString ( string & s ) {
	for ( auto & v : s ) { if ( v < 'a' || v > 'z' ) return false;}
	return true ;
}

void printAllAnagrams ( prefixTreeNode * root, dictV & dV , string & s, string & o ) {
	if ( checkLegitString ( s ) == false) { cout << "String : " << s << " is not a legit string." << endl; return ; }
	prefixTreeNode * tempLevel = root ;
	for ( size_t i = 0 ; i < s.size() ; ++ i ) {
		if ( tempLevel != NULL ) tempLevel = tempLevel->key[s[i] - 'a'] ;
	}
	if ( tempLevel == NULL ) { cout << "No anagrams." << endl ; return ; }
	if ( tempLevel->endingKeyStringIndex.size() == 0 ) { cout << "No anagrams." << endl ; return ; }
	for ( auto & v : tempLevel->endingKeyStringIndex) { if ( dV[v].second != o ) cout << dV[v].second << endl ;}
}

inline void printV ( dictV & v) { 
	for ( auto & s : v) cout << s.first << " : " << s.second << endl ;
}

bool deleteTree ( prefixTreeNode * root ) {
	queue<prefixTreeNode *> q ; q.push ( root );
	while ( !q.empty() ) {
		prefixTreeNode * tempLevel = q.front() ;
		for ( size_t i = 0 ; i < 26 ; ++ i ) {
			if ( tempLevel->key[i] != NULL ) q.push ( tempLevel->key[i]);
		}
		q.pop() ;
		free ( tempLevel) ;
	}
	return true ;
}

int main(int argc, char *argv[]) {

	// AnagramTest.cpp
//
// Programming Rules:
//  1. Any C++ compiler may be used.  Preferably VS2008, VS2010, or VS2012.
//     A. Please document which compiler (including version) was used.
//  2. All code should be standard-compliant C++ (i.e.: platform independent)
//  3. Any language or library feature in the C++11 standard may be used.
//  4. 3rd Party libraries (such as Boost) are not allowed.
//  5. Submit all files needed to build the final executable.
//
// Game Rules:
//  Anagrams are the result of rearranging the letters of a word to produce
//  a new word.
//
// Example: anagrams of "pale" are
//  leap
//  peal
//  plea
//
// Command line arguments:
//  AnagramTest.exe <dictionary_filename>
//
// Dictionary:
//  The dictionary file is a list of single ASCII words utilizing only letters 'a' to 'z'.
//  Each word is new line separated.  
//
// Function of the app:
//  The program should allow the user to enter multiple words, one at a time, using standard input. 
//  After a word is entered, the program should print to standard output all single-word anagrams 
//  for the word that are found in the supplied dictionary.  The program should handle the user 
//  entering characters that include upper and lower-case 'a' to 'z'.  
//
// Output:
//  The output for each word entered by the user should be a list of alphabetically
//  sorted anagrams for the given word.
//
// Test cases:
//  Using the supplied dictionary, the program should be able to accept the 
//  following input words from stdin and print the indicated output anagrams.
//
//  Entering: share
//  Should list: hares, hears, shear
//
//  Entering: decanter
//  Should list: cantered, recanted
//
//  Entering: diet
//  Should list: edit, tide, tied
//
//  Entering: percussion
//  Should list: supersonic
//
// Notes:
//  Your final solution should be PRODUCTION QUALITY, as if it is getting checked
//  in to live production code.
//

	/* Compiler :
	Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/usr/include/c++/4.2.1
	Apple LLVM version 10.0.1 (clang-1001.0.46.4)
	Target: x86_64-apple-darwin18.7.0
	Thread model: posix
	InstalledDir: /Library/Developer/CommandLineTools/usr/bin
	*/

	// compiled using $ g++ --std=c++14 -O0 -Wall -Wextra -fsanitize=address -g ArkaneTest.cpp -o run
	// Please note : original dict txt file didn't work correctly. Please copy paste to a new txt file on your system.
	
	if (argc != 2){
		std::cerr << "Usage: Anagram <dictionary_filename>" << endl;
		return -1;
	}
	ifstream inDict ( argv[1],std::ifstream::in ) ;
	dictV dict ; string inString ;
	if ( inDict ) {
		while ( getline (inDict,inString)) { 
			if ( inString.size() == 0 ) return -1; 
			//cout << inString << endl ;
			dict.push_back ( { inString, inString});
			sort ( dict.back().first.begin(), dict.back().first.end()  ) ;
		}
	}
	inDict.close() ;
	//printV ( dict ) ;
	prefixTreeNode * root = new prefixTreeNode () ;
	buildPrefixTree ( root ,dict) ;

	cout << "Enter a string to check for anagrams : " << endl ;
	// ctrl + d = EOF
	while ( getline ( cin , inString )) {
		if ( inString.size() > 0 ) {
			string originalS = inString ;
			sort ( inString.begin(), inString.end()) ;
			cout << "Anagrams for " << originalS << " : " << endl ;
			printAllAnagrams ( root, dict, inString , originalS) ;
		}
		cout << "Enter a string to check for anagrams : " << endl ;
	}

	if ( deleteTree( root ) == false )  cout << "Error in deleting Prefix Tree." << endl;

	return 0 ;
}