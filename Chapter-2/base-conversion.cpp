#include <iostream>
#include <stack>
#include <cmath>
#include <cctype>    // For isdigit() and toupper()
#include "stack.cpp"

using namespace std;

// Function to convert a decimal number to any base
string decimalToBase(int decimal, int base)
{
    Stack<int> stack;                        // Create an instance of the Stack class
    string digits = "0123456789ABCDEF"; // Digits for bases up to 16
    string result;

    while (decimal > 0)
    {
        stack.push(decimal % base); // Push the remainder onto the stack
        decimal /= base;            // Update the quotient
    }

    while (!stack.isEmpty())
    {
        int digit = stack.pop(); // Pop the digit from the stack
        result += digits[digit]; // Append the corresponding digit to the result
    }

    return result;
}

// Function to convert a number from any base to decimal
int baseToDecimal(string number, int base)
{
    Stack<int> stack; // Create an instance of the Stack class
    int decimal = 0;
    int power = 0;

    // Push the digits onto the stack
    for (int i=0; i<number.length(); i++)
    {
        char c = toupper(number[i]); // Convert to uppercase
        if (isdigit(c))
        {
            if(c - '0' >= base)
            {
                cout << "Invalid digit: " << c << endl;
                return -1;
            }
            stack.push(c - '0'); // Convert the digit character to an integer
        }
        else
        {
            if(c - 'A' + 10 >= base)
            {
                cout << "Invalid digit: " << c << endl;
                return -1;
            }
            stack.push(c - 'A' + 10); // Convert the letter character to an integer
        }
    }

    while (!stack.isEmpty())
    {
        int digit = stack.pop();             // Pop the digit from the stack
        decimal += digit * pow(base, power); // Calculate the decimal value
        power++;
    }

    return decimal;
}

// Function to convert a number from any base to any base
string baseToBase(string number, int fromBase, int toBase)
{
    if(fromBase == 10)
    {
        string validChars = "0123456789";
        for (char c : number)
        {
            char uc = toupper(c); // Convert to uppercase
            if (validChars.find(uc) == string::npos)
            {
                cout << "Invalid character '" << c << "' for base " << toBase << endl;
                return ""; // Return "" to indicate invalid input
            }
        }
        return decimalToBase(stoi(number), toBase); // If the input base is 10, call the decimalToBase function directly
    }
    if(toBase == 10)
    {
        return to_string(baseToDecimal(number, fromBase)); // If the output base is 10, call the baseToDecimal function directly
    }
    int decimal = baseToDecimal(number, fromBase); // Convert to decimal
    return decimalToBase(decimal, toBase);         // Convert from decimal to target base
}

int main()
{
    string number;
    int fromBase, toBase;

    cout << "Enter a number: ";
    cin >> number;

    cout << "Enter the base of the input number (2-16): ";
    cin >> fromBase;

    cout << "Enter the base to convert to (2-16): ";
    cin >> toBase;

    string result = baseToBase(number, fromBase, toBase);
    cout << "The number in base " << toBase << " is: " << result << endl;

    return 0;
}