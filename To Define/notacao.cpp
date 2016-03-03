#include <stdio.h>
#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
    string line;

    while(!(getline(cin,line)).eof()) {
        stack < int > testStack;
        bool foundError = false, divBy0 = false;

        for (int i = line.size()-1; i >= 0; i--) {
            if (!isspace(line[i])) {
                if (isdigit(line[i]))
                    testStack.push(line[i] - '0'); // line[i] - '0' é apenas a conversão do caractere na posição i para int
                else {
                    if (testStack.size() < 2) {
                        printf("Invalid expression.\n");
                        foundError = true;
                        break;
                    }
                    else if (line[i] == '/' && testStack.top() == 0) {
                        divBy0 = true;
                        testStack.pop();
                    }
                    else {
                        int x = testStack.top();
                        testStack.pop();
                        int y = testStack.top();
                        testStack.pop();
                        int result;
                        if (line[i] == '/')
                            result = y / x;
                        else if (line[i] == '*')
                            result = y * x;
                        else if (line[i] == '+')
                            result = y + x;
                        else
                            result = y - x;

                        testStack.push(result);
                    }
                }
            }
        }

        if (!foundError && testStack.size() != 1)
            printf("Invalid expression.\n");
        else if (!foundError && divBy0)
            printf("Division by zero.\n");
        else if (!foundError)
            printf("The answer is %d.\n", testStack.top());
    }

    return 0;
}
