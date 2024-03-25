#include <iostream>
#include <initializer_list>

using namespace std;

template <typename T>
class SinglyLinkedList
{
private:
    struct Node
    {
        T data;
        Node* next;

        Node(T val) : data(val), next(nullptr) {}
    };

    Node *head;
    Node *tail;
    int length;

public:
    // Constructor
    SinglyLinkedList() : length(0)
    {
        head = new Node(T());
        tail = head;
    }

    SinglyLinkedList(T *data, int size) : length(0)
    {
        head = new Node(T());
        tail = head;

        for (int i = 0; i < size; i++)
        {
            insertBackward(data[i]);
        }
    }

    SinglyLinkedList(initializer_list<T> initList) : length(0)
    {
        head = new Node(T());
        tail = head;

        for (auto &val : initList)
        {
            insertBackward(val);
        }
    }

    // Destructor
    ~SinglyLinkedList()
    {
        clear();
        delete head;
    }

    // 迭代器类
    class iterator
    {
    private:
        Node *ptr; // 指向当前节点的指针
    public:
        iterator(Node *p = nullptr) : ptr(p) {}

        // 重载操作符
        T &operator*() { return ptr->data; } // 解引用
        Node *operator->() { return ptr; }   // 成员访问
        iterator &operator++()
        { // 前置++
            ptr = ptr->next;
            return *this;
        }
        iterator operator++(int)
        { // 后置++
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        bool operator==(const iterator &other) { return ptr == other.ptr; }
        bool operator!=(const iterator &other) { return ptr != other.ptr; }

        friend class SinglyLinkedList<T>; // 允许SinglyLinkedList访问iterator的私有成员
    };

    iterator begin() { return iterator(head->next); }
    iterator end() { return iterator(nullptr); }

    Node *getHead() const { return head; }
    int getLength() const { return length; }

    // Forward Insertion
    void insertForward(T value)
    {
        Node *newNode = new Node(value);
        newNode->next = head->next;
        head->next = newNode;
        if (tail == head)
        {
            tail = head->next;
        }
        length++;
    }

    // Backward Insertion
    void insertBackward(T value)
    {
        tail->next = new Node(value);
        tail = tail->next;
        length++;
    }

    bool insert(T value, int index)
    {
        if(index < 0) return false;
        if(index >= length)
        {
            insertBackward(value);
            return true;
        }
        Node *cur = head->next;
        for (int i = 0; i < index; i++)
        {
            cur = cur->next;
        }
        Node *newNode = new Node(value);
        newNode->next = cur->next;
        cur->next = newNode;
        length++;
        return true;
    }

    bool remove(int index)
    {
        if(index < 0 || index >= length) return false;
        Node *cur = head;
        for (int i = 0; i < index; i++)
        {
            cur = cur->next;
        }
        Node *temp = cur->next;
        cur->next = temp->next;
        delete temp;
        length--;
        return true;
    }

    bool has(T value)
    {
        Node *cur = head->next;
        while (cur != nullptr)
        {
            if (cur->data == value)
            {
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    int getLength()
    {
        return length;
    }

    // Display the list
    void display() const
    {
        Node *current = head->next;
        while (current != nullptr)
        {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "null" << endl;
    }

    // Clear the list
    void clear()
    {
        Node *curr = head->next;
        while (curr != nullptr)
        {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
        head->next = nullptr;
        tail = head;
    }

    int get(int index)
    {
        if (index < 0 || index >= length)
            return T();
        Node *cur = head->next;
        for (int i = 0; i < index; i++)
        {
            cur = cur->next;
        }
        return cur->data;
    }
};

template <typename T>
class DoublyLinkedList
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node *prev;

        Node(T val) : data(val), next(nullptr), prev(nullptr) {}
    };

    Node *head;
    Node *tail;
    int length;

public:
    // Constructor
    DoublyLinkedList() : length(0)
    {
        head = new Node(T());
        tail = head;
    }

    DoublyLinkedList(initializer_list<T> initList) : length(0)
    {
        head = new Node(T());
        tail = head;

        for (auto &val : initList)
        {
            insertBackward(val);
        }
    }

    // Destructor
    ~DoublyLinkedList()
    {
        clear();
        delete head;
    }

    Node *getHead() const { return head; }
    int getLength() const { return length; }

    // Forward Insertion
    void insertForward(T value)
    {
        Node *newNode = new Node(value);
        newNode->next = head->next;
        newNode->prev = head;
        head->next = newNode;
        if (tail == head)
        {
            tail = head->next;
        }
        length++;
    }

    // Backward Insertion
    void insertBackward(T value)
    {
        tail->next = new Node(value);
        tail->next->prev = tail;
        tail = tail->next;
        length++;
    }

    bool insert(T value, int index)
    {
        if (index < 0)
            return false;
        if (index >= length)
        {
            insertBackward(value);
            return true;
        }
        Node *cur = head->next;
        for (int i = 0; i < index; i++)
        {
            cur = cur->next;
        }
        Node *newNode = new Node(value);
        newNode->next = cur->next;
        newNode->next->prev = newNode;
        newNode->prev = cur;
        cur->next = newNode;
        length++;
        return true;
    }

    bool remove(int index)
    {
        if (index < 0 || index >= length)
            return false;
        Node *cur = head;
        for (int i = 0; i < index; i++)
        {
            cur = cur->next;
        }
        Node *temp = cur->next;
        if (temp == tail)
        {
            tail = cur;
            cur->next = nullptr;
            delete temp;
            length--;
            return true;
        }
        cur->next = temp->next;
        temp->next->prev = cur;
        delete temp;
        length--;
        return true;
    }

    int getLength()
    {
        return length;
    }

    // Display the list
    void display() const
    {
        Node *current = head->next;
        while (current != nullptr)
        {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "null" << endl;
    }

    void backTranverse()
    {
        Node *current = tail;
        while(current != head)
        {
            cout << current->data << " -> ";
            current = current->prev;
        }
        cout << "head" << endl;
    }

    // Clear the list
    void clear()
    {
        Node *curr = head->next;
        while (curr != nullptr)
        {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
        head->next = nullptr;
        tail = head;
    }

    int get(int index)
    {
        if (index < 0 || index >= length)
            return T();
        Node *cur = head->next;
        for (int i = 0; i < index; i++)
        {
            cur = cur->next;
        }
        return cur->data;
    }
};

template <typename T>
class SinglyLinkedLoopList
{
private:
    struct Node
    {
        T data;
        Node *next;

        Node(T value) : data(value), next(nullptr) {}
    };

    Node *head;
    int length;

public:
    SinglyLinkedLoopList() : head(nullptr), length(0) {}
    SinglyLinkedLoopList(initializer_list<T> initList) : head(nullptr), length(0)
    {
        for(auto &val : initList)
        {
            insert(val);
        }
    }

    ~SinglyLinkedLoopList()
    {
        Node *curr = head;
        while (curr != nullptr)
        {
            Node *next = curr->next;
            delete curr;
            curr = (next == head) ? nullptr : next;
        }
    }

    Node* getHead() const { return head; }
    int getLength() const { return length; }

    void insert(T value)
    {
        Node *newNode = new Node(value);
        if (head == nullptr)
        {
            head = newNode;
            newNode->next = head;
        }
        else
        {
            Node *curr = head;
            while (curr->next != head)
            {
                curr = curr->next;
            }
            curr->next = newNode;
            newNode->next = head;
        }
        length++;
    }

    bool remove(int index)
    {
        if(index < 0 || length == 0) return false;
        Node *curr = head;
        Node *prev = nullptr;

        for(int i = 0; i < index; i++)
        {
            prev = curr;
            curr = curr->next;
        }

        if(curr == head)
        {
            if(length == 1)
            {
                head = nullptr;
                delete curr;
                length--;
                return true;
            }
            head = head->next;
        }

        prev->next = curr->next;
        delete curr;
        length--;
        return true;
    }

    void removeNext(Node *node)
    {
        if(node->next == head)
        {
            if(length == 1)
            {
                head = nullptr;
                delete node->next;
                length--;
                return;
            }
            head = head->next;
        }
        Node *next = node->next;
        node->next = next->next;
        delete next;
        length--;
    }

    void display()
    {
        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }

        Node *curr = head;
        do
        {
            cout << curr->data << "-> ";
            curr = curr->next;
        } while (curr != head);
        cout << "loop" << endl;
    }
};

// int main()
// {
//     SinglyLinkedList<int> linkedList {1, 2, 3};

//     // Forward insertion
//     linkedList.insertForward(3);
//     linkedList.insertForward(2);
//     linkedList.insertForward(1);

//     // Backward insertion
//     linkedList.insertBackward(4);
//     linkedList.insertBackward(5);

//     linkedList.remove(2);

//     cout << "The 2rd element is: " << linkedList.get(2) << endl;
//     cout << "The length of the list is: " << linkedList.getLength() << endl;

//     // Display the list
//     linkedList.display(); // Output: 1 -> 2 -> 3 -> 1 -> 2 -> 3 -> 4 -> 5 -> null

//     cout << "----------------------------" << endl;

//     DoublyLinkedList<int> doublyLinkedList {1, 2, 3};
//     doublyLinkedList.remove(2);
//     doublyLinkedList.backTranverse();

//     cout << "----------------------------" << endl;

//     SinglyLinkedLoopList<int> singlyLinkedLoopList{1, 2, 3};
//     singlyLinkedLoopList.display();
//     singlyLinkedLoopList.remove(2);
//     singlyLinkedLoopList.display();
//     singlyLinkedLoopList.remove(2);
//     singlyLinkedLoopList.display();
//     singlyLinkedLoopList.remove(2);
//     singlyLinkedLoopList.display();

//     return 0;
// }
