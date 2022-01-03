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

long numFish (int numDays) {
	long total = 1L;
	while (numDays > 9) {
		total += numFish(numDays - 9);
		numDays -= 7;
	}
	return total;
}

int main() {
	ifstream input;
	input.open("input.txt");

	vector<int> school;

	string line;
	while (getline(input, line)) {
		school = parseInputLine(line);
	}

	const int numDays = 256;

	vector<long> fishPop;
	for (int i=1; i<6; i++) {
		fishPop.push_back(numFish((9 - i) + numDays));
	}

	long totalFish = 0L;
	for (int i=0; i<school.size(); i++) {
		totalFish += fishPop[school[i] - 1];
	}

	cout << totalFish << endl;
	return 0;
}
