#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
	ifstream input;
	input.open("input.txt");

	vector<int> stack;
	map<char, int> charMap = {{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}, {')', -1}, {']', -2}, {'}', -3}, {'>', -4}};
	vector<int> errorMap = {3, 57, 1197, 25137};
	vector<long> syntaxErrors;

	string line;
	while (getline(input, line)) {
		long syntaxError = 0L;
		bool corrupted = false;
		for (int i=0; i<line.length(); i++) {
			if (charMap[line[i]] > 0) {
				stack.push_back(charMap[line[i]]);
			} else {
				if ((stack[stack.size() - 1] * -1) == charMap[line[i]]) {
					stack.pop_back();
				} else {
					corrupted = true;
					break;
				}
			}
		}
		if (corrupted) {
			stack.clear();
			continue;
		}
		while (stack.size() > 0) {
			syntaxError *= 5;
			syntaxError += stack[stack.size() - 1];
			stack.pop_back();
		}
		syntaxErrors.push_back(syntaxError);
		stack.clear();
	}

	sort(syntaxErrors.begin(), syntaxErrors.begin() + syntaxErrors.size());

	cout << syntaxErrors[(syntaxErrors.size() - 1) / 2] << endl;
	return 0;
}
