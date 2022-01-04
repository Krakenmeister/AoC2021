#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
		for (int j=10; j<14; j++) {
			if (signals[i][j].length() == 2 || signals[i][j].length() == 3 || signals[i][j].length() == 4 || signals[i][j].length() == 7) {
				total++;
			}
		}
	}

	cout << total << endl;
	return 0;
}
