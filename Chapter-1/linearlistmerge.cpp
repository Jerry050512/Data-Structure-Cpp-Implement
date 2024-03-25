#include <iostream>
#include "seqlist-array-ver.cpp"
#include "linklist.cpp"

using namespace std;

void seqlist_merge(int *, int, int*, int);
void linklist_merge(int *, int, int*, int);

int main()
{
    int a[] {1, 2, 3, 4}, b[] {4, 5, 6, 7};
    seqlist_merge(a, 4, b, 4);
    cout << "--------------------------" << endl;
    linklist_merge(a, 4, b, 4);
    return 0;
}

void seqlist_merge(int a[], int a_size, int b[], int b_size)
{
    SequentialList<int> seqlist_a(a, a_size), seqlist_b(b, b_size);
    seqlist_a.resize(a_size + b_size);

    for(auto &i : seqlist_b)
    {
        if(seqlist_a.has(i)) continue;
        seqlist_a.append(i);
    }

    seqlist_a.traverse();
}

void linklist_merge(int a[], int a_size, int b[], int b_size)
{
    SinglyLinkedList<int> linklist_a {a, a_size}, linklist_b {b, b_size};
    for(auto &i : linklist_b)
    {
        if(linklist_a.has(i)) continue;
        linklist_a.insertBackward(i);
    }

    linklist_a.display();
}