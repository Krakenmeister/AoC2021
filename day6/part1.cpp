#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <bits/stdc++.h>

using namespace std;

vector<int> parseInputLine(string line) {
	vector<int> output;
	for (int i=0; i<line.length(); i++) {
		if (line[i] != ',') {
			output.push_back(line[i] - '0');
		}
	}
	return output;
}

int main() {
	ifstream input;
	input.open("input.txt");

	vector<int> school;

	string line;
	while (getline(input, line)) {
		school = parseInputLine(line);
	}

	const int numDays = 80;
	for (int i=0; i<numDays; i++) {
		const int size = school.size();
		for (int j=0; j<size; j++) {
			if (school[j] == 0) {
				school[j] = 6;
				school.push_back(8);
			} else {
				school[j]--;
			}
		}
/*		for (int j=0; j<school.size(); j++) {
			cout << school[j] << " ";
		}
		cout << endl;*/
	}

	cout << school.size() << endl;
	return 0;
}
