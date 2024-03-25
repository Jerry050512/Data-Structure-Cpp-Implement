#include <iostream>
#include "seqlist-array-ver.cpp"
#include "linklist.cpp"

using namespace std;

void seqlist_merge(int la[], int len_a, int lb[], int len_b, bool no_duplicate, bool ascending);
void linklist_merge(int la[], int len_a, int lb[], int len_b, bool no_duplicate, bool ascending);

int main()
{
    int la[] {1, 3, 4, 7, 7, 8, 9};
    int lb[] {2, 3, 6, 7, 7, 7, 10};
    seqlist_merge(la, 7, lb, 7, false, true);
    cout << "------------------------------" << endl;
    linklist_merge(la, 7, lb, 7, false, true);
    cout << "------------------------------" << endl;
    seqlist_merge(la, 7, lb, 7, true, true);
    cout << "------------------------------" << endl;
    linklist_merge(la, 7, lb, 7, true, true);
    cout << "------------------------------" << endl;
    seqlist_merge(la, 7, lb, 7, true, false);
    cout << "------------------------------" << endl;
    linklist_merge(la, 7, lb, 7, true, false);
}

void seqlist_merge(int la[], int len_a, int lb[], int len_b, bool no_duplicate, bool ascending)
{
    SequentialList<int> seqlist_a {la, len_a}, seqlist_b {lb, len_b};
    SequentialList<int> seqlist_c {len_a+len_b};
    int i=0, j=0;
    while(i<len_a && j<len_b)
    {
        if(no_duplicate)
        {
            while(i<len_a-1 && la[i]==la[i+1]) i++;
            while(j<len_b-1 && lb[j]==lb[j+1]) j++;
        }
        
        if(seqlist_a[i] < seqlist_b[j])
        {
            if(ascending)
                seqlist_c.append(seqlist_a[i++]);
            else
                seqlist_c.insert(0, seqlist_a[i++]);
        }
        else if(seqlist_a[i] > seqlist_b[j])
        {
            if(ascending)
                seqlist_c.append(seqlist_b[j++]);
            else
                seqlist_c.insert(0, seqlist_b[j++]);
        }
        else
        {
            if(no_duplicate)
                j++;
            if(ascending)
                seqlist_c.append(seqlist_a[i++]);
            else
                seqlist_c.insert(0, seqlist_a[i++]);
        }
    }
    while(i<len_a)
    {
        if(no_duplicate)
            while(i<len_a-1 && la[i]==la[i+1]) i++;
        if(ascending)
            seqlist_c.append(seqlist_a[i++]);
        else
            seqlist_c.insert(0, seqlist_a[i++]);
    }
    while(j<len_b)
    {
        if(no_duplicate)
            while(j<len_b-1 && lb[j]==lb[j+1]) j++;
        if(ascending)
            seqlist_c.append(seqlist_b[j++]);
        else
            seqlist_c.insert(0, seqlist_b[j++]);
    }
    seqlist_c.traverse();
}

void linklist_merge(int la[], int len_a, int lb[], int len_b, bool no_duplicate, bool ascending)
{
    SinglyLinkedList<int> linklist_a {la, len_a}, linklist_b {lb, len_b};
    SinglyLinkedList<int> linklist_c;
    auto i=linklist_a.begin(), j=linklist_b.begin();
    auto next_i=i->next, next_j=j->next;

    while(i!=linklist_a.end() && j!=linklist_b.end())
    {
        if (no_duplicate)
        {
            while (next_i != nullptr && i->data == next_i->data)
            {
                i++;
                next_i = i->next;
            }
            while (next_j != nullptr && j->data == next_j->data)
            {
                j++;
                next_j = j->next;
            }
        }
        if(*i<*j)
        {
            if(ascending)
                linklist_c.insertBackward(*i++);
            else
                linklist_c.insertForward(*i++);
        }
        else if (*i > *j)
        {    
            if(ascending)
                linklist_c.insertBackward(*j++);
            else
                linklist_c.insertForward(*j++);
        }
        else
        {
            if (no_duplicate)
                j++;
            if (ascending)
                linklist_c.insertBackward(*i++);
            else
                linklist_c.insertForward(*i++);
        }
        if(next_i!=nullptr)
            next_i = i->next;
        if(next_j!=nullptr)
            next_j = j->next;
        
    }
    while (i != linklist_a.end())
    {
        if (no_duplicate)
            while (i->next != nullptr && i->data == i->next->data)
                i++;
        if (ascending)
            linklist_c.insertBackward(*i++);
        else
            linklist_c.insertForward(*i++);
    }
    while (j != linklist_a.end())
    {
        if (no_duplicate)
            while (j->next != nullptr && j->data == j->next->data)
                j++;
        if (ascending)
            linklist_c.insertBackward(*j++);
        else
            linklist_c.insertForward(*j++);
    }
    linklist_c.display();
}