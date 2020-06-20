#include "ifElseEvaluator.cpp"
using namespace std;

bool ifelsedebugger = false;
bool runTimeDebugger = false;


int main(int argc, char const* argv[]) {
	string commandLine = argv[1]; commandLine += ";";

	string fileName = get_str_between_two_str(commandLine, "", ";");

	string line, variableName, variableValue, identifiedType, functionName;
	int functionPosition;
	bool flag = false, hasFunctions = false;
	variables v;
	vector<functions> fcopy;


	cleanFile(fileName);

	ifstream inFS(fileName.c_str());

	int numberOfVariables = 0;
	
	if (!inFS.is_open()) {
		cout << "Unable to open the file." << endl;
		return 0;
	}



	while (getline(inFS, line)) {
		removeComments(line);

		if (runTimeDebugger) cout << "line length: " << line.length() << endl;

		if (line == "\n" || line == " " || line == "" || line.length() < 2) continue;

		if (line.substr(0, 6) == "print(") {
			// consoleOutputs.push_back(line);
			printToConsoleIndividually(line);
			continue;
		}

		if (line.substr(0,1) == "#") 
			continue;


		if (line.substr(0, 4) == "def ") {
			functions f;
			f.functionBody.push_back(line);
			// cout << line << endl;


			f.functionName = get_str_between_two_str(line, "def ", "(");

			removeNewLinesAndTabs(f.functionName);
			// cout << "pushing " << f.functionName << endl;

			f.numberOfParameters = findNumberOfParameters(line);
			

			findAndReplaceAll(line, " ", "");
			f.parametersString = split((get_str_between_two_str(line, "(", "):")), ",");


			getline(inFS, line);
			while (line != "") {
				if (line.find("def ") != string::npos) {
					// cout << "new function def found, breaking\n";
					break;
				}

				f.functionBody.push_back(line);

				// cout << "line: " << line << endl;

				if (line.length() < 2) { 
					// cout << "line length is < 2\n";
					break; 
				}

				if (line.find("if ") != string::npos) {
					flag = true;
					f.containsIfElse = true;


					while (getline(inFS, line)) {
						if (line == "") break;

						if (line.at(0) != ' ') {
							break;
						}
						f.functionBody.push_back(line);

						// cout << "pushed: " << line << endl;
					}

					break;
				}


				if (line.find("return") != string::npos) {	
					// cout << "return found\n";
					// getline(inFS, line);

					// cout << "next line: " << line << endl;

					// return 0;
					// break;
					if (!flag) { 
						removeNewLinesAndTabs(line);
						f.returnValue = get_str_between_two_str(line, "return ", "\n");
						getline(inFS, line);

						// cout << "no flag - breaking\n";
						break;
						// return 0;
					} else { 
						flag = false;
						// cout << "flag is now false\n";
						break;
					}
				} 

				removeNewLinesAndTabs(line);

				if (line.find("=") != string::npos) {

					variableName = get_str_between_two_str(line, "", "=");
					variableValue = get_str_between_two_str(line, "=", "\n");	



					if (isExpression(variableValue)) {
						identifiedType = evaluateExpression(f.functionVariables, variableValue);
					} else {
						int findVariable = findPreexisitingVariable(f.functionVariables, variableName);
						if (findVariable != -1) {
							identifiedType = f.functionVariables.at(findVariable).type;
							variableValue = replacevariableNamesWithValuesDuringCall(f.functionVariables, variableValue);
						} else {
							identifiedType = identifyVariableType(f.functionVariables, variableValue);
						}
					}


					v = { variableName, identifiedType, variableValue };
					f.functionVariables.push_back(v);
				}

				// if (flag) {cout << "flagged true\n";}
				// else {cout << "\t--flagged false\n";}
				getline(inFS, line);
			} //end while

			fcopy.push_back(f);
			// printStringVector(f.functionBody);


			if (!f.containsIfElse || f.functionVariables.size() > 0) {
				f = simplyfyFunction(f);
			}	

			functionsVector.push_back(f);
			if (runTimeDebugger) cout << "pushed function\n";

			
			// cout << "end of loop\n" << endl;
			
		} //function end

		// printStringVector(functionsVector[0].functionBody);
		// getline(inFS,line);
		// cout << "line: " << line << endl;
		// return 0;

		// vector<functions> fcopy = functionsVector;
		if (line.substr(0, 3) == "if ") {
			if (runTimeDebugger) cout << "line has if/else\n";

			trim(line);
			if (trim(line).back() != ':') {
				// cout << "line is valid\n";
				// If the statement is missing a colon
				while (line.substr(0, 4) != "else") {
					// cout << line << endl;
					getline(inFS, line);
				}
				getline(inFS, line);
				getline(inFS, line);
				getline(inFS, line);

				continue;
			}

			// vector<string> ifelsebody;

			// while (line.at(0) == ' ') {
			// 	ifelsebody.push_back(line);
			// 	getline(inFS, line);
			// }
			
			// printStringVector(ifelsebody);
			

			line = getIfElseResult(line, false);

			if (line == "-99") {
				while (line.find("else:") == string::npos) {
					getline(inFS, line);
				}
			}
			
			// cout << "line returned after if else evaluation" << line << endl;
			removeNewLinesAndTabs(line);
		} else {
			if (ifelsedebugger)	cout << "Operator not found" << endl;
		} //if end


		if (line.find("=") != string::npos) {
			numberOfVariables++;

			if (runTimeDebugger) cout << "Variable is assigned\n";

			v.name = get_str_between_two_str(line, "", "=");
			v.value = get_str_between_two_str(line, "=", "");
			removeNewLinesAndTabs(v.name);


			int varPosition = findPreexisitingVariable(variableVector, v.name);

			if (v.name == "") { continue; }
			else if (isExpression(v.value)) {
				if (runTimeDebugger) printf("variable is an expression\n");

				v.value = evaluateExpressionWithVariables(v.value);

				// cout << "after variable evaluation, v.value = " << v.value << endl;

				identifiedType = evaluateExpression(variableVector, v.value);
				v.type = identifiedType;

				if (varPosition != -1) {
					variableVector[varPosition] = v;
				} else {
					variableVector.push_back(v);
				}


			} else if (line.find("(") != string::npos) {
				if (runTimeDebugger) cout << "Calling a function variable: " << v.name << endl;
				/*Check if parenthesis are balanced*/
				int numberOfFunctionCalls = countNumberOfFunctionCalls(v.value);

				// cout << "number of function calls: " << numberOfFunctionCalls << endl;

				if (numberOfFunctionCalls > 1) {

					
					v.value = evaluateMultipleFunctionCalls(v.value);
					if (varPosition != -1) {
						variableVector[varPosition] = v;
					} else {
						variableVector.push_back(v);
					}

					// return 0;

					// cout << v.name << " is " << v.value << endl;
					continue;
				}



				functionName = get_str_between_two_str(v.value, "=", "(");

				functionPosition = findIfFunctionExists(functionName);

				if (functionPosition == -1) {
					v.type = "undefined";
					// cout << functionPosition << endl;
					if (runTimeDebugger) cout << "func not found\n";
				} else if (findNumberOfParameters(v.value) != functionsVector.at(functionPosition).numberOfParameters) {

					v.type = "undefined";
					if (runTimeDebugger) cout << "func params dont match\n";
				} else {
					

					// v.type = getTypeAfterFunctionCall(functionsVector, functionPosition, parameters);

					// printf("all good!\n");
					functions f = fcopy[functionPosition];

					removeNewLinesAndTabs(v.value);
					removeComments(v.value);

					v.value = replacevariableNamesWithValuesDuringCall(variableVector, v.value);
					// return 0;

					// cout << v.name << " before variable replacement is " << v.value << endl;
					v.value = getValueAfterFunctionCall(f, v);

					// cout << v.name << " is " << v.value << endl;
					// return 0;

					// cout << "all good: " << v.type << endl;
				}

				if (varPosition != -1) {
					variableVector[varPosition] = v;
				} else {
					variableVector.push_back(v);
				}


			} else {
				if (runTimeDebugger)  printf("Not calling a function variable\n");
				int findVariable = findPreexisitingVariable(variableVector, v.name);
				removeNewLinesAndTabs(v.value);
				v.type = identifyVariableType(variableVector, v.value);

				if (findVariable != -1) {
					variableVector[findVariable] = v;
				} else {
					variableVector.push_back(v);
				}
			}

		} //variable end
		// printVariableInformation(v);
			
		// cout << "before while " << "line: "<< line << endl;
		// printVector(variableVector);

		// if (numberOfVariables == variableVector.size()) {
		// 	break;
		// }

	} //end while
	if (runTimeDebugger) cout << "after while " << "line: "<< line << endl;

	// printVector(variableVector);
	
	// printOutputToConsole(consoleOutputs);
	// cout << "after printing to console" << endl;

	return 0;
}