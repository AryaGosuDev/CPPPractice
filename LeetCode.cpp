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

//typical cmd line compile : g++ --std=c++14 -O0 -Wall -Wextra -fsanitize=address -g LeetCode.cpp -o run

using namespace std ;

#define CHAR_SIZE 26

struct PrefixTrie {
	bool isLeaf;
	PrefixTrie * character[CHAR_SIZE];
	//function<bool(string )> deletion = bind ( &PrefixTrie::deleteH , this,  std::placeholders::_1, this) ;
	
	PrefixTrie() : isLeaf ( false ) {
		memset ( (void*)character, 0 , sizeof ( PrefixTrie * ) * CHAR_SIZE ) ;
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
		for (size_t i = 0; i < CHAR_SIZE; i++)
			if (curr->character[i] != NULL) return true;
		return false;
	}
};

bool wordBreak(string _s, vector<string>& wordDict) {
	stack < pair<PrefixTrie *, size_t> > s ;
	
	PrefixTrie * tree = new PrefixTrie() ;
	for ( auto & v : wordDict) tree->insert( v ) ;
	PrefixTrie * curr = NULL ;
	for ( size_t i = 0 ; i < _s.size() ; ++ i ) {
		char vC = _s[i] ;
		cout<< vC << " " << i <<   endl;
		
		if ( curr == NULL ) {
			if ( ( curr = tree->character[vC-'a']) == NULL){
				if ( s.empty()) return false ; else { i = s.top().second ; curr = s.top().first ; s.pop() ;}
			}
			else { if ( curr->isLeaf == true) { s.push ( {curr, i } ) ; curr = NULL ;}
			}
		}
		else {
			if ( ( curr = curr->character[vC-'a']) != NULL) {
				if ( curr->isLeaf == true){ s.push ( { curr, i }); curr = NULL ; }
			}
			else {
				if ( s.empty()) return false ;
				else { i = s.top().second ; curr = s.top().first ; s.pop() ; }
			}
		}
		if ( i == _s.size() - 1 and curr != NULL and curr->isLeaf != true) {
            i = s.top().second ; curr = s.top().first ; s.pop() ;
        }
	}
	return true ;
}

int main () {

	string s = "aaaaaaab";
	//vector<string> dict = {"kfomka","hecagbngambii","anobmnikj","c","nnkmfelneemfgcl","ah","bgomgohl","lcbjbg","ebjfoiddndih","hjknoamjbfhckb","eioldlijmmla","nbekmcnakif","fgahmihodolmhbi","gnjfe","hk","b","jbfgm","ecojceoaejkkoed","cemodhmbcmgl","j","gdcnjj","kolaijoicbc","liibjjcini","lmbenj","eklingemgdjncaa","m","hkh","fblb","fk","nnfkfanaga","eldjml","iejn","gbmjfdooeeko","jafogijka","ngnfggojmhclkjd","bfagnfclg","imkeobcdidiifbm","ogeo","gicjog","cjnibenelm","ogoloc","edciifkaff","kbeeg","nebn","jdd","aeojhclmdn","dilbhl","dkk","bgmck","ohgkefkadonafg","labem","fheoglj","gkcanacfjfhogjc","eglkcddd","lelelihakeh","hhjijfiodfi","enehbibnhfjd","gkm","ggj","ag","hhhjogk","lllicdhihn","goakjjnk","lhbn","fhheedadamlnedh","bin","cl","ggjljjjf","fdcdaobhlhgj","nijlf","i","gaemagobjfc","dg","g","jhlelodgeekj","hcimohlni","fdoiohikhacgb","k","doiaigclm","bdfaoncbhfkdbjd","f","jaikbciac","cjgadmfoodmba","molokllh","gfkngeebnggo","lahd","n","ehfngoc","lejfcee","kofhmoh","cgda","de","kljnicikjeh","edomdbibhif","jehdkgmmofihdi","hifcjkloebel","gcghgbemjege","kobhhefbbb","aaikgaolhllhlm","akg","kmmikgkhnn","dnamfhaf","mjhj","ifadcgmgjaa","acnjehgkflgkd","bjj","maihjn","ojakklhl","ign","jhd","kndkhbebgh","amljjfeahcdlfdg","fnboolobch","gcclgcoaojc","kfokbbkllmcd","fec","dljma","noa","cfjie","fohhemkka","bfaldajf","nbk","kmbnjoalnhki","ccieabbnlhbjmj","nmacelialookal","hdlefnbmgklo","bfbblofk","doohocnadd","klmed","e","hkkcmbljlojkghm","jjiadlgf","ogadjhambjikce","bglghjndlk","gackokkbhj","oofohdogb","leiolllnjj","edekdnibja","gjhglilocif","ccfnfjalchc","gl","ihee","cfgccdmecem","mdmcdgjelhgk","laboglchdhbk","ajmiim","cebhalkngloae","hgohednmkahdi","ddiecjnkmgbbei","ajaengmcdlbk","kgg","ndchkjdn","heklaamafiomea","ehg","imelcifnhkae","hcgadilb","elndjcodnhcc","nkjd","gjnfkogkjeobo","eolega","lm","jddfkfbbbhia","cddmfeckheeo","bfnmaalmjdb","fbcg","ko","mojfj","kk","bbljjnnikdhg","l","calbc","mkekn","ejlhdk","hkebdiebecf","emhelbbda","mlba","ckjmih","odfacclfl","lgfjjbgookmnoe","begnkogf","gakojeblk","bfflcmdko","cfdclljcg","ho","fo","acmi","oemknmffgcio","mlkhk","kfhkndmdojhidg","ckfcibmnikn","dgoecamdliaeeoa","ocealkbbec","kbmmihb","ncikad","hi","nccjbnldneijc","hgiccigeehmdl","dlfmjhmioa","kmff","gfhkd","okiamg","ekdbamm","fc","neg","cfmo","ccgahikbbl","khhoc","elbg","cbghbacjbfm","jkagbmfgemjfg","ijceidhhajmja","imibemhdg","ja","idkfd","ndogdkjjkf","fhic","ooajkki","fdnjhh","ba","jdlnidngkfffbmi","jddjfnnjoidcnm","kghljjikbacd","idllbbn","d","mgkajbnjedeiee","fbllleanknmoomb","lom","kofjmmjm","mcdlbglonin","gcnboanh","fggii","fdkbmic","bbiln","cdjcjhonjgiagkb","kooenbeoongcle","cecnlfbaanckdkj","fejlmog","fanekdneoaammb","maojbcegdamn","bcmanmjdeabdo","amloj","adgoej","jh","fhf","cogdljlgek","o","joeiajlioggj","oncal","lbgg","elainnbffk","hbdi","femcanllndoh","ke","hmib","nagfahhljh","ibifdlfeechcbal","knec","oegfcghlgalcnno","abiefmjldmln","mlfglgni","jkofhjeb","ifjbneblfldjel","nahhcimkjhjgb","cdgkbn","nnklfbeecgedie","gmllmjbodhgllc","hogollongjo","fmoinacebll","fkngbganmh","jgdblmhlmfij","fkkdjknahamcfb","aieakdokibj","hddlcdiailhd","iajhmg","jenocgo","embdib","dghbmljjogka","bahcggjgmlf","fb","jldkcfom","mfi","kdkke","odhbl","jin","kcjmkggcmnami","kofig","bid","ohnohi","fcbojdgoaoa","dj","ifkbmbod","dhdedohlghk","nmkeakohicfdjf","ahbifnnoaldgbj","egldeibiinoac","iehfhjjjmil","bmeimi","ombngooicknel","lfdkngobmik","ifjcjkfnmgjcnmi","fmf","aoeaa","an","ffgddcjblehhggo","hijfdcchdilcl","hacbaamkhblnkk","najefebghcbkjfl","hcnnlogjfmmjcma","njgcogemlnohl","ihejh","ej","ofn","ggcklj","omah","hg","obk","giig","cklna","lihaiollfnem","ionlnlhjckf","cfdlijnmgjoebl","dloehimen","acggkacahfhkdne","iecd","gn","odgbnalk","ahfhcd","dghlag","bchfe","dldblmnbifnmlo","cffhbijal","dbddifnojfibha","mhh","cjjol","fed","bhcnf","ciiibbedklnnk","ikniooicmm","ejf","ammeennkcdgbjco","jmhmd","cek","bjbhcmda","kfjmhbf","chjmmnea","ifccifn","naedmco","iohchafbega","kjejfhbco","anlhhhhg"} ;
	std::vector<string> dict = {"a","aa","aaa","aaaa"} ;
	cout << wordBreak ( s , dict )   << endl ;



	

	return 0;

	
}