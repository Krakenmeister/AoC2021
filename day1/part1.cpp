#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream input;
	input.open("input.txt");
	int depth = 0;
	int measurement;
	int counter = -1;
	while (input >> measurement) {
		if (measurement > depth) {
			counter++;
		}
		depth = measurement;
	}

	cout << counter << endl;
	return 0;
}
