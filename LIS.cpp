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

#define EPS 1e-6

using namespace std ;

int getLIS(vector<int> & v) {
    int maxL = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        int lastVal = v[i], lastIndex = i, LCnt = 1;
        for (size_t j = i + 1; j < v.size(); ++j) {
            if (v[j] > lastVal and j > lastIndex) {
                lastIndex = j;
                lastVal = v[j];
                LCnt++;
            }
        }
        lastVal = v[i]; lastIndex = i;
        for (int j = i - 1; j >= 0; --j) {
            if (lastVal > v[j] and lastIndex > j) {
                lastIndex = j;
                lastVal = v[j];
                LCnt++;
            }
        }
        maxL = max(maxL, LCnt);
    }
    return maxL;
}

vector<int> removeDupicates(vector<int> & b) {
    vector<int> res; if (b.size() == 0) return res;
    res.push_back(b[0]);
    size_t oI = 0, offI = 1;
    for (; offI < b.size(); ++offI) {
        if (b[oI] != b[offI]) {
            oI = offI; res.push_back(b[oI]);
        }
    }
    return res;
}

class segmentTree { 

    public :
        segmentTree () = default ;
        virtual ~segmentTree() {
            delete [] st ;
        }

        int RMQUtil( int start, int end, int qstart, int qend, int i) {
            // If segment of this node is a part of given range, then return val   
            if (qstart <= start and qend >= end) return st[i];
            // If segment of this node is outside the given range  
            if (end < qstart or start > qend) return 0;
            // If a part of this segment overlaps with the given range  
            int mid = start + (end - start) / 2;
            return max(RMQUtil(start, mid, qstart, qend, i * 2 + 1),
                RMQUtil( mid + 1, end, qstart, qend, i * 2 + 2));
        }
        // Return min/max of elements in range 
        // from index start to end   
        int RMQ( int n, int start, int end) {
            if (start < 0 || end > n - 1 || start > end) {
                cout << "Invalid input for range query.";
                return -1;
            }
            return RMQUtil(0, n - 1, start, end, 0);
        }
        int constructSTUtil(vector<int> & arr, int start, int end, int i) {
            //one element  
            if (start == end) {  //leaf
                st[i] = 0; mapV.push_back(i); return st[i];
            }
            int mid = start + (end - start) / 2;
            st[i] = max( constructSTUtil(arr, start, mid, i * 2 + 1),
                         constructSTUtil(arr, mid + 1, end, i * 2 + 2));
            return st[i];
        }
        void constructST(vector<int> & arr, int n) {
            int x = (int)(ceil(log2(n))); max_size = 2 * (int)pow(2, x) - 1;
            st = new int[max_size]; memset(st, 0, sizeof(int) * max_size);
            constructSTUtil(arr, 0, n - 1, 0);
        }
        void updateLeaf( int i, int val) {
            st[i] = val; int tempVal = st[i]; i = (i - 1) >> 1;
            while (i > 0) {
                if (tempVal > st[i]) st[i] = tempVal ;
                tempVal = st[i]; i = (i - 1) >> 1;
            }
            if (tempVal > st[0]) st[0] = tempVal;
        }
    public :
        int * st ; vector<int> mapV ; int max_size ;

};

int solveOptLIS(vector<int> & input, segmentTree & segT ) {
    if (input.size() == 0) return 0; if (input.size() == 1) return 1;
    vector<pair<int, size_t>> sortedInput(input.size());
    for (size_t i = 0; i < input.size(); ++i) sortedInput[i] = { input[i], i };
    stable_sort(sortedInput.begin(), sortedInput.end());
    vector<int> tempLISV(input.size());
    tempLISV[sortedInput[0].second] ++; segT.updateLeaf( segT.mapV[sortedInput[0].second], 1);
    size_t currentI = sortedInput[0].second, currentChain = 1;
    int  currentVal = sortedInput[0].first;

    for (size_t i = 1; i < sortedInput.size(); ++i) {
        if (sortedInput[i].second > currentI) { // comes after index
            if (currentI + 1 == sortedInput[i].second and sortedInput[i].first > currentVal) {
                ++currentChain;
                tempLISV[sortedInput[i].second] = currentChain; currentI = sortedInput[i].second; currentVal = sortedInput[i].first;
                segT.updateLeaf( segT.mapV[sortedInput[i].second], currentChain);
            }
            else if (sortedInput[i].first > currentVal) {
                int candidateLength = segT.RMQ( input.size(), currentI + 1, sortedInput[i].second - 1);
                if (candidateLength > tempLISV[currentI]) tempLISV[sortedInput[i].second] = candidateLength + 1; else tempLISV[sortedInput[i].second] = tempLISV[currentI] + 1;
                currentI = sortedInput[i].second; currentVal = sortedInput[i].first; currentChain = tempLISV[currentI];
                segT.updateLeaf( segT.mapV[sortedInput[i].second], currentChain);
            }
            else {
                int candidateLength = segT.RMQ(input.size(), currentI + 1, sortedInput[i].second - 1);
                if (candidateLength >= tempLISV[currentI]) tempLISV[sortedInput[i].second] = candidateLength + 1; else tempLISV[sortedInput[i].second] = tempLISV[currentI];
                currentI = sortedInput[i].second; currentVal = sortedInput[i].first; currentChain = tempLISV[currentI];
                segT.updateLeaf( segT.mapV[sortedInput[i].second], currentChain);
            }
        }
        else { // came before index
            currentVal = sortedInput[i].first;
            if (sortedInput[i].second == 0) {
                currentI = 0; tempLISV[currentI] = 1; currentChain = 1;
                segT.updateLeaf( segT.mapV[sortedInput[i].second], currentChain);
            }
            else {
                int candidateLength = segT.RMQ(input.size(), 0, sortedInput[i].second - 1);
                currentI = sortedInput[i].second; currentChain = candidateLength + 1; tempLISV[sortedInput[i].second] = candidateLength + 1;
                segT.updateLeaf( segT.mapV[sortedInput[i].second], currentChain);
            }
        }
    }
    return segT.st[0];
}

int main() {
    
    vector<int> input = {10,9,2,5,3,4};
    input = removeDupicates(input);
    segmentTree segT ;
    segT.constructST ( input, input.size() ) ;

    for_each(input.begin(), input.end(), [](int & b) { cout << b << " "; }); cout << endl;
    for_each(segT.mapV.begin(), segT.mapV.end(), [](int & b) { cout << b << " "; }); cout << endl;
    cout << "Complex Solution : " << getLIS(input) << endl;
    cout << "Opt solution : " << solveOptLIS(input, segT) << endl;
    
    return 0;
}