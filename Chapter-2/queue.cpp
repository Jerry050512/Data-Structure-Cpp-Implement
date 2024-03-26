#include <iostream>

using namespace std;

template <typename T, size_t CAPACITY = 100>
class Queue
{
private:
    T *arr;
    int front, rear;
    size_t size, capacity;

public:
    Queue()
    {
        capacity = CAPACITY;
        arr = new T[capacity];
        front = rear = -1;
        size = 0;
    }

    ~Queue()
    {
        delete[] arr;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    bool isFull()
    {
        return size == capacity;
    }

    void enqueue(T x)
    {
        if (isFull())
        {
            cout << "Queue is full" << endl;
            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = x;
        if (front == -1)
            front = 0;
        size++;
    }

    T dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return -1;
        }
        T x = arr[front];
        if (front == rear)
        {
            front = rear = -1;
        }
        else
        {
            front = (front + 1) % capacity;
        }
        size--;
        return x;
    }

    T getFront()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return -1;
        }
        return arr[front];
    }

    T getRear()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return -1;
        }
        return arr[rear];
    }
};

// int main()
// {
//     Queue<int> q;
//     q.enqueue(1);
//     q.enqueue(2);
//     q.enqueue(3);
//     q.enqueue(4);
//     q.enqueue(5);

//     cout << "Front: " << q.getFront() << endl;
//     cout << "Rear: " << q.getRear() << endl;

//     q.dequeue();
//     q.dequeue();

//     q.enqueue(6);
//     q.enqueue(7);

//     cout << "Front: " << q.getFront() << endl;
//     cout << "Rear: " << q.getRear() << endl;
//     cout << "Dequeue: " << q.dequeue() << endl;
//     cout << "Dequeue: " << q.dequeue() << endl;
//     cout << "Dequeue: " << q.dequeue() << endl;
//     while(q.isEmpty() == false)
//     {
//         cout << "Dequeue: " << q.dequeue() << endl;
//     }
//     q.dequeue();

//     return 0;
// }