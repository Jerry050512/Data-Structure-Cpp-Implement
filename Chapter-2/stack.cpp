#include <iostream>

using namespace std;

template <typename T, size_t MAX_SIZE = 100>
class Stack
{
private:
    T data[MAX_SIZE];
    size_t top_index;

public:
    Stack() : top_index(0) {}

    bool isEmpty() const
    {
        return top_index == 0;
    }

    bool full() const
    {
        return top_index == MAX_SIZE;
    }

    size_t size() const
    {
        return top_index;
    }

    void push(const T &value)
    {
        if (full())
        {
            cout << "Error: Stack is full!" << endl;
            return;
        }
        data[top_index++] = value;
    }

    T &pop()
    {
        if (isEmpty())
        {
            cout << "Error: Stack is empty!" << endl;
            static T dummy;
            return dummy;
        }
        return data[--top_index];
    }

    T &top()
    {
        if (isEmpty())
        {
            cout << "Error: Stack is empty!" << endl;
            static T dummy;
            return dummy;
        }
        return data[top_index - 1];
    }

    const T &top() const
    {
        if (isEmpty())
        {
            cout << "Error: Stack is empty!" << endl;
            static T dummy;
            return dummy;
        }
        return data[top - 1];
    }

    void clear()
    {
        while(!isEmpty())
        {
            pop();
        }
    }

    void clear(bool output)
    {
        while(!isEmpty())
        {
            cout << pop() << "  ";
        }
        cout << endl;
    }
};

// int main()
// {
//     Stack<int> s;
//     cout << "Stack is empty: " << s.isEmpty() << endl;
//     s.push(1);
//     s.push(2);
//     s.push(3);
//     cout << "Top of s: " << s.top() << endl;
//     cout << "Pop s: " << s.pop() << endl;
//     s.clear(true);
//     cout << "Size of s: " << s.size() << endl;
//     while(!s.full()) s.push(1);
//     cout << s.size() << "  " << s.full() << endl;
// }