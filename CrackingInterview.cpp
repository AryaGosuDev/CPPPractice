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
#include "mat3x3.h"
#include "vec3.h"

//typical cmd line compilate : g++ --std=c++14 -O0 -Wall -Wextra -fsanitize=address -fsanitize=undefined -g CrackingInterview.cpp -o run

using namespace std ;
`
void drawLine(uint8_t (&screen) [160], int width, int x1, int x2, int y) {
	if ( x1 > x2 ) return ; size_t horLineWidth = x2 - x1 + 1 ;
	for ( size_t i = 0 ; i < horLineWidth ; ++ i ) screen[(y*width) + (x1++)] = 1 ;
}

int main () {
	const size_t h = 10, w = 16 ; uint8_t screen[w * h] ; size_t num = 0 ;
	for ( size_t i = 0 ; i < h ; ++ i ) {
		for ( size_t j = 0 ; j < w ; ++j ) screen[j + ( i * w )] = 0 ;
	}
	drawLine ( screen, w, 2, 10, 3 ) ;
	for_each ( begin(screen), end(screen), [&](uint8_t & x) { cout << (int)x << " " ; num++ ; if ( num == 16) { cout << endl; num = 0 ; } } ) ;
	cout << endl;

	return 0 ;
}
