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
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <thread>
#include <atomic>
#include <random>
#include "mat3x3.h"
#include "vec3.h"

//typical cmd line compile : g++ --std=c++14 -O0 -Wall -Wextra -fsanitize=address -g main.cpp -o return

using namespace std ;

istream & retStream (  istream & _in) {
  istream<char> eof ;

  while ( _in != eof) {
    string s ;
    if ( getline ( _in, s )){
      cout << s << endl ;
    }
  }
  _in.clear() ;
  return _in ;
}

//int main(int argc, char *argv[]) {
int main() {
  ifstream inFile ( "gppCommands.txt");
  return 0;
}