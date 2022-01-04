#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

vector<string> parseInputLine(string line) {
	vector<string> output;
	int previousSpace = -1;
	for (int i=0; i<line.length(); i++) {
		if (line[i] == ' ') {
			string word = line.substr(previousSpace + 1, i - (previousSpace + 1));
			if (word.find("|") >= word.length()) {
				output.push_back(word);
			}
			previousSpace = i;
		}
	}
	return output;
}

vector<vector<char>> joinStrings (vector<char> set1, vector<char> set2) {
	vector<char> commonCharacters;
	vector<char> set1Unique;
	vector<char> set2Unique;
	for (int i=0; i<set1.size(); i++) {
		bool hasChar = false;
		for (int j=0; j<set2.size(); j++) {
			if (set2[j] == set1[i]) {
				hasChar = true;
				commonCharacters.push_back(set1[i]);
			}
		}
		if (!hasChar) {
			set1Unique.push_back(set1[i]);
		}
	}
	for (int i=0; i<set2.size(); i++) {
		bool hasChar = false;
		for (int j=0; j<set1.size(); j++) {
			if (set1[j] == set2[i]) {
				hasChar = true;
			}
		}
		if (!hasChar) {
			set2Unique.push_back(set2[i]);
		}
	}
	return {commonCharacters, set1Unique, set2Unique};
}

int main() {
	ifstream input;
	input.open("input.txt");

	vector<vector<string>> signals;

	string line;
	while (getline(input, line)) {
		line += " ";
		vector<string> signal = parseInputLine(line);
		signals.push_back(signal);
	}

	int total = 0;

	for (int i=0; i<signals.size(); i++) {
		//top | top-left | top-right | middle | bottom-left | bottom-right | bottom
		char wireMap [7] = {' ', ' ', ' ', ' ', ' ', ' ', ' '};

		//signals of length 1 || signals of length 2 || .... || signals of length 7
		vector<vector<char>> signalMap [7] = {{}, {}, {}, {}, {}, {}, {}};

		for (int j=0; j<10; j++) {
			vector<char> charSet;
			for (int k=0; k<signals[i][j].length(); k++) {
				charSet.push_back(signals[i][j][k]);
			}
			signalMap[signals[i][j].length() - 1].push_back(charSet);
		}

		//top-right, bottom-right = A
		vector<char> setA = signalMap[1][0];

		//top, top-right, bottom-right = B
		vector<char> setB = signalMap[2][0];

		//top-left, top-right, middle, bottom-right = C
		vector<char> setC = signalMap[3][0];

		//top middle bottom = D
		vector<char> setD = joinStrings(joinStrings(signalMap[4][0], signalMap[4][1])[0], signalMap[4][2])[0];

		//top, top-left, bottom-right, bottom = E
		vector<char> setE = joinStrings(joinStrings(signalMap[5][0], signalMap[5][1])[0], signalMap[5][2])[0];

		//top, top-left, top-right, middle, bottom-left, bottom-right, bottom = F
		vector<char> setF = signalMap[6][0];

		//top = B \ A
		wireMap[0] = joinStrings(setA, setB)[2][0];

		//top-left = (C ^ E) \ A
		wireMap[1] = joinStrings(joinStrings(setC, setE)[0], setA)[1][0];

		//top-right = A \ E
		wireMap[2] = joinStrings(setA, setE)[1][0];

		//middle = D \ E
		wireMap[3] = joinStrings(setD, setE)[1][0];

		//bottom-left = (F \ C) \ D
		wireMap[4] = joinStrings(joinStrings(setF, setC)[1], setD)[1][0];

		//bottom-right = A ^ E
		wireMap[5] = joinStrings(setA, setE)[0][0];

		//bottom = (D ^ E) \ B
		wireMap[6] = joinStrings(joinStrings(setD, setE)[0], setB)[1][0];

		vector<char> digit0 = {wireMap[0], wireMap[1], wireMap[2], wireMap[4], wireMap[5], wireMap[6]};
		vector<char> digit1 = {wireMap[2], wireMap[5]};
		vector<char> digit2 = {wireMap[0], wireMap[2], wireMap[3], wireMap[4], wireMap[6]};
		vector<char> digit3 = {wireMap[0], wireMap[2], wireMap[3], wireMap[5], wireMap[6]};
		vector<char> digit4 = {wireMap[1], wireMap[2], wireMap[3], wireMap[5]};
		vector<char> digit5 = {wireMap[0], wireMap[1], wireMap[3], wireMap[5], wireMap[6]};
		vector<char> digit6 = {wireMap[0], wireMap[1], wireMap[3], wireMap[4], wireMap[5], wireMap[6]};
		vector<char> digit7 = {wireMap[0], wireMap[2], wireMap[5]};
		vector<char> digit8 = {wireMap[0], wireMap[1], wireMap[2], wireMap[3], wireMap[4], wireMap[5], wireMap[6]};
		vector<char> digit9 = {wireMap[0], wireMap[1], wireMap[2], wireMap[3], wireMap[5], wireMap[6]};
		vector<vector<char>> digits = {digit0, digit1, digit2, digit3, digit4, digit5, digit6, digit7, digit8, digit9};

		for (int j=10; j<14; j++) {
			vector<char> charSet;
			for (int k=0; k<signals[i][j].length(); k++) {
				charSet.push_back(signals[i][j][k]);
			}
			for (int k=0; k<digits.size(); k++) {
				if ((joinStrings(digits[k], charSet)[0].size() == charSet.size()) && (charSet.size() == digits[k].size())) {
					total  = total + (int) (pow(10, 13 - j) * k);
				}
			}
		}
	}

	cout << total << endl;
	return 0;
}
