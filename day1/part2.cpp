#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream input;
	input.open("input.txt");
	int depth = 0;
	int measurements [3] = {0, 0, 0};
	int measurement;
	int counter = -3;
	while (input >> measurement) {
		for (int i=0; i<2; i++) {
			measurements[i] = measurements[i+1];
		}
		measurements[2] = measurement;

		int currentDepth = 0;
		for (int i=0; i<3; i++) {
			currentDepth += measurements[i];
		}

		if (currentDepth > depth) {
			counter++;
		}
		depth = currentDepth;
	}

	cout << counter << endl;
	return 0;
}
