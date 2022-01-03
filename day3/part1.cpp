#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <bitset>

using namespace std;

int main() {
	ifstream input;
	input.open("input.txt");

	int bitcomparison[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	string diagnostic;
	while (getline(input, diagnostic)) {
		for (int i=0; i<12; i++) {
			if (diagnostic[i] == '1') {
				bitcomparison[i]++;
			} else {
				bitcomparison[i]--;
			}
		}
	}

	int gamma_rate = 0;
	int epsilon_rate = 0;

	for (int i=0; i<12; i++) {
		if (bitcomparison[i] >= 0) {
			gamma_rate += (int) pow(2, 11 - i);
		} else {
			epsilon_rate += (int) pow(2, 11 - i);
		}
	}

/*	for (int i=0; i<12; i++) {
		cout << bitcomparison[i] << endl;
	}

	cout << bitset<12>(gamma_rate) << endl;
	cout << bitset<12>(epsilon_rate) << endl;*/

	int result = gamma_rate * epsilon_rate;
	cout << result << endl;

	return 0;
}
