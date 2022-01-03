#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> parseInputLine(string line) {
	vector<int> output;
	int previousComma = -1;
	for (int i=0; i<line.length(); i++) {
		if (line[i] == ',') {
			output.push_back(stoi(line.substr(previousComma + 1, i)));
			previousComma = i;
		}
	}
	return output;
}

int main() {
	ifstream input;
	input.open("input.txt");

	vector<int> crabs;

	string line;
	while (getline(input, line)) {
		crabs = parseInputLine(line);
	}

	int minPos = crabs[0];
	int maxPos = crabs[0];
	for (int i=0; i<crabs.size(); i++) {
		if (crabs[i] < minPos) {
			minPos = crabs[i];
		} else if (crabs[i] > maxPos) {
			maxPos = crabs[i];
		}
	}

	int minCost = -1;
	for (int i=minPos; i<=maxPos; i++) {
		int cost = 0;
		for (int j=0; j<crabs.size(); j++) {
			int distance = (int) abs(i - crabs[j]);
			cost += (distance * (distance + 1)) / 2;
		}
		if (cost < minCost || minCost == -1) {
			minCost = cost;
		}
	}

	cout << minCost << endl;
	return 0;
}
