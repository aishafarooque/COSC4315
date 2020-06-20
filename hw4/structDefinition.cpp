#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>


/*mypython.cpp*/
#include <algorithm>

/*helper.cpp*/
#include <bits/stdc++.h>
#include <cstring>

using namespace std;

struct variables {
	string name;
    string type; // int, bool, str, etc.
    string value;
};

struct functions {
	string functionName;
	vector<variables> functionVariables;
	vector<string> parametersString;
	vector<string> functionBody;
	string returnValue;
	int numberOfParameters;
	bool containsIfElse;
};

vector<variables> variableVector;
vector<functions> functionsVector;
vector<string> consoleOutputs;
bool programHasFunctions;