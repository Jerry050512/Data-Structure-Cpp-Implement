#include <iostream>
#include <stack>
#include <string>
#include "stack.cpp" // Include the file containing the Stack class

using namespace std;

bool isParenthesesMatched(string expression)
{
    Stack<char> stack; // Create an instance of the Stack class

    for (char c : expression)
    {
        if (c == '(' || c == '[' || c == '{')
        {
            stack.push(c); // Push the opening parenthesis onto the stack
        }
        else if (c == ')' || c == ']' || c == '}')
        {
            if (stack.isEmpty())
            {
                // No matching opening parenthesis found
                return false;
            }

            char top = stack.pop();

            if ((c == ')' && top != '(') || (c == ']' && top != '[') || (c == '}' && top != '{'))
            {
                // Mismatched parentheses
                return false;
            }
        }
    }

    // If the stack is empty, all parentheses are matched
    return stack.isEmpty();
}

int main()
{
    string expression;
    cout << "Enter an expression: ";
    getline(cin, expression);

    if (isParenthesesMatched(expression))
    {
        cout << "Parentheses are matched." << endl;
    }
    else
    {
        cout << "Parentheses are not matched." << endl;
    }

    return 0;
}