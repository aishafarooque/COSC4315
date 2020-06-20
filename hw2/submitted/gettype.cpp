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
    string type; // int, bool, str, etc.
};

struct functions {
    string functionName;
    vector<variables> functionVariables;
    vector<string> paramtersString;
    string returnValue;
    int numberOfParameters;
};

vector<variables> variableVector;
vector<functions> functionsVector;

string get_str_between_two_str(const std::string& s,
    const std::string& start_delim,
    const std::string& stop_delim)
{
    /*Code credit to: https://stackoverflow.com/questions/18800796/
	c-get-string-between-two-delimiter-string/18800868*/
    unsigned first_delim_pos = s.find(start_delim);
    unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
    unsigned last_delim_pos = s.find(stop_delim);

    return s.substr(end_pos_of_first_delim,
        last_delim_pos - end_pos_of_first_delim);
}

bool isNumber(const std::string& s)
{
    // Checks if string is a number or not
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

int findPreexisitingVariable(vector<variables> v, string key)
{
	/*Find if variable name already exists in vector v*/
    vector<variables>::iterator it;
    int counter = 0;
    for (it = v.begin(); it != v.end(); it++) {
        if (v.at(counter).name == key) {
            return counter;
        }
        counter++;
    }
    return -1;
}

bool isExpression(string s)
{
    if ((s.find("+") != string::npos) || (s.find("-") != string::npos)
        || (s.find("*") != string::npos) || (s.find("/") != string::npos)) {
        return true;
    }
    return false;
}

string identifyVariableType(vector<variables> v, string value)
{
    int findVariable = findPreexisitingVariable(v, value);
    if (findVariable != -1) {
        return v.at(findVariable).type;
    }
    else if (value.front() == '[' && value.back() == ']') {
        return "list";
    }
    else if (value.find("\"") != string::npos) {
        // Variable is a string
        return "str";
    }
    else if (value.find(">") != string::npos || value.find("<") != string::npos) {
        return "bool";
    }
    else if (isNumber(value)) {
        return "int";
    }
    else if (value == "true" || value == "false") {
        return "bool";
    }
    else {
        return "undefined"; // Else store as string
    }
}

void pop_all(vector<string>& vec)
{
    while (vec.size() != 1)
        vec.pop_back();
}

void verifyTwoTypes(vector<string>& vars_type)
{

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
    }
    else if (f == "str" && s == "str" && op == "*") { //we cannot multiply strings
        vars_type.insert(vars_type.begin(), "undefined");
        pop_all(vars_type);
    }
    else if (f == "int" && s == "str" && op == "*") {
    	vars_type.insert(vars_type.begin(), "undefined");
    	pop_all(vars_type);
    }
    else if (f == "undefined" || s == "undefined") {
        vars_type.insert(vars_type.begin(), "undefined");
        pop_all(vars_type);
    }
    else if (f == "list" && s != "list") {
        vars_type.insert(vars_type.begin(), "undefined");
        pop_all(vars_type);
    }
    else if (f == "list" && s == "list" && op != "+") { //we cannot multiply strings
        vars_type.insert(vars_type.begin(), "undefined");
        pop_all(vars_type);
    }
    else if (f == s) {
        vars_type.erase(vars_type.begin(), vars_type.begin() + 3); //remove f, s and op
        vars_type.insert(vars_type.begin(), f); //insert f
    }
}

string evaluateExpression(vector<variables> v, string s)
{
    s += "."; //set delimiter at end of string
    vector<string> vars;
    vector<string> vars_type;
    char arr[s.length() + 1];
    string variableName = "";

    strcpy(arr, s.c_str());

    for (int i = 0; i < s.length(); i++) {
        if (arr[i] != '+' && arr[i] != '*' && arr[i] != '-' && arr[i] != '/' && arr[i] != '.') {
            variableName += arr[i];
        }
        else {

            if (variableName == "") {
                // cout << "Variable name not found!";
                vars_type.insert(vars_type.begin(), "undefined");
                pop_all(vars_type); 
            }

            // cout << "Variable Name is " << variableName << endl;
            vars.push_back(variableName); //push variable name into vars

            int findVariable = findPreexisitingVariable(v, variableName); //see if variable name already exists
            // cout << "findVariable returned " << findVariable << endl;

            if (findVariable != -1) {
                vars_type.push_back(v.at(findVariable).type); //get preexisting var type
                // cout << "Variable already exists! " << variableName << " is " << v.at(findVariable).type << endl;
            }
            else {
                vars_type.push_back(identifyVariableType(v, variableName)); //push variable type
                // cout << "Variable " << variableName << " is pushed! The type is " << identifyVariableType(v, variableName) << endl;
            }

            if (arr[i] != '.') {
            	// cout << "Stopping at delimiter" << endl;
                vars.push_back(string(1, arr[i])); //push operator
                vars_type.push_back(string(1, arr[i]));
            }

            variableName = "";
        }
    }

    while (vars_type.size() != 1) {
        verifyTwoTypes(vars_type);
    }

    return vars_type[0];
}

bool compareAlphabetically(const variables& a, const variables& b)
{
    return a.name < b.name;
}

void printVector()
{
    sort(variableVector.begin(), variableVector.end(), compareAlphabetically);
    for (int i = 0; i < variableVector.size(); ++i) {
        cout << variableVector[i].name << ": " << variableVector[i].type << endl;
    }
}

void removeComments(string& s)
{
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
            if (char_array[i] != ' ') // We don't want to include spaces
                s += char_array[i];
        }
    }
}

void removeNewLinesAndTabs(string& s)
{
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
}

int findNumberOfParameters(string line)
{
    int count = 0;

    for (int i = 0; i < line.size(); i++)
        if (line[i] == ',')
            count++;

    return count + 1;
}

int findIfFunctionExists(string functionNameToFind)
{
    for (int i = 0; i < functionsVector.size(); i++) {
        if (functionsVector.at(i).functionName == functionNameToFind) {
            return i;
        }
    }
    return -1;
}

vector<variables> retrieveParameters(int functionPosition, string s) {
	string parametersName, parametersType;
	s += ")";										//set delimiter
	char char_array[s.size() + 1];
    strcpy(char_array, s.c_str());
    vector<variables> parameters;

    for (int i = 0; i < s.length(); i++) {
    	if (char_array[i] != ',' && char_array[i] != ')') {
    		parametersName += char_array[i];
    	} else {
    		parametersType = identifyVariableType(functionsVector.at(functionPosition).functionVariables, parametersName);
    		parameters.push_back({parametersName, parametersType});

    		// cout << "parametersName: " << parametersName << ", parametersType: " << parametersType << endl;

    		parametersName = parametersType = "";
    	}
    }
    return parameters;
}

string getTypeOfVariable(vector<variables> v, string key) {
	for (int i = 0; i < v.size(); i++) {
		if (v.at(i).name == key) 
			return v.at(i).type;
	}
	return ("could not find specified name: " + key);
}

string evaluateFunction(vector<functions> v, int functionPosition, string line/*, string functionReturn*/) {
	string identifiedType;
	functions f = v.at(functionPosition);
	vector<variables> parametersFromFunctionCall;
	parametersFromFunctionCall.push_back({".","."});									//set delimiter

	if (line.length() != 0) {	
		parametersFromFunctionCall = retrieveParameters(functionPosition, line);		//"2",3
		for (int i = 0; i < parametersFromFunctionCall.size(); i++) {
			parametersFromFunctionCall.at(i).name = f.paramtersString.at(i);			//a:str, b:int
		}
		while (parametersFromFunctionCall.size() >= 1) {
			if (parametersFromFunctionCall.front().name == ".") break;	

			// cout << "front of parametersFromFunctionCall " << parametersFromFunctionCall.front().name << endl;
			if (!isExpression(f.returnValue)) {
				/*See if the var has been over written*/
				if (findPreexisitingVariable(f.functionVariables, f.returnValue) != -1) { 	//find overwritten vars
					// cout << f.returnValue << " already exists!" << endl;
					identifiedType = identifyVariableType(f.functionVariables, f.returnValue);
				} /*Else pull type from parameter*/
				else {
					identifiedType = getTypeOfVariable(parametersFromFunctionCall, f.returnValue);
				}
			} else {
				// cout << "--evaluateExpression inside evaluateFunction" << endl;
				identifiedType = evaluateExpression(parametersFromFunctionCall, f.returnValue);
				parametersFromFunctionCall.erase(parametersFromFunctionCall.begin());
			}

			// cout << "parametersFromFunctionCall" << endl;
			// for (int i = 0; i < parametersFromFunctionCall.size(); i++) {
			// 	cout << parametersFromFunctionCall.at(i).name << ": " << parametersFromFunctionCall.at(i).type << endl;
			// }

			parametersFromFunctionCall.erase(parametersFromFunctionCall.begin());
		}

	}

	return identifiedType;
}

vector<string> split(string str, string token){
    vector<string>result;
    while(str.size()){
        int index = str.find(token);
        if(index!=string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}


int main(int argc, char const* argv[]) {
    string fileName = get_str_between_two_str(argv[1], "file=", "");
    ifstream inFS(fileName.c_str());
    string line, identifiedType, variableName, value, returnStatement, functionName;
    int functionPosition;
    variables v;
    functions f;

    vector<string> returnStatementsVector;

    if (!inFS.is_open()) {
        cout << "File could not be opened";
    }

    while (getline(inFS, line)) {


        /*Ignore if-else statements*/
        if (line.find("if ") != string::npos || line.find("else") != string::npos || line.find("elif") != string::npos) {
            continue;
        }
        /*Ignore new lines*/
        if (line == "\n" || line == "\t") {
            continue;
        }
        
        // cout << "Line: " << line << endl;

        // if (line.find("def") != string::npos) { //function definition is found
        if (line.substr(0, 4) == "def ") {
            //			cout << "Function found!" << endl;
            f.functionName = get_str_between_two_str(line, "def ", "(");
            //			cout << "Function name is " << functionName << endl;
            f.numberOfParameters = findNumberOfParameters(line);

            //			cout << "The function has " << f.numberOfParameters << " parameters." << endl;

            f.paramtersString = split(get_str_between_two_str(line, "(", ")"), ",");
            // cout << "The function's parameters are " << f.paramtersString.back() << endl;
            getline(inFS, line);

            while (line != "") { //until end of function definition

                if (line.find("return") != string::npos) { //condition to break loop
                	removeNewLinesAndTabs(line);
                    f.returnValue = get_str_between_two_str(line, "return ", "\n");
                    // cout << "The function returns " << f.returnValue << endl;
                    getline(inFS, line);
                    break;
                }
                removeNewLinesAndTabs(line);
                variableName = get_str_between_two_str(line, "", "=");
                value = get_str_between_two_str(line, "=", "\n");

                if (isExpression(value)) {
                	cout << "--evaluateExpression inside main" << endl;
                    identifiedType = evaluateExpression(f.functionVariables, value);
                }
                else {
                    int findVariable = findPreexisitingVariable(f.functionVariables, variableName);
                    if (findVariable != -1) {
                        cout << "Variable found " << endl;
                        identifiedType = f.functionVariables.at(findVariable).type;
                    }
                    else {
                        identifiedType = identifyVariableType(f.functionVariables, value);
                    }
                }

                // cout << "Pushing " << variableName << " of type " << identifiedType << endl;
                v = { variableName, identifiedType };
                f.functionVariables.push_back(v);

                getline(inFS, line);
            }
            
            functionsVector.push_back(f);

            // for (int i = 0; i < f.functionVariables.size(); i++) {
            //     cout << f.functionVariables.at(i).name << ": " << f.functionVariables.at(i).type << endl;
            // }
        }
        /*Clean the line*/
        removeComments(line);
        removeNewLinesAndTabs(line);

        variableName = get_str_between_two_str(line, "", "=");
        if (variableName == "")
            continue;

        value = get_str_between_two_str(line, "=", "\n");

        if (value == "") {
        	variableVector.push_back({variableName, "undefined"});
        } else if (isExpression(line)) {
        	// cout << "--evaluateExpression inside normal variable main" << endl;
            identifiedType = evaluateExpression(variableVector, value); // return type
            v = { variableName, identifiedType }; // make new v object
            variableVector.push_back(v); // push into the vector
        }
        else if (line.find("(") != string::npos) { // line is a calling function
            functionName = get_str_between_two_str(line, "def", "(");
            functionPosition = findIfFunctionExists(functionName);
            if (functionPosition == -1) {			//function does not exist
                identifiedType = "undefined";
            } else if (findNumberOfParameters(line) != functionsVector.at(functionPosition).numberOfParameters) {
            	identifiedType = "undefined";
            } else {
            	string parameters = get_str_between_two_str(value, "(", ")");
            	identifiedType = evaluateFunction(functionsVector, functionPosition, 
            		parameters/*, returnStatementsVector.at(functionPosition)*/);
            }
// 
            v = {variableName, identifiedType};
            variableVector.push_back(v);
        }
        else {
            int findVariable = findPreexisitingVariable(variableVector, variableName); //returns counter of var
            identifiedType = identifyVariableType(variableVector, value);

            if (findVariable != -1) { // variable is found, index is returned
                variableVector[findVariable].type = identifiedType; // Overwrite preexisting variable
            }
            else {
                v = { variableName, identifiedType }; // Otherwise push new variable into the vector
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