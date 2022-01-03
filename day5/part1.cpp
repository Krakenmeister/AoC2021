#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <bits/stdc++.h>

using namespace std;

struct hash_pair {
	template <class T1, class T2>
	size_t operator () (const pair<T1, T2> &p) const {
		auto hash1 = hash<T1>()(p.first);
		auto hash2 = hash<T2>()(p.second);
		return hash1 ^ hash2;
	}
};

vector<vector<int>> parseInputLine(string line) {
	vector<int> markers;
	for (int i=0; i<line.length(); i++) {
		if (line[i] == ',' || line[i] == ' ') {
			markers.push_back(i);
		}
	}
	return {{stoi(line.substr(0, markers[0])), stoi(line.substr(markers[0] + 1, markers[1] - markers[0] - 1))}, {stoi(line.substr(markers[2] + 1, markers[3] - markers[2] - 1)), stoi(line.substr(markers[3] + 1))}};
}

int main() {
	ifstream input;
	input.open("input.txt");

	unordered_map<pair<int, int>, int, hash_pair> pointCount;

	string line;
	while (getline(input, line)) {
		vector<vector<int>> coordinates = parseInputLine(line);
		int coordMatch = -1;
		if (coordinates[0][0] == coordinates[1][0]) {
			const int start = min(coordinates[0][1], coordinates[1][1]);
			const int end = max(coordinates[0][1], coordinates[1][1]);
			for (int i = start; i <= end; i++) {
				const pair<int, int> currentPoint = {coordinates[0][0], i};
				if (pointCount.find(currentPoint) == pointCount.end()) {
					pointCount[currentPoint] = 1;
				} else {
					pointCount[currentPoint]++;
				}
			}
		} else if (coordinates[0][1] == coordinates[1][1]) {
			const int start = min(coordinates[0][0], coordinates[1][0]);
			const int end = max(coordinates[0][0], coordinates[1][0]);
			for (int i = start; i <= end; i++) {
				const pair<int, int> currentPoint = {i, coordinates[0][1]};
				if (pointCount.find(currentPoint) == pointCount.end()) {
					pointCount[currentPoint] = 1;
				} else {
					pointCount[currentPoint]++;
				}
			}
		}
	}

	int totalPoints = 0;
	for (auto i = pointCount.begin(); i != pointCount.end(); i++) {
		if (i->second > 1) {
			totalPoints++;
		}
	}

	cout << totalPoints << endl;
	return 0;
}
