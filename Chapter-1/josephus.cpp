#include "linklist.cpp"

int main()
{
    int m, n;
    cout << "按顺序输入总人数m与报数n: ";
    cin >> m >> n;

    SinglyLinkedLoopList<int> josephusRing;
    for(int i=1; i<=m; i++)
    {
        josephusRing.insert(i);
    }

    josephusRing.display();

    auto cur = josephusRing.getHead();

    while(josephusRing.getLength()>0)
    {
        for(int i=1; i<n-1; i++)
        {
            cur = cur->next;
        }
        cout << "要走的人是: " << cur->next->data << "号" << endl;
        josephusRing.removeNext(cur);
        cur = cur->next;
    }

    return 0;
}