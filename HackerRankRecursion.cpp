#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <string>

using namespace std ;

constexpr int N = 10 ;
enum Direction { Horizontal, Vertical };

struct word {
	word ( string _word = "", bool _used = false ) : CWword ( _word) , used ( _used) {}
	string CWword ;
	bool used ;
};

struct line {
	line() = default ;
	line ( Direction _d , pair<int, int> _startingPoint , int _length = 0) : d ( _d ), startingPoint ( _startingPoint) , length ( _length) {} 
	Direction d ;
	pair<int, int> startingPoint;
	int length;
};

inline void  printCW ( vector<string> & B ) {
	for ( int i = 0 ; i < N ; ++ i ) {
		for ( int j = 0 ; j < N ; ++ j ) {
			cout << B[i][j] ;
		}
		cout << endl;
	}
	cout << endl;
}

bool isOnALine ( Direction d , std::vector<line> & l, int i , int j ) {
	for ( auto & lineVal : l ) {
		if ( lineVal.d == d ) {
			if ( lineVal.d == Horizontal and lineVal.startingPoint.first == i and 
				 lineVal.startingPoint.second <= j and lineVal.startingPoint.second + lineVal.length >= j) return true;
			if ( lineVal.d == Vertical   and lineVal.startingPoint.second == j and
				 lineVal.startingPoint.first <= i and lineVal.startingPoint.first + lineVal.length >= i ) return true ;
		}
	}
	return false ;
}

void addLine ( Direction d, std::vector<line> & l, vector<string> & B , int i , int j ) {
	int length = 0 ;
	if ( d == Horizontal and B[i][j+1] == '-' ) {
		l.push_back(line ( Horizontal, pair<int, int> (i,j)));
		for ( int it = j ; it < N and B[i][it] == '-' ; ++it) ++length;
		l.back().length = length ;
	}
	else if ( d == Vertical and B[i+1][j] == '-' ) {
		l.push_back ( line ( Vertical, pair<int, int> ( i, j )));
		for ( int it = i ; it < N and B[it][j] == '-' ; ++it ) ++length ;
		l.back().length = length ;
	}
}

void findVerticalLines ( vector<string> & B , vector<line> & l) {
	for ( int i = 0 ; i < N - 1 ; ++ i ){ //rows
		for ( int j = 0 ; j < N ; ++ j ) {
			if ( B[i][j] == '-' and !isOnALine( Vertical, l, i, j )) addLine ( Vertical, l,B, i, j ) ;
		}
	}
}

void findHorizontalLines ( vector<string> & B  , vector<line> & l ) {
	for ( int j = 0 ; j < N - 1 ; ++ j ) { //cols
		for ( int i = 0; i < N ; ++ i ) {
			if ( B[i][j] == '-' and !isOnALine ( Horizontal, l, i , j )) addLine ( Horizontal, l,B, i , j ) ;
		}
	}
}

bool canFill ( line & linei , string word, vector<string> & B ) {
	if ( linei.d == Vertical ) {
		int y = linei.startingPoint.second ;
		for ( int i = linei.startingPoint.first; i < linei.length + linei.startingPoint.first; ++ i ){
			if ( B[i][y] != '-' and word[i-linei.startingPoint.first] != B[i][y]) return false;
		}
	}
	if ( linei.d == Horizontal ) {
		int x = linei.startingPoint.first ;
		for ( int i = linei.startingPoint.second; i < linei.length + linei.startingPoint.second ; ++ i ) {
			if ( B[x][i] != '-' and word[i-linei.startingPoint.second] != B[x][i]) return false ;
		}
	}
	return true ;
}

void fill ( line & linei , word & w, vector<string> & B ) {
	if ( linei.d == Vertical ) {
		int y = linei.startingPoint.second ;
		for ( int i = linei.startingPoint.first; i < linei.length + linei.startingPoint.first ; ++ i )
			B[i][y] = w.CWword[i-linei.startingPoint.first] ;	
	}
	if ( linei.d == Horizontal ) {
		int x = linei.startingPoint.first ;
		for ( int i = linei.startingPoint.second; i < linei.length + linei.startingPoint.second  ; ++ i ) 
			B[x][i] = w.CWword[i-linei.startingPoint.second] ;
	}
	w.used = true ;
}

void unfill ( line & linei , word & w, vector<string> & B ) {
	if ( linei.d == Vertical ) {
		int y = linei.startingPoint.second ;
		for ( int i = linei.startingPoint.first; i < linei.length + linei.startingPoint.first; ++ i )
			B[i][y] = '-' ;
	}
	if ( linei.d == Horizontal ) {
		int x = linei.startingPoint.first ;
		for ( int i = linei.startingPoint.second; i < linei.length + linei.startingPoint.second ; ++ i ) 
			B[x][i] = '-' ;
	}
	w.used = false ;

}

bool solveCW ( vector<line> & lines , vector<word> & words, vector<string> & B  , int linei ) {
	if ( linei == lines.size()) return true ;
	cout << "Enter " <<  endl;

	for ( int i = 0 ; i < words.size() ; ++ i ) {
		if ( lines[linei].length == words[i].CWword.length() and words[i].used == false and canFill ( lines[linei], words[i].CWword, B )){
			printCW( B );
			fill ( lines[linei], words[i], B ) ;
			if ( solveCW ( lines, words, B, linei + 1 ) == true) return true ;
			unfill ( lines[linei], words[i],B);
			//return false ; 
		}
	}
	return false ;
}

int main () {
	/*
	vector<string> twoDCW = { 
		"**********",
		"**********",
		"*---------",
		"*-****-***",
		"*-****-***",
		"*-****-***",
		"*-********",
		"*-********",
		"*-********",
		"*-********"
	};
	*/
	vector<string> twoDCW = {
	"XXXXXX-XXX",
	"XX------XX",
	"XXXXXX-XXX",
	"XXXXXX-XXX",
	"XXX------X",
	"XXXXXX-X-X",
	"XXXXXX-X-X",
	"XXXXXXXX-X",
	"XXXXXXXX-X",
	"XXXXXXXX-X"
};

	string incWords = "ICELAND;MEXICO;PANAMA;ALMATY";

	vector<line> lines(0) ;
	vector<word> words(0);
	string stringBuilder = "";

	for ( auto & charVal : incWords) {
		if ( charVal == ';' ){
			words.push_back( word ( stringBuilder));
			stringBuilder = "";
		}
		else stringBuilder += charVal;
	}
	words.push_back( word ( stringBuilder)) ;

	//print words
	for ( auto & wordVal : words) cout << wordVal.CWword << endl;
	
	printCW ( twoDCW);



	auto start = std::chrono::system_clock::now();

	findVerticalLines ( twoDCW, lines  );
	cout << "after" << endl;
	findHorizontalLines ( twoDCW, lines ) ;



	for ( auto & lineVal : lines ) {
		cout << lineVal.d << " : " << lineVal.startingPoint.first << " : " << lineVal.startingPoint.second << " : " << lineVal.length << endl;
	}
	cout << endl;

	cout << solveCW(lines,words,twoDCW,0) << endl;

	printCW ( twoDCW);

	auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << endl;

    //print2d() ;

	return 0;
}