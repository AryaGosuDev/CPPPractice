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

using namespace std;

void addToMappedList ( list<unordered_multimap<char,pair<bool, int>>::iterator> & currentMappedList, unordered_multimap<char, pair<bool, int>>::iterator & i ) {

	auto listBegin = currentMappedList.begin(), listEnd = currentMappedList.end();
	bool foundLoc = false;

	while (listBegin != listEnd) {
		if (foundLoc == false && (*listBegin)->second.second > i->second.second) {
			listBegin = currentMappedList.insert(listBegin, i);
			foundLoc = true;
			listBegin++;
		}
		else if (foundLoc == true) {
			(*listBegin)->second.first = false;
			listBegin = currentMappedList.erase(listBegin);
		}
		if ( foundLoc == false ) listBegin++;
	}

	if (foundLoc == false) {
		currentMappedList.push_back(i);
	}

	if (currentMappedList.size() == 0) {
		currentMappedList.insert(listBegin, i);
	}
}

int commonChild ( string s1, string s2 ) {
	int maxCount = 0, currentCount = 0;
	unordered_multimap<char, pair<bool, int>> placementMap( s2.length() ) ;

	for ( int i = 0 ; i < s2.length(); ++i ) {
		placementMap.insert ( pair<char, pair<bool, int>>(s2[i], pair<bool,int> ( false, i )) );
	}

	//for ( auto & placementMapVal : placementMap  ) {
		//cout << placementMapVal.first << " : " << placementMapVal.second.first << " " << placementMapVal.second.second << endl;
	//}

	list<unordered_multimap<char,pair<bool, int>>::iterator> currentMappedList(0);

	for ( auto & charVal : s1 ) {
		//cout << charVal << endl;
		if ( placementMap.find(charVal) != placementMap.end()) {

			pair<unordered_multimap<char, pair<bool, int>>::iterator,unordered_multimap<char, pair<bool, int>>::iterator> rangeIt = placementMap.equal_range(charVal) ;
			
			bool foundFirstCharValue = false;

			while ( !foundFirstCharValue && rangeIt.first != rangeIt.second ) {
				//cout << "in loop" << endl;
				if ( (rangeIt.first)->second.first == false) {
					(rangeIt.first)->second.first = true ;
					addToMappedList ( currentMappedList , rangeIt.first ) ;

					currentCount = currentMappedList.size();
					
					if ( currentCount > maxCount) maxCount = currentCount ;
					foundFirstCharValue = true ;
				}
				rangeIt.first ++;
				//cout << "found " << currentCount << endl;
			}
		}
	}
	return maxCount ;
}

int main () {
/*
	LL_Node * head = new LL_Node() ;
	LL_Node * current = head ;
	head->data = 1;
	head->next = NULL ;

	current->next = new LL_Node() ;
	current = current->next ;
	current->next = NULL ;
	current->data = 2 ;

	current->next = new LL_Node() ;
	current = current->next ;
	current->next = NULL ;
	current->data = 3 ;

	current->next = new LL_Node() ;
	current = current->next ;
	current->next = NULL ;
	current->data = 4 ;

	current->next = new LL_Node() ;
	current = current->next ;
	current->next = NULL ;
	current->data = 5 ;
*/
	//printLLRev ( head ) ;

	cout << commonChild ( "WEWOUCUIDGCGTRMEZEPXZFEJWISRSBBSYXAYDFEJJDLEBVHHKS", 
						  "FDAGCXGKCTKWNECHMRXZWMLRYUCOCZHJRRJBOAJOQJZZVUYXIC" ) << " : Should be 15" << endl;

	cout << commonChild ( "FDAGCXGKCTKWNECHMRXZWMLRYUCOCZHJRRJBOAJOQJZZVUYXIC", 
						  "WEWOUCUIDGCGTRMEZEPXZFEJWISRSBBSYXAYDFEJJDLEBVHHKS" ) << " : Should be 15" << endl;

	//right answer is 15

	

	return 0;
}