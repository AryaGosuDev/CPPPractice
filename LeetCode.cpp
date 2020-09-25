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
#include <unorderedset>
#include <stack>
#include <algorithm>
#include <thread>
#include <atomic>
#include <random>
#include "mat3x3.h"
#include "vec3.h"

//typical cmd line compile : g++ --std=c++14 -O0 -Wall -Wextra -fsanitize=address -fsanitize=undefined -g LeetCode.cpp -o run

using namespace std ;

#define CHARsIZE 26

struct PrefixTrie {
	bool isLeaf;
	PrefixTrie * character[CHARsIZE];
	//function<bool(string )> deletion = bind ( &PrefixTrie::deleteH , this,  std::placeholders::_1, this) ;
	
	PrefixTrie() : isLeaf ( false ) {
		memset ( (void*)character, 0 , sizeof ( PrefixTrie * ) * CHARsIZE ) ;
	}

	~PrefixTrie() { printf ( "PrefixTrie dtor called") ;}

	void insert(std::string key) {
		// start from root node
		PrefixTrie * curr = this;
		for (size_t i = 0; i < key.length(); i++) {
			// create a new node if path doesn't exists
			if (curr->character[key[i] - 'a'] == NULL) curr->character[key[i]-'a'] = new PrefixTrie();
			curr = curr->character[key[i]-'a'];
		}
		curr->isLeaf = true;
	}

	bool deleteH( std::string key , PrefixTrie * curr) {
		if (curr == NULL) return false;
		if (key.length()) {
			if (curr != NULL and curr->character[key[0]-'a'] != NULL and deleteH( key.substr(1), curr->character[key[0]-'a']) and curr->isLeaf == false) {
				if (!haveChildren(curr)) {
					delete curr; curr = NULL ; return true;
				}
				else return false;
			}
		}
		if (key.length() == 0 and curr->isLeaf == true) {
			if (!haveChildren(curr)) {
				delete curr; curr = NULL ; return true;
			}
			else {	
				curr->isLeaf = false; return false;
			}
		}
		return false;
	}

	bool search(const std::string key) const {
		const PrefixTrie *  curr = this;
		for (size_t i = 0; i < key.length(); i++) {
			curr = curr->character[key[i]-'a'];
			if (curr == NULL) return false;
		}
		return curr->isLeaf;
	}

	bool haveChildren(PrefixTrie const * curr) const {
		for (size_t i = 0; i < CHARsIZE; i++)
			if (curr->character[i] != NULL) return true;
		return false;
	}

};

struct pTMarixNode {
	uint32_t lengthOfWord ; PrefixTrie * pT ; bool ending ;
	pTMarixNode ( PrefixTrie  * const pT , bool ending, uint32_t l ) : 
		lengthOfWord (l), pT ( pT ), ending ( ending ) {}
};

bool wordBreak(string s, vector<string>& wordDict) {
	uint32_t n = s.size() ;
	
	PrefixTrie * tree = new PrefixTrie() ;
	for ( auto & v : wordDict) tree->insert( v ) ;
	
	vector < vector < pTMarixNode >> wordMatrix ( n ) ;
	for ( uint32_t i = 0 ; i < n ; ++ i ) {
		if ( i == 0 ) {
			if ( tree->character[s[i] - 'a'] != NULL ) {
				wordMatrix[i].push_back ( pTMarixNode( tree->character[s[i] - 'a'], 
										  			   tree->character[s[i] - 'a']->isLeaf, 1)) ;
			}
			else return false ;
		}
		else {
			bool added = false ;
			if ( tree->character[s[i] - 'a'] != NULL) {
				wordMatrix[i].push_back ( pTMarixNode( tree->character[s[i] - 'a'], 
										  			   tree->character[s[i] - 'a']->isLeaf,1));
				added = true ;
			}
			for ( uint32_t i_prev = 0 ; i_prev < wordMatrix[i-1].size() ; ++i_prev ) {
				PrefixTrie * tempPointer = wordMatrix[i-1][i_prev].pT->character[s[i] - 'a'] ;
				if ( tempPointer != NULL ){
					wordMatrix[i].push_back ( pTMarixNode ( tempPointer, tempPointer->isLeaf,
															wordMatrix[i-1][i_prev].lengthOfWord+1 ));
					added = true ;
				}
				
			}
			if ( added == false) return false ;
		}
	}
	/*
	for ( auto & v : wordMatrix) {
		for  ( auto & vv : v ) {
			cout << vv.lengthOfWord << " " << vv.pT << " " << vv.ending << " " << endl ;
		}
		cout << endl << endl ;
	}
*/
	cout << "here" << endl ;
	
	if ( wordMatrix[n-1].size() == 0 ) return false;
	stack<pair<uint32_t,uint32_t>> wordStack ;
	for ( uint32_t i = 0 ; i < wordMatrix[n-1].size(); ++ i ) {
		if ( wordMatrix[n-1][i].ending == true )
			wordStack.push ( { n - 1, wordMatrix[n-1][i].lengthOfWord}) ;
	}
	while ( !wordStack.empty()){
		int newIndx = wordStack.top().first - wordStack.top().second ;
		if ( newIndx < 0 ) return true ;
		wordStack.pop();
		for ( uint32_t i = 0 ; i < wordMatrix[newIndx].size(); ++ i ) {
			if ( wordMatrix[newIndx][i].ending == true ) {
				wordStack.push ( { newIndx, wordMatrix[newIndx][i].lengthOfWord}) ;
			}
		}
	}
	return false ;
}

int main () {

	//"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	//["aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa","ba"]
	string s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	//vector<string> dict = {"kfomka","hecagbngambii","anobmnikj","c","nnkmfelneemfgcl","ah","bgomgohl","lcbjbg","ebjfoiddndih","hjknoamjbfhckb","eioldlijmmla","nbekmcnakif","fgahmihodolmhbi","gnjfe","hk","b","jbfgm","ecojceoaejkkoed","cemodhmbcmgl","j","gdcnjj","kolaijoicbc","liibjjcini","lmbenj","eklingemgdjncaa","m","hkh","fblb","fk","nnfkfanaga","eldjml","iejn","gbmjfdooeeko","jafogijka","ngnfggojmhclkjd","bfagnfclg","imkeobcdidiifbm","ogeo","gicjog","cjnibenelm","ogoloc","edciifkaff","kbeeg","nebn","jdd","aeojhclmdn","dilbhl","dkk","bgmck","ohgkefkadonafg","labem","fheoglj","gkcanacfjfhogjc","eglkcddd","lelelihakeh","hhjijfiodfi","enehbibnhfjd","gkm","ggj","ag","hhhjogk","lllicdhihn","goakjjnk","lhbn","fhheedadamlnedh","bin","cl","ggjljjjf","fdcdaobhlhgj","nijlf","i","gaemagobjfc","dg","g","jhlelodgeekj","hcimohlni","fdoiohikhacgb","k","doiaigclm","bdfaoncbhfkdbjd","f","jaikbciac","cjgadmfoodmba","molokllh","gfkngeebnggo","lahd","n","ehfngoc","lejfcee","kofhmoh","cgda","de","kljnicikjeh","edomdbibhif","jehdkgmmofihdi","hifcjkloebel","gcghgbemjege","kobhhefbbb","aaikgaolhllhlm","akg","kmmikgkhnn","dnamfhaf","mjhj","ifadcgmgjaa","acnjehgkflgkd","bjj","maihjn","ojakklhl","ign","jhd","kndkhbebgh","amljjfeahcdlfdg","fnboolobch","gcclgcoaojc","kfokbbkllmcd","fec","dljma","noa","cfjie","fohhemkka","bfaldajf","nbk","kmbnjoalnhki","ccieabbnlhbjmj","nmacelialookal","hdlefnbmgklo","bfbblofk","doohocnadd","klmed","e","hkkcmbljlojkghm","jjiadlgf","ogadjhambjikce","bglghjndlk","gackokkbhj","oofohdogb","leiolllnjj","edekdnibja","gjhglilocif","ccfnfjalchc","gl","ihee","cfgccdmecem","mdmcdgjelhgk","laboglchdhbk","ajmiim","cebhalkngloae","hgohednmkahdi","ddiecjnkmgbbei","ajaengmcdlbk","kgg","ndchkjdn","heklaamafiomea","ehg","imelcifnhkae","hcgadilb","elndjcodnhcc","nkjd","gjnfkogkjeobo","eolega","lm","jddfkfbbbhia","cddmfeckheeo","bfnmaalmjdb","fbcg","ko","mojfj","kk","bbljjnnikdhg","l","calbc","mkekn","ejlhdk","hkebdiebecf","emhelbbda","mlba","ckjmih","odfacclfl","lgfjjbgookmnoe","begnkogf","gakojeblk","bfflcmdko","cfdclljcg","ho","fo","acmi","oemknmffgcio","mlkhk","kfhkndmdojhidg","ckfcibmnikn","dgoecamdliaeeoa","ocealkbbec","kbmmihb","ncikad","hi","nccjbnldneijc","hgiccigeehmdl","dlfmjhmioa","kmff","gfhkd","okiamg","ekdbamm","fc","neg","cfmo","ccgahikbbl","khhoc","elbg","cbghbacjbfm","jkagbmfgemjfg","ijceidhhajmja","imibemhdg","ja","idkfd","ndogdkjjkf","fhic","ooajkki","fdnjhh","ba","jdlnidngkfffbmi","jddjfnnjoidcnm","kghljjikbacd","idllbbn","d","mgkajbnjedeiee","fbllleanknmoomb","lom","kofjmmjm","mcdlbglonin","gcnboanh","fggii","fdkbmic","bbiln","cdjcjhonjgiagkb","kooenbeoongcle","cecnlfbaanckdkj","fejlmog","fanekdneoaammb","maojbcegdamn","bcmanmjdeabdo","amloj","adgoej","jh","fhf","cogdljlgek","o","joeiajlioggj","oncal","lbgg","elainnbffk","hbdi","femcanllndoh","ke","hmib","nagfahhljh","ibifdlfeechcbal","knec","oegfcghlgalcnno","abiefmjldmln","mlfglgni","jkofhjeb","ifjbneblfldjel","nahhcimkjhjgb","cdgkbn","nnklfbeecgedie","gmllmjbodhgllc","hogollongjo","fmoinacebll","fkngbganmh","jgdblmhlmfij","fkkdjknahamcfb","aieakdokibj","hddlcdiailhd","iajhmg","jenocgo","embdib","dghbmljjogka","bahcggjgmlf","fb","jldkcfom","mfi","kdkke","odhbl","jin","kcjmkggcmnami","kofig","bid","ohnohi","fcbojdgoaoa","dj","ifkbmbod","dhdedohlghk","nmkeakohicfdjf","ahbifnnoaldgbj","egldeibiinoac","iehfhjjjmil","bmeimi","ombngooicknel","lfdkngobmik","ifjcjkfnmgjcnmi","fmf","aoeaa","an","ffgddcjblehhggo","hijfdcchdilcl","hacbaamkhblnkk","najefebghcbkjfl","hcnnlogjfmmjcma","njgcogemlnohl","ihejh","ej","ofn","ggcklj","omah","hg","obk","giig","cklna","lihaiollfnem","ionlnlhjckf","cfdlijnmgjoebl","dloehimen","acggkacahfhkdne","iecd","gn","odgbnalk","ahfhcd","dghlag","bchfe","dldblmnbifnmlo","cffhbijal","dbddifnojfibha","mhh","cjjol","fed","bhcnf","ciiibbedklnnk","ikniooicmm","ejf","ammeennkcdgbjco","jmhmd","cek","bjbhcmda","kfjmhbf","chjmmnea","ifccifn","naedmco","iohchafbega","kjejfhbco","anlhhhhg"} ;
	std::vector<string> dict = {"a","aa","aaa","aaaa","aaaaa","aaaaaa"} ;
	cout << wordBreak ( s , dict )   << endl ;

	return 0;

	
}