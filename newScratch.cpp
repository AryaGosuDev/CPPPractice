#include <iostream>
#include <map>

using std::cout;
using std::endl;
using std::get;

typedef std::tuple<int, int> tuple ;

char * returnOrderSorted ( char * _input, char * _sortedOrder ) {
  std::map < char, int > orderMapping = {} ;

  for ( int indx = 0; _sortedOrder[indx] != 0 ; ++indx )
    orderMapping.insert ( { _sortedOrder[indx], 0 } );

  for ( int indx = 0 ; _input[indx] != 0 ; ++indx ) {
    if ( orderMapping.find (_input[indx]) != orderMapping.end())
      orderMapping[_input[indx]] ++ ;
  }

  int offsetCounter = 0 ;

  while ( (*_sortedOrder) != 0 ) {
    for ( int i = 0 ; i < orderMapping[(*_sortedOrder)] ; ++ i ) {
      _input[offsetCounter + i] = (*_sortedOrder) ;
    }
    offsetCounter += orderMapping[(*_sortedOrder)];
    _sortedOrder++;
  }

  _input[offsetCounter] = 0;
  return _input ;
}

tuple findtuple ( int  n, int (& arr1)[6] ) {

  std::map<int,int> hashTable = {} ;

  for ( int indx = 0 ; indx < 6 ; ++indx ) {
    auto currentKey = arr1[indx] ;
    if ( currentKey <= n ) {
      if ( hashTable.find ( currentKey) != hashTable.end())
        return tuple { indx , hashTable[currentKey]} ;
      else
        hashTable[n-currentKey] = indx ;
    }
  }
  return tuple { -1, -1 } ;
}

int main () {

  int array1[6] = {2,7,24,25,5,8};
  tuple thisT = findtuple ( 10, array1 ) ;
  cout << get<0>(thisT) << " : " << get<1>(thisT)  << endl;

  char sInput[] =  " testt";
  char sOrder[] =  "est";
  cout << returnOrderSorted ( sInput, sOrder ) << endl ;

  sOrder++ ;

  cout << *sOrder << endl ;

return 0;
}
