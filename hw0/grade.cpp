#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[]) {
	ifstream generated_output, answer;
	int lines_in_output, lines_in_answer;
	string str;


	generated_output.open("tc1.txt");
	answer.open("ans1.out");


	if (!generated_output.is_open()) {
		cout << "Output file cannot be opened\n";
	}

	if (!answer.is_open()) {
		cout << "Answer file cannot be opened\n";	
	}

	while (getline(generated_output, str)) {
		lines_in_output++;
	}
	return 0;
}
