// #include <iostream>
// #include <vector>
#include "helper.cpp"
using namespace std;

bool isExpression(string s); /*variables.cpp*/
int findPreexisitingVariable(vector<variables> v, string key); /*variables.cpp*/
string identifyVariableType(vector<variables> v, string value); /*variables.cpp*/
string getTypeOfVariable(vector<variables> v, string key); /*variables.cpp*/
string evaluateExpression(vector<variables> v, string s); /*variables.cpp*/
void printVariableInformation(variables vars); /*helper.cpp*/
void printStringVector(vector<string> stringVector); /*helper.cpp*/
string get_str_between_two_str(const std::string& s,
	const std::string& start_delim,
    const std::string& stop_delim);			/*helper.cpp*/
	vector<string> split(string str, string token);
void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr); /*helper.cpp*/
void printVector(vector<variables> variableVector); /*helper.cpp*/
void removeNewLinesAndTabs(string& s); /*helper.cpp*/
bool isNumber(const std::string& s); /*helper.cpp*/
int evaluate(string s1); /*helper.cpp*/
void removeComments(string &line); /*helper.cpp*/
string getIfElseResultInsideFunction(functions f, variables v); /*ifelseeval.cpp*/
void pop_all(vector<string>& vec); /*helper.cpp*/
string loopedFindAndReplaceVariableVector(vector<variables> &vec, string line);
string loopedFindAndReplaceStringVector(vector<string> functionParameters, vector<string> vec, string line);

int findNumberOfParameters(string line) {
    int count = 0;

    for (int i = 0; i < line.size(); i++)
        if (line[i] == ',')
            count++;

    return count + 1;
}

int findIfFunctionExists(string functionNameToFind) {
    for (int i = 0; i < functionsVector.size(); i++) {
        if (functionsVector.at(i).functionName == functionNameToFind) {
            return i;
        }
    }
    return -1;
}

vector < variables > retrieveParameters(int functionPosition, string s) {
    string parametersName, parametersType;
    s += ")"; //set delimiter
    char char_array[s.size() + 1];
    strcpy(char_array, s.c_str());
    vector < variables > parameters;

    for (int i = 0; i < s.length(); i++) {
        if (char_array[i] != ',' && char_array[i] != ')') {
            parametersName += char_array[i];
        } else {
            parametersType = identifyVariableType(functionsVector.at(functionPosition).functionVariables, parametersName);
            parameters.push_back({
                parametersName,
                parametersType
            });

            // cout << "parametersName: " << parametersName << ", parametersType: " << parametersType << endl;

            parametersName = parametersType = "";
        }
    }
    return parameters;
}


string getTypeAfterFunctionCall(vector<functions> v, int functionPosition, string line) {
	string identifiedType;
	functions f = v.at(functionPosition);
	vector<variables> parametersFromFunctionCall;
	parametersFromFunctionCall.push_back({".","."});									//set delimiter

	if (line.length() != 0) {	
		parametersFromFunctionCall = retrieveParameters(functionPosition, line);		//"2",3
		for (int i = 0; i < parametersFromFunctionCall.size(); i++) {
			parametersFromFunctionCall.at(i).name = f.parametersString.at(i);			//a:str, b:int
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
			// cout << "--evaluateExpression inside getTypeAfterFunctionCall" << endl;
				identifiedType = evaluateExpression(parametersFromFunctionCall, f.returnValue);
				parametersFromFunctionCall.erase(parametersFromFunctionCall.begin());
			}

			parametersFromFunctionCall.erase(parametersFromFunctionCall.begin());
		}

	}

	return identifiedType;
}

string replacevariableNamesWithValuesDuringCall(vector<variables> vectorToExtractFrom, string s) {
	// cout << "s: " << s << endl;
	// string functionName = get_str_between_two_str(s, "", "(");

	/*takes (v, 10) and if v: 5, returns 5,10*/

	s = get_str_between_two_str(s, "(", ")");
	vector<string> runTimeValue = split(s, ",");
	string result;
	bool flag = false;
	for (int i = 0; i < runTimeValue.size(); i++) {
		// cout << "runTimeValue[i] = " << runTimeValue[i] << endl;
		int checkVarPosition = findPreexisitingVariable(vectorToExtractFrom, runTimeValue[i]);
		if (checkVarPosition != -1) {
			flag = true;
			result += vectorToExtractFrom[checkVarPosition].value;

			// cout << "result: " << result << endl;
		} else {
			result += runTimeValue[i];
		}

		if (i != runTimeValue.size()-1) {
			result += ",";
		}
	}

	// cout << s << " after op: " << result << endl;
	removeNewLinesAndTabs(result);
	if (flag) return result;
	else return s;
}

functions simplyfyFunction(functions f) {
/*Find and replace local variables inside function*/

	// cout << "simplifying \n";

	for (int i = 0; i < f.functionVariables.size(); i++) {

		string variableToReplace = f.functionVariables[i].name;
		string valueToReplaceWith = f.functionVariables[i].value;

		for (int i = 0; i < f.functionBody.size(); i++) {
			// findAndReplaceAll(f.functionBody[i], variableToReplace, valueToReplaceWith);
			if (f.functionBody[i].find("=") != string::npos) {
				string toKeep = get_str_between_two_str(f.functionBody[i], "", "=");
				string toChange = get_str_between_two_str(f.functionBody[i], "=", "");
				findAndReplaceAll(toChange, variableToReplace, valueToReplaceWith);

				f.functionBody[i] = toKeep + "=" + toChange;

				removeNewLinesAndTabs(toKeep);
				int varPos = findPreexisitingVariable(f.functionVariables, toKeep);

				if (varPos != -1) {
					// cout << "updating " << toKeep << " to " << toChange << " inside simplyfyFunction\n";
					f.functionVariables[varPos].value = toChange;
				}
			}
		}
	}

	// printVector(f.functionVariables);

	return f;
}

string getValueAfterFunctionCall(functions f, variables v) {

	// cout << "getting value\n";

    string currentInstruction, valueAfterCall;
	// cout << "currentInstruction: " << currentInstruction << endl;

	// printStringVector(f.functionBody);
	// cout << f.functionBody.size() << endl;
	// return "";

    f.functionBody.erase(f.functionBody.begin()); /*remove the function header*/

    v.value = get_str_between_two_str(v.value, "(", ")");
    vector < string > variableParamtersString = split(v.value, ",");
    vector < variables > localParameters;
    variables localVariable;
    bool ifElseStatementsStarted = false;

    // printVector(f.functionVariables);

 //    cout << "before replacement \n";
	// printStringVector(variableParamtersString);	

    for (int i = 0; i < f.functionBody.size(); i++) {
    	/*replace function local parameters*/
    	string frontOfVector = f.functionBody.front();
		 f.functionBody[i] = loopedFindAndReplaceVariableVector(f.functionVariables, f.functionBody[i]);

		 /*find and replace with passed in paameters*/
		 f.functionBody[i] = loopedFindAndReplaceStringVector(f.parametersString, variableParamtersString, f.functionBody[i]);

    }

    // printStringVector(f.functionBody);

    for (int i = 0; i < variableParamtersString.size(); i++) {

		/*replace local function var with passed in parameters*/
    	string variableToReplace = f.parametersString[i];
    	string valueToReplaceWith = variableParamtersString[i];

		// cout << variableToReplace << "=" << valueToReplaceWith << endl;

    	for (int j = 0; j < variableParamtersString.size(); j++) {
    		findAndReplaceAll(variableParamtersString[j], variableToReplace, valueToReplaceWith);
    	}
    }

    // cout << "after replacement \n";
    // printStringVector(variableParamtersString);
    // printStringVector(f.functionBody);


    // printStringVector(variableParamtersString);
    for (int i = 0; i < variableParamtersString.size(); i++) {
    	/*check if there are global variables inside function calls from main function,

		example:
		v2 = 3
		v1 = add(v2,1) => add(3,1)
    	*/
    	int checkVarPosition = findPreexisitingVariable(variableVector, variableParamtersString[i]);
    	if (checkVarPosition != -1) {
    		variableParamtersString[i] = variableVector[checkVarPosition].value;
    		// cout << variableParamtersString[i] << " = " << variableVector[checkVarPosition].value << endl;
    	}
    }

 //    cout << "printing variableParamtersString \n";	// => 2
	// printStringVector(variableParamtersString);

	// cout << "printting function parametersString \n"; // => x
	// printStringVector(f.parametersString);

	// printStringVector(f.functionBody);
	// printVector(f.functionVariables);
	// return "";


    for (int j = 0; j < variableParamtersString.size(); j++) {

        /*replace parameters with the passed in value*/
		string variableToReplace = f.parametersString[j];
		string valueToReplaceWith = variableParamtersString[j];

		// cout << variableToReplace << " -- " << valueToReplaceWith << endl;

		for (int i = 0; i < f.functionBody.size(); i++) {
			if (f.containsIfElse && (f.functionBody[i].find("if ") == string::npos
				|| f.functionBody[i].find("else:") != string::npos)) {
				// cout << "checked for if/else\n";
				findAndReplaceAll(f.functionBody[i], variableToReplace, valueToReplaceWith);
			} else if (!f.containsIfElse) {
				// findAndReplaceAll(f.functionBody[i], variableToReplace, valueToReplaceWith);
				if (f.functionBody[i].find("=") != string::npos) {
					// cout << "variables needs to be replaced " << " inside getValueAfterFunctionCall\n";
					string toKeep = get_str_between_two_str(f.functionBody[i], "", "=");
					string toChange = get_str_between_two_str(f.functionBody[i], "=", "");

					// cout << "\ttoChange before replacement: " << toChange << endl;
					findAndReplaceAll(toChange, variableToReplace, valueToReplaceWith);
					// cout << "\ttoChange after replacement: " << toChange << endl;


					// cout << "functionBody before replacement: " << f.functionBody[i] << endl;
					f.functionBody[i] = toKeep + "=" + toChange;
					// cout << "functionBody after replacement: " << f.functionBody[i] << endl;


					removeNewLinesAndTabs(toKeep);
					// cout << "keeping: " << toKeep << "." << endl;
					int varPos = findPreexisitingVariable(f.functionVariables, toKeep);

					if (varPos != -1) {
						// cout << "updating " << toKeep << " to " << toChange << " inside getValueAfterFunctionCall\n";
						f.functionVariables[varPos].value = toChange;
					} else {
						f.functionVariables.push_back({toKeep, "", toChange});
					}
				} else if (f.functionBody[i].find("return ") != string::npos) {
					findAndReplaceAll(f.functionBody[i], variableToReplace, valueToReplaceWith);
				}
			} 
		}
	}

	functions f_copy = f;
	// printStringVector(f.functionBody);
	// printVector(f.functionVariables);
	// return "";

    while (f.functionBody.size() != 1) {
        /*keep popping until return statement is reached*/
        currentInstruction = f.functionBody.front();


		if (currentInstruction.find("if ") != string::npos) { 
			// f.functionBody.push_back(getIfElseResultInsideFunction(f_copy, v));
			string eval = getIfElseResultInsideFunction(f_copy, v);
			f.functionBody.insert(f.functionBody.begin(), eval);

			pop_all(f.functionBody);
			
			break;
		}

        if (currentInstruction.find("return ") == string::npos) {
        	/*Until return is not found*/
            f.functionBody.erase(f.functionBody.begin());
        }
    }


    currentInstruction = f.functionBody.front();
    // cout << "currentInstruction: " << currentInstruction << endl;

    // return "";
    removeNewLinesAndTabs(currentInstruction);






    string returnStatement = get_str_between_two_str(currentInstruction, "return ", "");
   	removeNewLinesAndTabs(returnStatement);

   	int checkVarPosition = findPreexisitingVariable(f.functionVariables, returnStatement);

   	// cout << "returnStatement before replacement is " << returnStatement << endl;
   	if (checkVarPosition != -1) {
   		returnStatement = f.functionVariables[checkVarPosition].value;
   	}
   	// cout << "returnStatement after replacement is " << returnStatement << endl;

   	// return "";



    /*Check if return statement is an expression*/
    if (returnStatement[0] == '-' && stoi(returnStatement)) {
    	// cout << "returnStatement: " << returnStatement << endl;
    	return returnStatement;
    }
    else if (returnStatement.find("+") != string::npos ||
        returnStatement.find("-") != string::npos ||
        returnStatement.find("*") != string::npos ||
        returnStatement.find("/") != string::npos) {


        findAndReplaceAll(returnStatement, "+", " + ");
        findAndReplaceAll(returnStatement, "*", " * ");
        findAndReplaceAll(returnStatement, "-", " - ");
        findAndReplaceAll(returnStatement, "/", " / ");

        valueAfterCall = to_string(evaluate(returnStatement));
    }  else {
        valueAfterCall = returnStatement;
    }

    // cout << "valueAfterCall is " << valueAfterCall << endl;
    removeComments(valueAfterCall);
    return valueAfterCall;
}


int countNumberOfFunctionCalls(string s) {
	char char_array[s.size() + 1];
	strcpy(char_array, s.c_str());
	int balanced = 0;
	int numberOfFunctions = 0;

	for (int i = 0; i < s.length(); i++) {
		if (char_array[i] == '(') {
			balanced ++;
			numberOfFunctions ++;
		}
		else if (char_array[i] == ')') 
			balanced --;
	}

	// cout << "inside countNumberOfFunctionCalls\n";

	if (balanced <= 0) return numberOfFunctions;
	else return -1;
}


// /*score 201*/
string evaluateMultipleFunctionCalls(string st) {
	// printf("function is called\n");

	findAndReplaceAll(st, "(" , " ");
	findAndReplaceAll(st, ")" , " ");
	findAndReplaceAll(st, "," , " ");
	findAndReplaceAll(st, "  ", " ");


	vector<string> functionCalls = split(st, " ");
	int iterator = 0;
	variables v;
	functions f;

	while (functionCalls.size() != 1) {
		// printf("inside while\n");
		vector<string> temp;
		for (int i = 0; i < functionCalls.size()-1; i++) {
			// printf("inside for-1\n");
			string num1 = functionCalls[i];
			string num2 = functionCalls[i+1];

			int checkVarPosition = findPreexisitingVariable(variableVector, num1);
			if (checkVarPosition != -1) {
				num1 = variableVector[checkVarPosition].value;
			}

			checkVarPosition = findPreexisitingVariable(variableVector, num2);
			if (checkVarPosition != -1) {
				num2 = variableVector[checkVarPosition].value;
			}

			if (isNumber(num1) && isNumber(num2)) {
				// printf("inside if-1\n");
				string functionName = functionCalls[i-1];
				f = functionsVector[findIfFunctionExists(functionName)];
				// cout << "function " << f.functionName << " has " << f.parametersString.size() << " parameters." << endl;

				temp.pop_back();

				v.value =  "(" + num1;

				if (f.parametersString.size() == 2) {
					if (isNumber(num2)) {
						v.value = v.value + "," + num2;

					}
				}

				v.value = v.value + ")";
				// v.value = "(" + num1 + "," + num2 + ")";
				// cout << v.name << ":" << v.value << endl;


				temp.push_back(getValueAfterFunctionCall(f, v));
				// cout << "after call: " << getValueAfterFunctionCall(f, v);
				// printf("inside if\n");

				for (int j = i + 2; j < functionCalls.size(); j++) {
					// printf("inside for-2\n");
					temp.push_back(functionCalls[j]);
				}

				break;
			} /*else if (isNumber(num1)) {
				cout << "num1 is a number\n";
				cout << "functionBody[i-1] is " << f.functionBody[i-1] << endl;  
				printStringVector(temp);

				temp.push_back(num1);
			}*/

				else {
					temp.push_back(num1);
				}

			/*else {
				cout << "num1 = " << num1 << "." << endl; 
				cout << "num2 = " << num2 << "." << endl; 

				temp.push_back(num1); 


				if (isNumber(num1)) {
					cout << "if - num1 is a number\n";

					string functionName = f.functionBody[i-1];
					f = functionsVector[findIfFunctionExists(functionName)];
					if (f.parametersString.size() == 1) {
						cout << "function takes one pama\n";

						temp.pop_back();
						v.value = "(" + num1 + ")";

						temp.push_back(getValueAfterFunctionCall(f, v));
						

						for (int j = i + 2; j < functionCalls.size(); j++) {
					// printf("inside for-2\n");
							temp.push_back(functionCalls[j]);
						}

						break;
					}

					break;
					
				} else {
					cout << "else - num1 is not number\n";
					temp.push_back(num1);
				}
				return "110";
				
			}*/
			

		} //end for

		functionCalls = temp;
	} //end while

	// cout << "inside evaluateMultipleFunctionCalls: " << functionCalls[0] << endl;

	return (functionCalls[0]);
}
