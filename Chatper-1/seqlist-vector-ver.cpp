#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

template <typename T>
class SequentialList
{
private:
    vector<T> list;

public:
    // Initialization
    SequentialList() {}

    // Constructor with initializer_list
    SequentialList(std::initializer_list<T> initList) : list(initList) {}

    // Insertion
    bool insert(int index, T elem)
    {
        if (index >= 0 && index <= getLength())
        {
            list.insert(list.begin() + index, elem);
            return true;
        }
        return false;
    }

    // Delete
    bool remove(int index)
    {
        if (index >= 0 && index < getLength())
        {
            list.erase(list.begin() + index);
            return true;
        }
        return false;
    }

    // Loop-through
    void display()
    {
        for (const auto &elem : list)
        {
            cout << elem << " ";
        }
        cout << endl;
    }

    // Clear
    void clear()
    {
        list.clear();
    }

    // Destroy
    void destroy()
    {
        list.~vector();
    }

    // Length
    int getLength()
    {
        return list.size();
    }

    // Empty check
    bool isEmpty()
    {
        return list.empty();
    }

    // Get the i-th element
    T get(int index)
    {
        if (index >= 0 && index < getLength())
        {
            return list[index];
        }
        throw out_of_range("Index out of range")
    }

    // Get the previous of i-th element
    T getPrev(int index)
    {
        if (index > 0 && index < getLength())
        {
            return list[index - 1];
        }
        return T(); // Return default value of T
    }

    // Get the next of i-th element
    T getNext(int index)
    {
        if (index >= 0 && index < getLength() - 1)
        {
            return list[index + 1];
        }
        return T(); // Return default value of T
    }
};

int main()
{
    SequentialList<int> sList {1, 2, 3};

    // Example usage
    sList.insert(0, 10);
    sList.insert(1, 20);
    sList.insert(2, 30);
    sList.display();

    cout << "Element at index 1: " << sList.get(1) << endl;
    cout << "Previous element of index 1: " << sList.getPrev(1) << endl;
    cout << "Next element of index 1: " << sList.getNext(1) << endl;

    sList.remove(1);
    sList.display(); 

    cout << "Is list empty? " << (sList.isEmpty() ? "Yes" : "No") << endl;

    sList.clear();
    cout << "Is list empty after clear? " << (sList.isEmpty() ? "Yes" : "No") << endl;

    // Note: The destroy function is not typically used as it's handled by the destructor.
    // sList.destroy(); // Use with caution, only if you know what you're doing.

    return 0;
}
