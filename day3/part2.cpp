#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <bitset>
#include <vector>

using namespace std;

int findRating(vector<vector<bool>> diagnostics, bool ratingType) {
	for (int i=0; i<12; i++) {
		int bitcomparison = 0;
		for (int j=0; j<diagnostics.size(); j++) {
			if (diagnostics.size() == 1) {
				i = 12;
				break;
			}
			if (diagnostics[j][i]) {
				bitcomparison++;
			} else {
				bitcomparison--;
			}
		}
		if (i == 12) {
			break;
		}
		bool patternMatch;
		if (bitcomparison >= 0) {
			patternMatch = true;
		} else {
			patternMatch = false;
		}
		if (ratingType) {
			patternMatch = !patternMatch;
		}
		for (int j=0; j<diagnostics.size(); j++) {
			if (diagnostics[j][i] != patternMatch) {
				diagnostics.erase(diagnostics.begin() + j);
				j--;
			}
		}
	}

	int rating = 0;
	for (int i=0; i<12; i++) {
		if (diagnostics[0][i]) {
			rating += (int) pow(2, 11 - i);
		}
        }
	return rating;
}

int main() {
	ifstream input;
	input.open("input.txt");

	vector<vector<bool>> diagnostics;

	string line;
	while (getline(input, line)) {
		vector<bool> diagnostic;
		for (int i=0; i<line.length(); i++) {
			if (line[i] == '1') {
				diagnostic.push_back(true);
			} else {
				diagnostic.push_back(false);
			}
		}
		diagnostics.push_back(diagnostic);
	}

	int oxygen_rating = findRating(diagnostics, false);
	int co2_rating = findRating(diagnostics, true);

	int result = oxygen_rating * co2_rating;
	cout << result << endl;

	return 0;
}
