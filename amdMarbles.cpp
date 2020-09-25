//competitive programming includes
#include <string>
#include <iostream>
#include <type_traits>
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
//#include "mat3x3.h"
//#include "vec3.h"

//typical cmd line compilation : g++ --std=c++14 -O0 -Wall -Wextra -fsanitize=address -g amdMarbles.cpp -o run

#define numOfDirectionsPerMove 3
using namespace std ;
//split the input string to an array of ints
vector<int> split_string(string input_string) {
	string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {return x == y and x == ' ';});
	input_string.erase(new_end, input_string.end());
    while (input_string[input_string.length() - 1] < '0' or input_string[input_string.length() - 1] > '9' ) input_string.resize( input_string.length() - 1 ) ;
	
    vector<int> splits;
    char delimiter = ' '; size_t i = 0;
    size_t pos = input_string.find(delimiter);
	
    while (pos != string::npos) {
        splits.push_back(atoi(input_string.substr(i, pos - i).c_str()));
        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }
    splits.push_back(atoi(input_string.substr(i, min(pos, input_string.length()) - i + 1).c_str()));
    return splits;
}
// the enum types for the all possible moves from a position
enum Direction { downLeft = 0 , down , downRight } ;
//the offset shifts to the indexes for each potential move.
int x_Moves[numOfDirectionsPerMove] ;
int y_Moves[numOfDirectionsPerMove] ;
//is the mable move a legit move inside the board
bool isLegitMove ( const size_t & sizeRows, const size_t & sizeCols , const int && x, const int && y ) {
	return x >= 0 and y >= 0 and x < sizeRows and y < sizeCols ;
}
//a node in the board to determine whether the path from this position has already been calculated
struct boardNode {
	int pathCost ;
	Direction nextPathDirection ;
	//start with the max value, will reduce from max value
	boardNode() : pathCost ( numeric_limits<int>::max() ) {} 
	boardNode ( int  _pathCost) : pathCost ( _pathCost) , nextPathDirection ( (Direction)(Direction::down) )  {} 
};
//return the resulting optimal position from each column because a marble released from a column might use another column to optimize its path
//also return a string representing the shortest path
pair<size_t, string> returnShortestPath ( vector<vector<boardNode *>> & _c, size_t & _marble_pos, const size_t & _rows, const size_t & _cols ) {
	string resultString ;
	//start from a row above the first row
	int x = -1, y = _marble_pos ; size_t startingMarbleCol = _marble_pos ;
	//choose which column to start from
	for ( size_t i = 0 ; i < numOfDirectionsPerMove ; ++ i ) {
		if ( isLegitMove ( _rows, _cols , x + x_Moves[i] , y + y_Moves[i] ) and _c[0][startingMarbleCol]->pathCost > _c[x + x_Moves[i]][y + y_Moves[i]]->pathCost )
			startingMarbleCol = y + y_Moves[i] ;
	}
	//now from the first row, find the correct path to the last row 
	x++ ; y = startingMarbleCol ;
	while ( x < _rows) {
		resultString += "(" + to_string(x) + "," + to_string(y) + ")" ;
		if ( x + 1 != _rows) resultString += ",";
		Direction nextPathD = _c[x][y]->nextPathDirection ;
		x += x_Moves[nextPathD] ; y += y_Moves[nextPathD];
	}
	resultString += "\n" ;
	return pair<size_t, string> { startingMarbleCol,resultString } ;
}
// make the solution substructure, pass in the original board
vector<vector<boardNode *>> ShortestPath ( vector<vector<int>> & _board, const size_t & _rows, const size_t & _cols ) {
	vector<vector<boardNode *>> result ( _rows, vector<boardNode *> ( _cols, NULL ) ) ;
	//fill the last row of the board because its shortest paths are its respective board values
	for ( size_t i = 0 ; i < _cols ; ++ i ) result[_rows-1][i] = new boardNode ( _board[_rows-1][i] );
	
	//fill rest of result tensor using memoization from the previous row
	for ( int i = _rows - 2 ; i >= 0 ; i -- )  {
		for ( int j = _cols - 1; j >= 0 ; --j ) {
			result[i][j] = new boardNode() ;
			for ( int moves = numOfDirectionsPerMove - 1; moves >= 0 ; --moves ) {
				//starting node value is the max int value
				if ( isLegitMove ( _rows, _cols, i + x_Moves[moves], j + y_Moves[moves] ) and result[i][j]->pathCost > result[i+x_Moves[moves]][j+y_Moves[moves]]->pathCost ) {
					//if path is shorter, assign new shortest path and its direction needed to travel
					result[i][j]->pathCost = result[i+x_Moves[moves]][j+y_Moves[moves]]->pathCost ;
					result[i][j]->nextPathDirection = (Direction)moves ;
				}
			}
			//add time cost to current node from original board
			result[i][j]->pathCost += _board[i][j];
		}
	}
	return result ;
}
//delete dynamic allocated memory from the resulting tensor
inline void deleteMemory ( vector<vector<boardNode *>> & _c ) {
	for ( auto & v : _c ) { for ( auto & vP : v ) delete vP ;}
}

template<typename T> void printBoard ( vector<vector<T*>> & _c ) {
		cout << "Print resulting paths : " << endl ;
		for ( auto & v : _c ) { for ( auto & vV : v ) cout << vV->pathCost << " : " << vV->nextPathDirection << "		" ; cout << endl ; }
}

template<typename T> void printBoard ( vector<vector<T>> & _c ) {
	cout << "Print board : " << endl ;
		for ( auto & v : _c ) { for ( auto & vV : v ) cout << vV << " " ; cout << endl ; }
}

int main (int argc, char *argv[]) {
	//original board
	vector<vector<int>> board ; size_t m = 0 , n = 0 ;
	x_Moves[Direction::downLeft] =  1;  x_Moves[Direction::down] =  1;  x_Moves[Direction::downRight] =  1 ;
	y_Moves[Direction::downLeft] =  -1;  y_Moves[Direction::down] =  0;  y_Moves[Direction::downRight] =  1 ; 
	if ( argc != 2)
		printf ( "Error, please pass in a file name to load the board data.\n") ;
	else {
		string line; ifstream myfile ( argv[1] ) ;
		if (myfile.is_open()) {
			while ( getline (myfile,line) ) {
			  m++ ;
			  vector<int> row_temp = split_string(line);
			  cout << "row " << m << " size : " << row_temp.size() <<   endl ;
			  if ( n == 0 ) n = row_temp.size() ;
			  else if ( n != row_temp.size() ) {myfile.close(); printf ( "Please make sure all the sizes of the columns are the same.\n" )  ; return 0 ; }
			  board.push_back ( vector<int>(0) ) ;
			  for ( auto & v : row_temp )  board.back().push_back( v ) ; 
			}
			myfile.close();
		}
		else printf ( "Error,could not load file.\n") ;	
	}
	if ( m == 0 ) {  printf ( "Please make sure the file has data rows and cols.\n" )  ; return 0 ;}
	printBoard (board ) ;
	vector<vector<boardNode *>> tempRes = ShortestPath ( board, m, n ) ; 
	//printBoard (tempRes ) ;
	for ( size_t i = 0 ; i < n ; ++ i ) {
		pair<size_t, string> tempPair = returnShortestPath ( tempRes , i, m, n ) ;
		cout << "The minimum time spent by the marble dropped at col " << i << " is " << tempRes[0][tempPair.first]->pathCost << ". Path : " << tempPair.second ;		
	}
	deleteMemory ( tempRes ) ;
	
	return 0 ;
}

