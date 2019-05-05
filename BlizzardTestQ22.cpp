//Arya Mahini
//time spent : 4 hours
//compiled using g++ -std=c++11
//approach : initially I designed this algorithm to perform in in-place mergeSort
//but finally discovered that it is orders of magnitude less efficient than the standard
//vector copy merge sort. I designed a bit vector to order the ascii characters to a specific
//order and finally sorted the letters according to the sortOrder ordering.
//runtime : O ( n lg n ) -> theta ( n lg n )
//future / advancements : on very very large strings, the memory capacity of the program stack may
//overflow and so an inplace merge can be used. Also, a heap approach would also work. Better yet, a
//precomputed heap pool that exactly allocates all the necessary memory for a deterministic merge sort.
#include <iostream>
#include <vector>

using std::cout ;
using std::endl ;

//print a vector
inline void printV ( const std::vector<char> & inputVec) {
  for ( auto & val : inputVec)
    cout << val ;
  cout << endl ;
}

//merge function
//create a new merge vector in order to store the results of comparions between L1 and L2
std::vector<char> merge(std::vector<char> & L1, std::vector<char> & L2, unsigned int * bitVectorOrder) {

	std::vector<char> mergeVec;

	size_t IndexL1 = 0, IndexL2 = 0;

	while (IndexL1 < L1.size() && IndexL2 < L2.size()) {
		if (bitVectorOrder[L1[IndexL1]] > bitVectorOrder[L2[IndexL2]])
			mergeVec.push_back(L2[IndexL2++]);
		else
			mergeVec.push_back(L1[IndexL1++]);
	}

	while (IndexL1 < L1.size())
		mergeVec.push_back(L1[IndexL1++]);

	while (IndexL2 < L2.size())
		mergeVec.push_back(L2[IndexL2++]);

  mergeVec.resize(L1.size() + L2.size());

	return mergeVec;
}

//a divide and conquer merge sort algorithm
//divides the data into n/x subarrays each performing n/x work where x > 1 and x is a base 2 number
std::vector<char> mergeSort(std::vector<char> & input, unsigned int * bitVectorOrder) {

	if (input.size() == 1) return input;

  //create a vector that will begin from the first element of input
  //to one past the last element of that particular sub array
  //input.end() == one past the last element of a subarray
	std::vector<char> L1(input.begin(), input.begin() + (input.size() / 2));
	std::vector<char> L2(input.begin() + (input.size() / 2), input.end());

  //return from sub array calls
	L1 = mergeSort(L1, bitVectorOrder);
	L2 = mergeSort(L2, bitVectorOrder);

	return merge(L1, L2, bitVectorOrder);
}

//every character in the input string also appears in the sortorder string. Don't need to catch non-strored characters.
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

  std::vector<char> inputString;
  size_t inputCharCount = 0;

  for ( size_t i = 0 ; input[i] != 0 ; ++ i) {
    inputString.push_back ( input[i] );
    inputCharCount ++ ;
  }

  inputString.resize(inputCharCount);

  //initial mergesort call
  //can choose to make this mergeSort an in place mergesort to save vector copies and space but will be less efficient
  inputString = mergeSort ( inputString, bitVectorOrder);

  //copy back into input string
  for ( size_t i = 0 ; i < inputCharCount; i++)
    input[i] = inputString[i] ;

}

int main() {

  char inputString[] = "sort the letters in this string" ;
  char sortOrder[] = " isetlgornh" ;
  SortLetters ( inputString, sortOrder);
  cout << inputString << endl;

  char inputString1[] = "cfgfdgdfkdfjghfkdjhgfdjhdfkjghdfgjkdfghdfjkghdkjgdfhgjdkgfkhdgjfkdgkfjdhjdkhgfjdghdfkjgfdjghkfdjghfdjgdfkghdfgjkd" ;
  char sortOrder1[] = " acf$gdbhkj@!" ;
  SortLetters ( inputString1, sortOrder1);
  cout << inputString1 << endl;

  char inputString2[] = "^%&^%^ %^&% &^%^$$&^  %^%&^ %^%&^" ;
  char sortOrder2[] = " acsdjkfhdsjfhdskjfhdsj fhdsjkfhdsfjkdshfjdskfhsdkjfhsdjkiuwhewiuh$%$#%%^&*(*&(&*^&^&%^#$#@(*&(f$@! " ;
  SortLetters ( inputString2, sortOrder2);
  cout << inputString2 << endl;

  char inputString4[] = "sort the letters in this stringggggggg" ;
  char sortOrder4[] = " isetlgornh" ;
  SortLetters ( inputString4, sortOrder4);
  cout << inputString4 << endl;

  char inputString5[] = "FOR TEH HORDE" ;
  char sortOrder5[] = "FOR THED" ;
  SortLetters ( inputString5, sortOrder5);
  cout << inputString5 << endl;

  return 0;
}
