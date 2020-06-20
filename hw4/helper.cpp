// #include <iostream>
// #include <cstring>
// #include <bits/stdc++.h>
// #include <string>
// #include <algorithm>
#include "structDefinition.cpp"
using namespace std;

int findPreexisitingVariable(vector<variables> v, string key);  /*variables.cpp*/
string getValueAfterFunctionCall(functions f, variables v); /*functions.cpp*/
int findIfFunctionExists(string functionNameToFind); /*functions.cpp*/
int countNumberOfFunctionCalls(string s); /*functions.cpp*/
string evaluateMultipleFunctionCalls(string st); /*functions.cpp*/
bool isExpression(string s); /*variables.cpp*/
string evaluateExpressionWithVariables(string str); /*variables.cpp*/

string get_str_between_two_str(const std::string& s,
    const std::string& start_delim,
    const std::string& stop_delim) {
    /*Code credit to: https://stackoverflow.com/questions/18800796/
	c-get-string-between-two-delimiter-string/18800868*/
    unsigned first_delim_pos = s.find(start_delim);
    unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
    unsigned last_delim_pos = s.find(stop_delim);

    return s.substr(end_pos_of_first_delim,
        last_delim_pos - end_pos_of_first_delim);
}

void removeNewLinesAndTabs(string& s) {
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
}

vector<string> split(string str, string token) {
    /*str = "1,2" and token = ",", then return vector("1","2")*/
    vector<string>result;
    while(str.size()) {
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

void removeComments(string &line) {
  vector<string> cleanedLine = split(line, "#");
  line = cleanedLine[0];
}


bool isNumber(const std::string& s) {
    // Checks if string is a number or not
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

bool compareAlphabetically(const variables& a, const variables& b) {
    return a.name < b.name;
}

void printVector(vector<variables> variableVector) {
    // cout << "Printing variables vector." << endl;

    sort(variableVector.begin(), variableVector.end(), compareAlphabetically);
    for (int i = 0; i < variableVector.size(); ++i) {
        cout << variableVector[i].name << ": " << variableVector[i].type << ", " << variableVector[i].value << endl;
    }
}

void printStringVector(vector<string> stringVector) {
    for (int i = 0; i < stringVector.size(); ++i) {
        cout << stringVector.at(i) << endl;
    }
}

std::string trim(const std::string& line) {
    const char* WhiteSpace = " \t\v\r\n";
    std::size_t start = line.find_first_not_of(WhiteSpace);
    std::size_t end = line.find_last_not_of(WhiteSpace);
    return start == end ? std::string() : line.substr(start, end - start + 1);
}

string printFunction(string line) {
    if ((line.find("(") || line.find(")")) == string::npos) {
        return "";
    }

    line.replace(line.begin(), line.end(), "\'", "\"");
    string statement = get_str_between_two_str(line, "(\"", "\")");

    return statement;
}

void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr) {
    size_t pos = data.find(toSearch);
    while( pos != std::string::npos) {
        data.replace(pos, toSearch.size(), replaceStr);
        pos =data.find(toSearch, pos + replaceStr.size());
    }
}

void pop_all(vector<string>& vec) {
    while (vec.size() != 1)
        vec.pop_back();
}

void printVariableInformation(variables vars) {
    cout << vars.name << ": " << vars.type << ", " << vars.value << endl;
}

string houseCleaning(string toParse) {
  string cleanStr = toParse;
//House-Cleaning Sanitizing String!
  if (!toParse.empty() && toParse[toParse.size() - 1] == '\r')
    cleanStr = toParse.erase(toParse.size() - 1);

  return cleanStr;
}


// void printOutputToConsole(vector<string> consoleOutputs) {

//     for (string line: consoleOutputs) {
//         // removeComments(line);

//         findAndReplaceAll(line, "print(", "");
//         vector<string> elements = split(line, ",");

//         for (string substring: elements) {
//           substring = houseCleaning(substring);
//             if (substring.find(")") != string::npos) {
//                 /*Remove closing parenthesis from the end of vector*/
//                 findAndReplaceAll(substring, ")", "");
//             }

//             if (substring.find("\"") != string::npos) {
//                 /*cout the statement in quotes*/
//                 findAndReplaceAll(substring, "\"", "");
//                 cout << substring;
//             } else {
                
//                 removeNewLinesAndTabs(substring);

//                 int variablePosition = findPreexisitingVariable(variableVector, substring);
//                 variables v = variableVector[variablePosition];
//                 removeComments(v.value);

//                 if (v.value.find("(") != string::npos) {

//                     int functionPosition = findIfFunctionExists(get_str_between_two_str(v.value, "=", "("));

//                     // cout << "single call: substring is " << substring << "." << endl;
//                     printStringVector(functionsVector[functionPosition].functionBody);
//                     // return;
//                     v.value =  getValueAfterFunctionCall(functionsVector[functionPosition], v);
//                     cout << v.value;

//                     // cout << " is the value after function call evaluation";
                    
//                 } else {
//                     cout << v.value;
//                     // cout << " is without the function call evaluation";

//                 }//end function evaluation
//             }
//         } //end inner-for
//         cout << endl;
//     }//end outer-for
// }

void printToConsoleIndividually(string line) {

    // for (string line: consoleOutputs) {
        // removeComments(line);

        findAndReplaceAll(line, "print(", "");
        vector<string> elements = split(line, ",");

        for (string substring: elements) {
          substring = houseCleaning(substring);
            if (substring.find(")") != string::npos) {
                /*Remove closing parenthesis from the end of vector*/
                findAndReplaceAll(substring, ")", "");
            }

            if (substring.find("\"") != string::npos) {
                /*cout the statement in quotes*/
                findAndReplaceAll(substring, "\"", "");
                cout << substring;
            } else {
                
                removeNewLinesAndTabs(substring);

                int variablePosition = findPreexisitingVariable(variableVector, substring);
                variables v = variableVector[variablePosition];
                removeComments(v.value);

                if (v.value.find("(") != string::npos) {

                    int functionPosition = findIfFunctionExists(get_str_between_two_str(v.value, "=", "("));

                    // cout << "single call: substring is " << substring << "." << endl;
                    printStringVector(functionsVector[functionPosition].functionBody);
                    // return;
                    v.value =  getValueAfterFunctionCall(functionsVector[functionPosition], v);
                    cout << v.value;

                    // cout << " is the value after function call evaluation";
                    
                } else {
                    cout << v.value;
                    // cout << " is without the function call evaluation";

                }//end function evaluation
            }
        } //end inner-for
        cout << endl;
    // }//end outer-for
}



/*Code credit to: https://gist.github.com/rajeshsubhankar/f6bba165781a86d34de0*/
bool isChar(string s)
{
     if(s.size() >1 ) return false;

     switch (s[0]) {
        case '+': return true;
        case '-': return true;
        case '*': return true;
        case '/': return true;
        case '(': return true;
        case ')': return true;
        case '^': return true;
        default: return false;
    }
}

int solve(int op1, int op2, char ch) {
     switch(ch) {
          case '+': return (op1+op2);
          case '-': return (op1-op2);
          case '*': return (op1*op2);
          case '/': return floor(op1/op2);
          case '^': return pow(op1,op2);

     }
}

int preference( char ch) {
     switch(ch) {
          case '+': return 1;
          case '-': return 1;
          case '*': return 2;
          case '/': return 2;
          case '^': return 3;
          case '(': return -1;
     }
}

int evaluate(string s1) {
     stack<char> operators;
     stack<int> operands;

     string s;
     istringstream is(s1);
     while(is>>s) {
          if(isChar(s)) {
               if(s[0]=='(') operators.push('(');
               else if(s[0]==')') {
                    while(operators.top()!='(') {
                         char ch=operators.top(); operators.pop();
                         int op2=operands.top(); operands.pop();
                         int op1=operands.top(); operands.pop();

                         operands.push(solve(op1,op2,ch));
                    }
                    operators.pop();
               }
               else {
                    while(!operators.empty() &&   preference(s[0]) <= preference(operators.top())) {
                         char ch=operators.top(); operators.pop();
                         int op2=operands.top(); operands.pop();
                         int op1=operands.top(); operands.pop();

                         operands.push(solve(op1,op2,ch));

                    }

                    operators.push(s[0]);
               }

          }
          else {
               int op=atoi(s.c_str());
               operands.push(op);
          }

     }

     while(!operators.empty()) {
          char ch=operators.top(); operators.pop();
          int op2=operands.top(); operands.pop();
          int op1=operands.top(); operands.pop();

          operands.push(solve(op1,op2,ch));
     }

     return operands.top();
}

void cleanFile(string fileName) {
  ifstream inFS(fileName.c_str());
  ofstream outFS("temp.py");
  string line;
  vector<string> contents;
  while(getline(inFS, line)) {
    contents.push_back(line);
  }

  for (int i = 0; i < contents.size(); i++) {
    // cout << "length: " << contents[i].length() << endl;
    if (contents[i] != "") {
      outFS << contents[i] << endl;
    } else {
      // cout << "empty line found\n";
      // cout << "i-1: " <<contents[i-1] << endl;
      // cout << "i+1: " <<contents[i+1] << endl;

      if (contents[i-1].find("return") != string::npos &&
      contents[i+1].find("def") != string::npos)  {
        outFS << endl;
      }
      if (contents[i-1].find("return") != string::npos &&
      contents[i+1].find("=") != string::npos) {
        outFS << endl;
        continue;
      }
    }
  }

  inFS.close();
  outFS.close();

  ifstream dupInFS("temp.py");
  ofstream dupOutFS(fileName.c_str());

  while (getline(dupInFS, line)) {
    dupOutFS << line << endl;
  }

  dupInFS.close();
  dupOutFS.close();
}