#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void flashIndex (vector<vector<int>> &energies, int i, int j, int &flashCount) {
	for (int a = i-1; a <= i+1; a++) {
		for (int b = j-1; b <= j+1; b++) {
			if (((a != i) || (b != j)) && (a >= 0) && (b >= 0) && (a < energies.size()) && (b < energies[0].size())) {
				if (energies[a][b] < 10 && energies[a][b] > 0) {
					energies[a][b]++;
					if (energies[a][b] == 10) {
						flashCount++;
						energies[a][b] = 0;
						flashIndex(energies, a, b, flashCount);
					}
				}
			}
		}
	}
}

int main() {
	ifstream input;
	input.open("input.txt");

	vector<vector<int>> energies;

	string line;
	while (getline(input, line)) {
		vector<int> energyRow;
		for (int i=0; i<line.length(); i++) {
			energyRow.push_back(line[i] - '0');
		}
		energies.push_back(energyRow);
	}

	int flashCount = 0;
	const int numSteps = 100;

	for (int steps=0; steps >= 0; steps++) {
		//Increase energy level
		for (int i=0; i<energies.size(); i++) {
			for (int j=0; j<energies[i].size(); j++) {
				energies[i][j]++;
			}
		}
		//Process flash propagation
		for (int i=0; i<energies.size(); i++) {
			for (int j=0; j<energies[i].size(); j++) {
				if (energies[i][j] == 10) {
					flashCount++;
					energies[i][j] = 0;
					flashIndex(energies, i, j, flashCount);
				}
			}
		}

		//Check if synchronized
		bool synchronized = true;
		for (int i=0; i<energies.size(); i++) {
			for (int j=0; j<energies[i].size(); j++) {
				if (energies[i][j] != 0) {
					synchronized = false;
				}
			}
		}
		if (synchronized) {
			cout << (steps + 1) << endl;
			steps = -100;
		}
	}

	return 0;
}
