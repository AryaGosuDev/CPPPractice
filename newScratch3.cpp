#include <iostream>
#include <map>
#include <set>
#include <cmath>
#include <vector>
#include <memory>
#include <algorithm>
#include <stack>
#include <list>
#include <unordered_map>
#include <queue>

using namespace std ;

int x_Moves[] = { -2, -1,1,2,2, 1,-1,-2 };
int y_Moves[] = {  1,  2,2,1,-1,-2,-2,-1};

bool canMove ( vector<vector<int>> & b, int x , int y ) {
	return ( x >= 0 and x < 4 and y >= 0 and y < 4 and (( b[x][y] >= 1 and b[x][y] <= 9) or b[x][y] == 11) ) ;
}

int kt ( vector<vector<int>> & b, int x, int y, int i ) {
	if ( i == 0 ) return 0 ;

	int moves = 0 ;

	for ( int j = 0 ; j < 8 ; ++j) {
		int newXMove = x + x_Moves[j] ;
		int newYMove = y + y_Moves[j] ;

		if ( canMove ( b, newXMove, newYMove)) {

			moves += 1 + kt ( b, newXMove, newYMove, i - 1);
		}
	}
	return moves ;
}

int main() { 

	vector<vector<int>> b = {{1,2,3}, {4,5,6} , {7,8,9}, {10,11,12}} ;

	for ( auto & v : b ) {
		for ( auto v1 : v ) {
			cout << v1 << " " ;
		}
		cout << endl;
	}
	cout << endl ;

	//cout << b[3][0] << endl ;

	cout << kt ( b, 0,0,2) ;

    return 0; 
} 