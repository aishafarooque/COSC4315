#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iterator>
#include <algorithm>
#include <bits/stdc++.h> 
#include <string>
using namespace std;

string identifyVariableType(string value);
string evaluateExpression(string s);


struct variables {
	string name;
	string type;		// int, bool, str, etc.
};

struct functions {
	string functionName;
	vector<variables> functionVariables; 
	string returnValue;
};

vector<variables> variableVector;
vector<functions> functionsVector;

string get_str_between_two_str(const std::string &s,
	const std::string &start_delim,
	const std::string &stop_delim) {
	/*Code credit to: https://stackoverflow.com/questions/18800796/
	c-get-string-between-two-delimiter-string/18800868*/
	unsigned first_delim_pos = s.find(start_delim);
	unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
	unsigned last_delim_pos = s.find(stop_delim);
	
	return s.substr(end_pos_of_first_delim,
		last_delim_pos - end_pos_of_first_delim);
}

bool isNumber(const std::string& s) {
  // Checks if string is a number or not
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

int findPreexisitingVariable(string key) {
	vector<variables>::iterator it;
	int counter = 0;
	for (it = variableVector.begin(); it != variableVector.end(); it++) {
		if (variableVector.at(counter).name == key) {
			return counter;
		}
		counter++;
	}
	return -1;
}

bool isExpression(string s) {
	if ((s.find("+") != string::npos) || (s.find("-")!= string::npos) 
		|| (s.find("*") != string::npos) || (s.find("/") != string::npos )) {
		return true;
}
return false;
}


string identifyVariableType(string value) {
/*	if (isExpression(value)) {
		evaluateExpression(value);
	} else */if (value.front() == '[' && value.back() == ']') {
	return "list";
} else if (value.find("\"") != string::npos) {
		// Variable is a string
	return "str";
} else if (value.find(">") != string::npos || value.find("<") != string::npos) {
	return "bool";
} else if (isNumber(value)) {
	return "int";
} else if (value == "true" || value == "false") {
	return "bool";
}  else {
		return "undefined"; // Else store as string
	}
}

void pop_all(vector<string> &vec) {
	while (vec.size() != 1) vec.pop_back();
}

void verifyTwoTypes(vector<string> &vars_type) {
	
	if (vars_type.size() < 3) {
		cout << "Insufficient elements" << endl;
		vars_type.insert(vars_type.begin(), "undefined");
		return;
	}

	string f = vars_type[0];
	string op = vars_type[1];
	string s = vars_type[2];
	
	if ((f == "int" && s == "str") || (f == "str" && s == "int")) {
		vars_type.insert(vars_type.begin(), "undefined");
		pop_all(vars_type);
	} else if (f == "str" && s == "str" && op == "*") {		//we cannot multiply strings
		vars_type.insert(vars_type.begin(), "undefined");
		pop_all(vars_type);
	} else if (f == "undefined" || s == "undefined") {
		vars_type.insert(vars_type.begin(), "undefined");
		pop_all(vars_type);
	} else if (f == "list" && s != "list") {
		vars_type.insert(vars_type.begin(), "undefined");
		pop_all(vars_type);
	} else if (f == "list" && s == "list" && op != "+") {		//we cannot multiply strings
		vars_type.insert(vars_type.begin(), "undefined");
		pop_all(vars_type);
	} else if (f == s) {
		vars_type.erase (vars_type.begin(),vars_type.begin()+3);		//remove f, s and op
		vars_type.insert(vars_type.begin(), f);							//insert f
	} 
}

string evaluateExpression(string s) {
	s += ".";		//set delimiter
	vector<string> vars;
	vector<string> vars_type;
	char arr[s.length()+1];
	string variableName = "";

	strcpy(arr, s.c_str());

	for (int i = 0; i < s.length(); i++) {
		if (arr[i] != '+' && arr[i] != '*' && arr[i] != '-' && arr[i] != '/' && arr[i] != '.') {
			variableName += arr[i];
		} else {

			if (variableName == "") {
				cout << "Variable name not found!";
				vars_type.insert(vars_type.begin(), "undefined");
				pop_all(vars_type);
			}

			// cout << "Variable Name is " << variableName << endl;
			vars.push_back(variableName);						//push variable name into vars

			int findVariable = findPreexisitingVariable(variableName);	//see if variable name already exists
			if (findVariable != -1) {
				vars_type.push_back(variableVector[findVariable].type);	//get preexisting var type
//				cout << "Variable already exists! " << variableName << " is " << variableVector[findVariable].type << endl;
			} else {
				vars_type.push_back(identifyVariableType(variableName));  //push variable type
				// cout << "Variable " << variableName << " is pushed! The type is " << identifyVariableType(variableName) << endl;
			}
			
			if (arr[i] != '.') {
				vars.push_back(string(1, arr[i]));	//push operator
				vars_type.push_back(string(1, arr[i]));
			}
			
			variableName = "";
		}
	}

	while (vars_type.size() != 1)  {
		verifyTwoTypes(vars_type);
	}

	return vars_type[0];
}



bool compareAlphabetically(const variables& a, const variables& b) {
	return a.name < b.name;
}

void printVector() {
	sort(variableVector.begin(), variableVector.end(), compareAlphabetically);
	for (int i = 0; i < variableVector.size(); ++i) {
		cout << variableVector[i].name << ": " << variableVector[i].type << endl;
	}
}

void removeComments(string &s) {
/*Find and remove comments from .py file*/
	char char_array[s.size() + 1];
	strcpy(char_array, s.c_str());

	size_t findComment = s.find('#');
	size_t findNewLine = s.find('\n');
	size_t findTabs = s.find('\t');
	if (findComment != string::npos) {
		s = "";
	// Comment was found
		for (int i = 0; i < findComment; i++) {
			if (char_array[i] != ' ') 		// We don't want to include spaces
				s += char_array[i];
		}	
	}	
}

void removeNewLinesAndTabs(string &s) {
	s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
}

int main(int argc, char const *argv[]) {
	string fileName = get_str_between_two_str(argv[1], "file=", "");
	ifstream inFS(fileName.c_str());
	string line, identifiedType;
	variables v;
	functions f;

	if (!inFS.is_open()) { cout << "File could not be opened"; }

	while (getline(inFS, line)) {
		
//		cout << line << endl;
		
		/*Ignore if-else statements*/
		if (line.find("if ") != string::npos || line.find("else") != string::npos || line.find("elif") != string::npos) {
			continue;
		}
		/*Ignore new lines*/
		if (line == "\n" || line == "\t") {
			continue;
		}
		
//		if (line.find("def") != string::npos) {
//			while (line != "") {		// until we reach end of function definition
//				f.functionName = get_str_between_two_str(line, "def ", "(");
//				while (line.find("return") != string::npos) { //until we reach return statement
//					
//				}
//					
//			}
//			
//			cout << "Inside the function vector" << endl;
//			for (int i = 0; i < functions.size(); i++) {
//				cout << functions[i] << endl;
//			}
//		}
//
		/*Clean the line*/
		removeComments(line);
		removeNewLinesAndTabs(line);

		string variableName = get_str_between_two_str(line, "", "=");
		if (variableName == "") continue;

		string value = get_str_between_two_str(line, "=", "\n");

		if (isExpression(line)) {
			identifiedType = evaluateExpression(value);		// return type
			v = {variableName, identifiedType};								// make new v object
			variableVector.push_back(v);								// push into the vector 
		} else {
			int findVariable = findPreexisitingVariable(variableName);		//returns counter of var
			identifiedType = identifyVariableType(value);

			if (findVariable != -1) {		// variable is found, index is returned
				variableVector[findVariable].type = identifiedType;  // Overwrite preexisting variable
			} else {
				v = {variableName, identifiedType};			// Otherwise push new variable into the vector
				variableVector.push_back(v);
			}
		}
	}
	printVector();
	return 0;
}

/*To run this file:
clear
g++ -std=c++11 gettype.cpp -o gettype
./gettype file="tc5.py"

*/