#include <iostream>
#include <stdio.h>

using std::cout;
using std::cin;
using std::endl;

int main () {
    char * keyInput ;

    do {
      cout << "1. Make a new room" << endl;
      cout << "2. Make a room connection" << endl;
      cout << "3. Find if a room is connectec" << endl;
      cout << "4. Find shortest path to room" << endl ;
      cout << "q. quit" << endl ;
      std::cin >> keyInput;

      cout << strlen ( keyInput) << endl ;

      switch (*keyInput) {
        case '1':
          cout << "Enter name of a new room : " << endl;
          std::cin >> keyInput;
          if ( )

        break;
        case '2':
        break;
        case '3':
        break;
        case '4':
        break;
        default:
        break ;
      }
    } while ( *keyInput != 'q' ) ;

    return 0;
}
