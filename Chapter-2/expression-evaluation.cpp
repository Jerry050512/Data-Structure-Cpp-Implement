#include <iostream>
#include <string>
#include <cctype>
#include <unordered_map>
#include "stack.cpp" // Include the file containing the Stack class

using namespace std;

unordered_map<char, int> opPrecedence = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
    {'%', 2}
};

int applyOperation(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '%':
        return a % b;
    }
    return 0; // Should never reach here
}

int evaluateExpression(string expression)
{
    Stack<int> values; // Stack to store operands
    Stack<char> ops;   // Stack to store operators

    for (char c : expression)
    {
        if (isdigit(c))
        {
            values.push(c - '0'); // Push the operand onto the values stack
        }
        else if (c == '(')
        {
            ops.push(c); // Push the opening parenthesis onto the ops stack
        }
        else if (c == ')')
        {
            // Evaluate the sub-expression inside the parentheses
            while (!ops.isEmpty() && ops.top() != '(')
            {
                int b = values.pop();
                int a = values.pop();
                char op = ops.pop();
                values.push(applyOperation(a, b, op));
            }
            if (!ops.isEmpty())
            {
                ops.pop(); // Pop the opening parenthesis from the ops stack
            }
        }
        else if (opPrecedence.count(c))
        {
            // Process the operator
            while (!ops.isEmpty() && opPrecedence.count(ops.top()) && opPrecedence[ops.top()] >= opPrecedence[c])
            {
                int b = values.pop();
                int a = values.pop();
                char op = ops.pop();
                values.push(applyOperation(a, b, op));
            }
            ops.push(c); // Push the current operator onto the ops stack
        }
    }

    // Evaluate any remaining operators
    while (!ops.isEmpty())
    {
        int b = values.pop();
        int a = values.pop();
        char op = ops.pop();
        values.push(applyOperation(a, b, op));
    }

    return values.pop(); // The final result is on the top of the values stack
}

int main()
{
    string expression;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);

    int result = evaluateExpression(expression);
    cout << "Result: " << result << endl;

    return 0;
}