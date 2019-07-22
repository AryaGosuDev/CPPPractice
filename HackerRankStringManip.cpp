
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>

using namespace std ;

inline int returnArithSum ( int n , int a1, int aN ) {
    return (double)n * ( (double)(a1 + aN ) / 2.0 ) ;
}

// Complete the substrCount function below.
long substrCount(int n, string s) {
    using SubstrNode = pair<char,int>;
    long substrCount = 0;
    int size = 0 ;
    SubstrNode * substrArray = new SubstrNode[n] ;
    substrArray[size] = SubstrNode( s[0], 0);

    for ( auto & charVal : s ) {
    	if ( substrArray[size].first == charVal) substrArray[size].second ++ ;
    	else {
    			size++ ;
    			substrArray[size].first = charVal ;
    			substrArray[size].second ++ ;
    	}
    }

    for ( int i = 0 ; i <= size ; ++ i ) {
    	cout << substrArray[i].first << " : " << substrArray[i].second << endl;
    	substrCount += returnArithSum ( substrArray[i].second, 1, substrArray[i].second);
    	if ( substrArray[i].second == 1 && i - 1 >= 0 && i + 1 <= size && substrArray[i-1].first == substrArray[i+1].first) substrCount += min(substrArray[i-1].second , substrArray[i+1].second) ;
    }
    delete [] substrArray;
    return substrCount;
}

int main () {

	string testString = "mnonopoo" ;

	auto start = std::chrono::system_clock::now();

	cout << substrCount(testString.length(),testString) << endl;

	auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << endl;
    
	return 0;
}