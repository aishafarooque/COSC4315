#include "variables.cpp"
using namespace std;

bool evaluateIfElseExpression(int LHS, string op, int RHS) {
	if (op == "<") return LHS < RHS;
	else if (op == ">") return LHS > RHS;
	else if (op == ">=") return LHS >= RHS;
	else if (op == "<=") return LHS <= RHS;
	else if (op == "!=") return LHS != RHS;
	else if (op == "==") return LHS == RHS;
}

string findOperator(string line) {
    /*Find out which operator (>, <, ==, !=)*/
	if (line.find("<") != string::npos) return "<";
	else if (line.find(">") != string::npos) return ">";
	else if (line.find(">=") != string::npos) return ">=";
	else if (line.find("<=") != string::npos) return "<=";
	else if (line.find("!=") != string::npos) return "!=";
	else if (line.find("==") != string::npos) return "==";
	else return "No operator found";
}

bool getIfElseResult(string line, bool fromFunction) {
	string argument = line.substr(3, line.length());

	removeNewLinesAndTabs(argument);

	string op = findOperator(argument);

	string LHSVariableName = (get_str_between_two_str(argument, "", op));
	string ifArgumentRHS = (get_str_between_two_str(argument, op , ":"));

	string ifArgumentLHS;
	if (!fromFunction) 	ifArgumentLHS = (variableVector.at(findPreexisitingVariable(variableVector, LHSVariableName)).value);
	else ifArgumentLHS = LHSVariableName;



	int checkLHS = findPreexisitingVariable(variableVector, ifArgumentLHS);
	int checkRHS = findPreexisitingVariable(variableVector, ifArgumentRHS);


	if (checkLHS != -1) {
		ifArgumentLHS = variableVector[checkLHS].value;
	}

	if (checkRHS != -1) {
		ifArgumentRHS = variableVector[checkRHS].value;
	}


	// cout << "getting result for: " << ifArgumentLHS << op << ifArgumentRHS << endl;
	return evaluateIfElseExpression(stoi(ifArgumentLHS), op, stoi(ifArgumentRHS));
}


string loopedFindAndReplaceVariableVector(vector<variables> &vec, string line) {
	string varName, varValue, stringToReplace;
	bool flag = false;
	for (int i = 0; i < vec.size(); i++) {
		varName = vec[i].name;
		varValue = vec[i].value;

		if (line.find("=") != string::npos && line.find("<=") == string::npos && line.find(">=") == string::npos 
			&& line.find("==") == string::npos && line.find("!=") == string::npos) {
		
			stringToReplace = get_str_between_two_str(line, "=", "");
			flag = true;

		} else {
			stringToReplace = line;
		}
		
		findAndReplaceAll(stringToReplace, varName, varValue);

		if (line.find("return") != string::npos) {
			/*dont change return statment due to override local var*/
			continue;
		}

		if (flag) {
			line = varName + "=" + stringToReplace;
			flag = false;
		} else {
			line = stringToReplace;
		}

	}


	return line;
}


string loopedFindAndReplaceStringVector(vector<string> functionParameters, vector<string> vec, string line) {

	string varName, varValue, stringToReplace, localVarName;
	bool flag = false;
	for (int i = 0; i < functionParameters.size(); i++) {
		varName = functionParameters[i];
		varValue = vec[i];

		if (line.find("=") != string::npos && line.find("<=") == string::npos && line.find(">=") == string::npos 
			&& line.find("==") == string::npos && line.find("!=") == string::npos) {
			localVarName = get_str_between_two_str(line, "", "=");
			stringToReplace = get_str_between_two_str(line, "=", "");
			flag = true;

		} else {
			stringToReplace = line;
		}
		

		findAndReplaceAll(stringToReplace, varName, varValue);

		if (line.find("return") != string::npos) {
			/*dont change return statment due to override local var*/
			continue;
		}
		
		if (flag) {
			line = localVarName + "=" + stringToReplace;
			flag = false;
		} else {
			line = stringToReplace;
		}
	}
	return line;
}


string getIfElseResultInsideFunction(functions f, variables v) {

	vector <string> passedInParameters = split(v.value, ",");
	vector <string> ifElseStatements;
	vector <variables> functionVariablesDuringEvaluation;
	string frontOfVector, variableName, variableValue, ifElseResult;
	vector<string>::iterator it;
	bool ifElseStatementsStarted = false;

	// printStringVector(f.functionBody);

	for (int i = 0; i < f.functionBody.size(); i++) {

		/*replace function local parameters*/
		 f.functionBody[i] = loopedFindAndReplaceVariableVector(f.functionVariables, f.functionBody[i]);

		 /*find and replace with passed in paameters*/
		 f.functionBody[i] = loopedFindAndReplaceStringVector(f.parametersString, passedInParameters, f.functionBody[i]);


		 frontOfVector = f.functionBody[i];
		 string nextInstruction = f.functionBody.at(1);

		 if (frontOfVector.find("if ") != string::npos) {
		 	// cout << "if else statements have started\n";
		 	ifElseStatementsStarted = true;
		 }

		 if (frontOfVector.find("=") != string::npos && frontOfVector.find("if ") == string::npos) {

		 	variables v ({
		 		get_str_between_two_str(frontOfVector, "", "="),
		 		"",
		 		get_str_between_two_str(frontOfVector, "=", "")
		 	});


		 	int checkPos = findPreexisitingVariable(functionVariablesDuringEvaluation, v.name);
		 	if (checkPos == -1) {
		 		functionVariablesDuringEvaluation.push_back(v);
		 	} else {
		 		functionVariablesDuringEvaluation[checkPos] = v;
		 	}
		 } /*else {
		 	ifElseStatements.push_back(f.functionBody[i]);
		 }*/

		 if (ifElseStatementsStarted) { ifElseStatements.push_back(frontOfVector); }
	}

	// cout << "f.functionBody: " << endl;
	// printStringVector(f.functionBody);

	// cout << "ifElseStatements: " << endl;
	// printStringVector(ifElseStatements);
	// cout << "\n\n\n\n";

	// return "return x*y";

	// f.functionBody.clear();
	f.functionBody = ifElseStatements;

	// return "return x*y";
	frontOfVector = f.functionBody.front();

	bool ifElseDebugger = false;

	if (frontOfVector.find("if ") != string::npos) {
		frontOfVector = get_str_between_two_str(frontOfVector, "i", "");

		frontOfVector = "i" + frontOfVector;

		if (getIfElseResult(frontOfVector, true)) {

			if (ifElseDebugger) cout << frontOfVector << " is true and under level-1.\n";

			f.functionBody.erase(f.functionBody.begin());
			frontOfVector = f.functionBody.front();

			if (frontOfVector.find("if ") != string::npos) {

				frontOfVector = get_str_between_two_str(frontOfVector, "i", "");
				if (getIfElseResult("i" + frontOfVector, true)) {
					if (ifElseDebugger) cout << frontOfVector << " is nested (if) and true\n";
					
					f.functionBody.erase(f.functionBody.begin());
					frontOfVector = f.functionBody.front();

					ifElseResult = frontOfVector;
				} else {
					if (ifElseDebugger) cout << frontOfVector << " is nested (if) and false\n";
					while (f.functionBody.front() != "      else:") {
						f.functionBody.erase(f.functionBody.begin());
					}

					f.functionBody.erase(f.functionBody.begin());
					ifElseResult = f.functionBody.front();
				}
			} else {
				
				// f.functionBody.erase(f.functionBody.begin());
				// frontOfVector = f.functionBody.front();

				if (ifElseDebugger) cout << "if else will return " << frontOfVector << endl;


				ifElseResult = frontOfVector;
			}

		} else {
			if (ifElseDebugger) cout << frontOfVector << " is false and under level-1.\n";

			while(frontOfVector != "   else:") {
				f.functionBody.erase(f.functionBody.begin());
				frontOfVector = f.functionBody.front();
			}

			f.functionBody.erase(f.functionBody.begin());
			frontOfVector = f.functionBody.front();

			if (frontOfVector.find("if ") != string::npos) {
				frontOfVector = get_str_between_two_str(frontOfVector, "i", "");


				if (getIfElseResult("i" + frontOfVector, true)) {
					if (ifElseDebugger) cout << frontOfVector << " is nested (else) and true\n";

					f.functionBody.erase(f.functionBody.begin());
					frontOfVector = f.functionBody.front();

					ifElseResult = frontOfVector;
				} else {
					if (ifElseDebugger) cout << frontOfVector << " is nested (else) and false\n";
					while (f.functionBody.front() != "      else:") {
						f.functionBody.erase(f.functionBody.begin());
					}

					f.functionBody.erase(f.functionBody.begin());
					ifElseResult = f.functionBody.front();
				}
			} else {
				if (ifElseDebugger) cout << "else if not nested and returns " << frontOfVector << endl;
				ifElseResult = frontOfVector;
			}
		}
	} else {
		if (ifElseDebugger) cout << "No if else statements found\n";
	}


	int checkForVariable = findPreexisitingVariable(functionVariablesDuringEvaluation, get_str_between_two_str(ifElseResult, "return ", ""));
	if (checkForVariable != -1) {
		ifElseResult = "return " + functionVariablesDuringEvaluation[checkForVariable].value;
	} else {
		string removeSpaces = get_str_between_two_str(ifElseResult, "return", "");
		ifElseResult = "return " + removeSpaces;
	}

	if (ifElseResult.find("=") != string::npos) {
		string removeSpaces = get_str_between_two_str(ifElseResult, "=", "");
		ifElseResult = "return " + removeSpaces;
	}

	// cout << "returning: " << ifElseResult << endl;
	return ifElseResult;
}