#include <iostream>
#include <map>
#include <string>
using namespace std;

int consumeToken(const string _s, int & _index) {
	string intToken = "";
	while (_index < _s.length() && _s[_index] >= '0' && _s[_index] <= '9') {
		intToken += _s[_index];
		_index++;
	}
	return stoi(intToken);
}

int calcRec(string _s, int _index) {
	if (_index >= _s.length()) return 0;
	if (_s[_index] >= '0' && _s[_index] <= '9') {
		int operand = consumeToken(_s, _index);
		int sum = operand;
		while (_index < _s.length() && _s[_index] == '*') {
			_index++;
			operand = consumeToken(_s, _index);
			sum *= operand;
		}
		_index++;
		return sum + calcRec(_s, _index);
	}

}

int main() {
	string input = "20+3+4+4+5";

	cout << calcRec(input, 0) << endl;

	return 0;
}