#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> parseInputLine(string line) {
	vector<int> output;
	for (int i=0; i<line.length(); i++) {
		output.push_back(line[i] - '0');
	}
	return output;
}

int main() {
	ifstream input;
	input.open("input.txt");

	vector<vector<int>> heightmap;

	string line;
	while (getline(input, line)) {
		vector<int> heights = parseInputLine(line);
		heightmap.push_back(heights);
	}

	int totalRisk = 0;

	for (int i=0; i<heightmap.size(); i++) {
		for (int j=0; j<heightmap[i].size(); j++) {
			if (((i == 0) || (heightmap[i][j] < heightmap[i - 1][j])) && ((i == heightmap.size() - 1) || (heightmap[i][j] < heightmap[i + 1][j])) && ((j == 0) || (heightmap[i][j] < heightmap[i][j - 1])) && ((j == heightmap[i].size() - 1) || (heightmap[i][j] < heightmap[i][j + 1]))) {
				totalRisk = totalRisk + heightmap[i][j] + 1;
			}
		}
	}

	cout << totalRisk << endl;
	return 0;
}
