#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	ifstream input;
	input.open("input.txt");

	int depth = 0;
	int pos = 0;

	string command;
	while (getline(input, command)) {
		int amount = command.back() - '0';
		if (command.at(0) == 'u') {
			depth -= amount;
		} else if (command.at(0) == 'd') {
			depth += amount;
		} else if (command.at(0) == 'f') {
			pos += amount;
		}
	}

	int result = depth*pos;
	cout << result << endl;

	return 0;
}
