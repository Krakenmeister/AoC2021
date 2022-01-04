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

	int totalSyntaxError = 0;
	vector<int> stack;
	map<char, int> charMap = {{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}, {')', -1}, {']', -2}, {'}', -3}, {'>', -4}};
	vector<int> errorMap = {3, 57, 1197, 25137};

	string line;
	while (getline(input, line)) {
		for (int i=0; i<line.length(); i++) {
			if (charMap[line[i]] > 0) {
				stack.push_back(charMap[line[i]]);
			} else {
				if ((stack[stack.size() - 1] * -1) == charMap[line[i]]) {
					stack.pop_back();
				} else {
					totalSyntaxError += errorMap[(-1 * charMap[line[i]]) - 1];
					break;
				}
			}
		}
		stack.clear();
	}

	cout << totalSyntaxError << endl;
	return 0;
}
