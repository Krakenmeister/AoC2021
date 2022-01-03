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

	const int numDays = 256;

	vector<long> fishGenerations = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	for (int i=0; i<school.size(); i++) {
		fishGenerations[school[i]]++;
	}

	for (int i=0; i<numDays; i++) {
		long freshFish = fishGenerations[0];
		for (int j=0; j<8; j++) {
			fishGenerations[j] = fishGenerations[j+1];
		}
		fishGenerations[8] = freshFish;
		fishGenerations[6] += freshFish;
	}

	long totalFish = 0;
	for (int i=0; i<9; i++) {
		totalFish += fishGenerations[i];
	}

	cout << totalFish << endl;
	return 0;
}
