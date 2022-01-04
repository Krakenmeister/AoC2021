#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> parseInputLine(string line) {
	vector<int> output = {9};
	for (int i=0; i<line.length(); i++) {
		output.push_back(line[i] - '0');
	}
	output.push_back(9);
	return output;
}

int main() {
	ifstream input;
	input.open("input.txt");

	vector<vector<int>> heightmap;

	int numLines = 0;
	string line;
	while (getline(input, line)) {
		if(numLines == 0) {
			vector<int> heights;
			for (int i=0; i<line.length()+2; i++) {
				heights.push_back(9);
			}
			heightmap.push_back(heights);
		}
		vector<int> heights = parseInputLine(line);
		heightmap.push_back(heights);
		numLines++;
	}
	vector<int> heights;
	for (int i=0; i<heightmap[0].size(); i++) {
		heights.push_back(9);
	}
	heightmap.push_back(heights);

	vector<vector<vector<int>>> basins;
	vector<int> basinSizes;

	for (int i=0; i<heightmap.size(); i++) {
		for (int j=0; j<heightmap[i].size(); j++) {
			if (heightmap[i][j] < 9) {
				if ((heightmap[i][j] < heightmap[i-1][j]) && (heightmap[i][j] < heightmap[i+1][j]) && (heightmap[i][j] < heightmap[i][j-1]) && (heightmap[i][j] < heightmap[i][j+1])) {
					basins.push_back({{i, j}});
				}
			}
		}
	}

	while (basins.size() > 0) {
		for (int i=0; i<basins.size(); i++) {
			int numPointsAdded = 0;
			for (int j=0; j<basins[i].size(); j++) {
				int basinX = basins[i][j][0];
				int basinY = basins[i][j][1];
				if ((heightmap[basinX][basinY] < heightmap[basinX - 1][basinY]) && (heightmap[basinX - 1][basinY] != 9)) {
					vector<int> newPoint = {basinX - 1, basinY};
					if (find(basins[i].begin(), basins[i].end(), newPoint) == basins[i].end()) {
						basins[i].push_back(newPoint);
						numPointsAdded++;
					}
				}
				if ((heightmap[basinX][basinY] < heightmap[basinX + 1][basinY]) && (heightmap[basinX + 1][basinY] != 9)) {
					vector<int> newPoint = {basinX + 1, basinY};
					if (find(basins[i].begin(), basins[i].end(), newPoint) == basins[i].end()) {
						basins[i].push_back(newPoint);
						numPointsAdded++;
					}
				}
				if ((heightmap[basinX][basinY] < heightmap[basinX][basinY - 1]) && (heightmap[basinX][basinY - 1] != 9)) {
					vector<int> newPoint = {basinX, basinY - 1};
					if (find(basins[i].begin(), basins[i].end(), newPoint) == basins[i].end()) {
						basins[i].push_back(newPoint);
						numPointsAdded++;
					}
				}
				if ((heightmap[basinX][basinY] < heightmap[basinX][basinY + 1]) && (heightmap[basinX][basinY + 1] != 9)) {
					vector<int> newPoint = {basinX, basinY + 1};
					if (find(basins[i].begin(), basins[i].end(), newPoint) == basins[i].end()) {
						basins[i].push_back(newPoint);
						numPointsAdded++;
					}
				}
			}
			if (numPointsAdded == 0) {
				basinSizes.push_back(basins[i].size());
				basins.erase(basins.begin() + i);
				i--;
			}
		}
	}

	sort(basinSizes.begin(), basinSizes.begin() + basinSizes.size());

	cout << (basinSizes[basinSizes.size() - 1] * basinSizes[basinSizes.size() - 2] * basinSizes[basinSizes.size() - 3]) << endl;
	return 0;
}
