#include <iostream>
using namespace std;

template <typename T>
class SequentialList
{
private:
    T *list;
    int capacity;
    int length;

public:
    // Constructor to initialize the list
    SequentialList(int size)
    {
        capacity = size;
        list = new int[capacity];
        length = 0;
    }

    // Constructor to initialize the list with given data
    SequentialList(T *data, int size) : capacity(size), length(size)
    {
        list = new T[capacity];
        for (int i = 0; i < size; ++i)
        {
            list[i] = data[i];
        }
    }

    // Destructor to destroy the list
    ~SequentialList()
    {
        delete[] list;
    }

    using iterator = T *;

    iterator begin()
    {
        return list;
    }

    iterator end()
    {
        return list+length;
    }

    T& operator[](int index)
    {
        if(index < 0 || index >= length)
        {
            throw "Index out of range";
        }
        return list[index];
    }

    // Resize
    void resize(int size)
    {
        if (size <= capacity)
            return;
        T *temp = new T[size];
        for (int i = 0; i < length; i++)
        {
            temp[i] = list[i];
        }
        delete[] list;
        list = temp;
        capacity = size;
    }

    // Function to insert an element at a specified position
    bool insert(int index, T element)
    {
        if (index < 0 || index > length || length == capacity)
            return false;
        for (int i = length; i > index; --i)
        {
            list[i] = list[i - 1];
        }
        list[index] = element;
        length++;
        return true;
    }

    bool append(T element)
    {
        return insert(length, element);
    }

    // Function to delete an element at a specified position
    bool remove(int index)
    {
        if (index < 0 || index >= length)
            return false;
        for (int i = index; i < length - 1; ++i)
        {
            list[i] = list[i + 1];
        }
        --length;
        return true;
    }

    bool has(T element)
    {
        for (int i = 0; i < length; i++)
        {
            if (list[i] == element)
                return true;
        }
        return false;
    }

    // Function to get the length of the list
    int getLength()
    {
        return length;
    }

    // Function to check if the list is empty
    bool isEmpty()
    {
        return length == 0;
    }

    // Function to clear the list
    void clear()
    {
        length = 0;
    }

    // Function to get the i-th element of the list
    T get(int index)
    {
        if (index < 0 || index >= length)
            throw out_of_range("Index out of range");
        return list[index];
    }

    // Function to get the previous element of the i-th element
    T getPrev(int index)
    {
        if (index <= 0 || index >= length)
            throw out_of_range("Index out of range");
        return list[index - 1];
    }

    // Function to get the next element of the i-th element
    T getNext(int index)
    {
        if (index < 0 || index >= length - 1)
            throw out_of_range("Index out of range");
        return list[index + 1];
    }

    // Function to loop through the list
    void traverse()
    {
        for (int i = 0; i < length; ++i)
        {
            cout << list[i] << " ";
        }
        cout << endl;
    }
};

// // Example usage
// int main()
// {
//     SequentialList sList(10);                         // Initialize list with capacity 10
//     sList.insert(0, 5);                               // Insert 5 at position 0
//     sList.insert(1, 10);                              // Insert 10 at position 1
//     sList.traverse();                                 // Output: 5 10
//     cout << "Length: " << sList.getLength() << endl;  // Output: Length: 2
//     cout << "Element at 1: " << sList.get(1) << endl; // Output: Element at 1: 10
//     sList.remove(0);                                  // Remove element at position 0
//     sList.traverse();                                 // Output: 10
//     return 0;
// }
