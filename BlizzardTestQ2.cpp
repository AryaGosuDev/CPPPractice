#include <iostream>
#include <vector>

using std::cout ;
using std::endl ;

void printV ( std::vector<char> & v) {
  for ( auto & v : v)
    cout << v ;
  cout << endl ;
}

inline void swap ( std::vector<char> & input, const int & indxA, const int  & indxB ) {
  char temp = input[indxA] ;
  input[indxA] = input[indxB];
  input[indxB] = temp;
}

void merge ( std::vector<char> & input , unsigned int * bitVectorOrder,
             int startIndexA, const int sizeOfArrayA,
             int startIndexB, const int sizeOfArrayB ) {

               cout << startIndexA << " " << sizeOfArrayA << " " << startIndexB << " "  << sizeOfArrayB << endl ;

    //int workingIndex = startIndexA ;

    int lastIndexA = sizeOfArrayA + startIndexA , lastIndexB = sizeOfArrayB + startIndexB  ;

    while ( startIndexA < lastIndexA && startIndexB < lastIndexB ) {

      if ( bitVectorOrder[input[startIndexA]] > bitVectorOrder[input[startIndexB]] ) {
        swap ( input , startIndexA, startIndexB );
        startIndexA++ ;

      }
      else  startIndexA ++ ;
      //workingIndex++;
    }

    while ( startIndexA < lastIndexA - 1 ) {

      if ( bitVectorOrder[input[startIndexA]] > bitVectorOrder[input[startIndexA+1]]) {
        swap ( input ,startIndexA,startIndexA+1  );
      }
      startIndexA ++ ;
    }

    while ( startIndexB < lastIndexB - 1 ) {
      //cout << 33 << endl;
      if ( bitVectorOrder[input[startIndexB]] > bitVectorOrder[input[startIndexB+1]]) {
        swap ( input ,startIndexB,startIndexB+1  );
      }
      startIndexB ++ ;
    }
    printV ( input ) ;
}

// perform merge sort in place
void mergeSort ( std::vector<char> & input, unsigned int * bitVectorOrder ,
                 const int startIndex, const int sizeOfArray) {

  if ( sizeOfArray == 1 ) return ;

  //cout << startIndex << " " << sizeOfArray  << " "  ;
  mergeSort ( input, bitVectorOrder, startIndex, sizeOfArray / 2 );
  mergeSort ( input, bitVectorOrder, startIndex + sizeOfArray / 2, sizeOfArray - sizeOfArray / 2 ) ;

  merge ( input, bitVectorOrder,
          startIndex, sizeOfArray / 2,
          startIndex + sizeOfArray / 2, sizeOfArray - sizeOfArray / 2 ) ;

}

void SortLetters(char * input, char * sortOrder) {

  if ( input == NULL || sortOrder == NULL ) return ;

  //create a bit vector so as to order the input string with respect to the order of the sortOrder string
  //assign each value in the sortOrder a higher value than the char before it
  //need to construct a vector that is large enough to hold all the values of a char
  //the size of the vector should be 2^(8*sizeof(char))
  //will ensure speed for increased fixed space
  unsigned int bitVectorOrder[256] = {};

  //a c-style string ends with a 0 ( null )
  //cannot ensure that the size of the data pointed to by a char * contains exactly all the letters
  for ( size_t i = 0 ; sortOrder[i] != 0 ; ++ i )
    bitVectorOrder[sortOrder[i]] = i;

  for ( int i = 0 ; i < 256 ; ++ i ) {
    //cout << bitVectorOrder[i] << " " ;
  }

  cout << endl;

  std::vector<char> inputString;
  size_t inputCharCount = 0;

  for ( size_t i = 0 ; input[i] != 0 ; ++ i) {
    inputString.push_back ( input[i] );
    inputCharCount ++ ;
  }

  inputString.resize(inputCharCount);

  //initial mergesort call
  mergeSort ( inputString, bitVectorOrder, 0, inputCharCount);

  //for ( size_t i = 0 ; i < inputCharCount; i++)
    //input[i] = inputString[i] ;

  //std::cout << inputString[6] << std::endl;
  printV ( inputString) ;

}

int main() {

  //char * inputString = "sort the letters in this stringg" ;
  //char * sortOrder = " isetlgornh" ;

  char * inputString = "sort  " ;
  char * sortOrder = " rtso" ;

  SortLetters ( inputString, sortOrder);

  return 0;
}
