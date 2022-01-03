#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	ifstream input;
	input.open("input.txt");

	int depth = 0;
	int pos = 0;
	int aim = 0;

	string command;
	while (getline(input, command)) {
		int amount = command.back() - '0';
		if (command.at(0) == 'u') {
			aim -= amount;
		} else if (command.at(0) == 'd') {
			aim += amount;
		} else if (command.at(0) == 'f') {
			pos += amount;
			depth = depth + (aim * amount);
		}
	}

	int result = depth*pos;
	cout << result << endl;

	return 0;
}
