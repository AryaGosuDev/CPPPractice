
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>

using namespace std ;

unsigned nChoosek( unsigned n, unsigned k ){
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    int result = n;
    for( int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

string isValid(string s) {

	unordered_map <char, int> charCountMap = {} ;

	for ( auto & charVal : s ) charCountMap[charVal]++ ;

	for ( auto & val : charCountMap ) cout << val.first << " " << val.second << endl ;

	bool removeUsed = false ;

	int pastVal = -1, newVal = -1, counter = 0 ;

	auto it = charCountMap.begin() ;

	while ( it != charCountMap.end()) {

		newVal = (*it).second;

		cout << "Past : " << pastVal << " : newVal : " << newVal << endl ;

		if ( pastVal == -1 ) pastVal = (*it).second ;
		else {
			if ( newVal != pastVal) {
				if ( removeUsed == true ) return "NO" ;
				removeUsed = true ;
				if ( counter == 1 && newVal == 1) {
					
					if ( pastVal == 2 && (*(next(it,1))).second > 2 ) return "NO" ;
					else if ( pastVal > 2) {} 
					else pastVal = -1 ; 
				}
				else if ( counter == 1 && pastVal == 1 ) {
					if ( newVal == 2 && (*(next(it,1))).second > 2) return "NO" ;
					else if ( newVal > 2) { pastVal = newVal ;}
					else pastVal = -1 ;
				}
				else if ( pastVal == 1 ) {
					if ( newVal > 2 ) return "NO" ;
				}
				else if ( newVal == 1 ) {}
				else if ( abs ( newVal - pastVal) > 1) return "NO" ;
				else if ( newVal > pastVal) {}
				else if ( pastVal > newVal ) {
					if ( counter > 1) return "NO" ;
					else pastVal = newVal ;
				}
			}
		}
		counter	 ++ ;
		cout << "Counter : " << counter << endl ;
		it = next ( charCountMap.begin(), counter );
	}
	return "YES" ;
}

int main () {

	string testString = "ibfdgaeadiaefgbhbdghhhbgdfgeiccbiehhfcggchgghadhdhagfbahhddgghbdehidbibaeaagaeeigffcebfbaieggabcfbiiedcabfihchdfabifahcbhagccbdfifhghcadfiadeeaheeddddiecaicbgigccageicehfdhdgafaddhffadigfhhcaedcedecafeacbdacgfgfeeibgaiffdehigebhhehiaahfidibccdcdagifgaihacihadecgifihbebffebdfbchbgigeccahgihbcbcaggebaaafgfedbfgagfediddghdgbgehhhifhgcedechahidcbchebheihaadbbbiaiccededchdagfhccfdefigfibifabeiaccghcegfbcghaefifbachebaacbhbfgfddeceababbacgffbagidebeadfihaefefegbghgddbbgddeehgfbhafbccidebgehifafgbghafacgfdccgifdcbbbidfifhdaibgigebigaedeaaiadegfefbhacgddhchgcbgcaeaieiegiffchbgbebgbehbbfcebciiagacaiechdigbgbghefcahgbhfibhedaeeiffebdiabcifgccdefabccdghehfibfiifdaicfedagahhdcbhbicdgibgcedieihcichadgchgbdcdagaihebbabhibcihicadgadfcihdheefbhffiageddhgahaidfdhhdbgciiaciegchiiebfbcbhaeagccfhbfhaddagnfieihghfbaggiffbbfbecgaiiidccdceadbbdfgigibgcgchafccdchgifdeieicbaididhfcfdedbhaadedfageigfdehgcdaecaebebebfcieaecfagfdieaefdiedbcadchabhebgehiidfcgahcdhcdhgchhiiheffiifeegcfdgbdeffhgeghdfhbfbifgidcafbfcd" ;

	auto start = std::chrono::system_clock::now();

	cout << isValid(testString) << endl;

	auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << endl;
    
	return 0;
}