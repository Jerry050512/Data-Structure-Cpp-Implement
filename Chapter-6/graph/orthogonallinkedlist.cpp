#include <iostream>
#include <vector>

using namespace std;

// Node structure for linked list
struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

class Graph {
private:
    int V; // Number of vertices
    vector<Node*> row; // Row representations (linked lists)
    vector<Node*> col; // Column representations (linked lists)

public:
    Graph(int numVertices) {
        V = numVertices;
        row = vector<Node*>(V, nullptr);
        col = vector<Node*>(V, nullptr);
    }

    void addEdge(int src, int dest) {
        // Add edge to row list
        Node* newNode = new Node(dest);
        newNode->next = row[src];
        if (row[src]) {
            row[src]->prev = newNode;
        }
        row[src] = newNode;

        // Add edge to column list
        newNode = new Node(src);
        newNode->next = col[dest];
        if (col[dest]) {
            col[dest]->prev = newNode;
        }
        col[dest] = newNode;
    }

    void removeEdge(int src, int dest) {
        // Remove edge from row list
        Node* current = row[src];
        Node* prev = nullptr;
        while (current != nullptr && current->data != dest) {
            prev = current;
            current = current->next;
        }
        if (current != nullptr) {
            if (prev != nullptr) {
                prev->next = current->next;
                if (current->next) {
                    current->next->prev = prev;
                }
            } else {
                row[src] = current->next;
                if (current->next) {
                    current->next->prev = nullptr;
                }
            }
            delete current;
        }

        // Remove edge from column list
        current = col[dest];
        prev = nullptr;
        while (current != nullptr && current->data != src) {
            prev = current;
            current = current->next;
        }
        if (current != nullptr) {
            if (prev != nullptr) {
                prev->next = current->next;
                if (current->next) {
                    current->next->prev = prev;
                }
            } else {
                col[dest] = current->next;
                if (current->next) {
                    current->next->prev = nullptr;
                }
            }
            delete current;
        }
    }

    bool isEdge(int src, int dest) {
        Node* current = row[src];
        while (current != nullptr) {
            if (current->data == dest) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void printAdjList() {
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << ": ";
            Node* current = row[i];
            while (current != nullptr) {
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        }
    }
};

int main() {
    int numVertices = 5;
    Graph g(numVertices);

    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    cout << "Adjacency List:" << endl;
    g.printAdjList();

    cout << "Is there an edge between 0 and 1? " << g.isEdge(0, 1) << endl;
    cout << "Is there an edge between 2 and 4? " << g.isEdge(2, 4) << endl;

    g.removeEdge(1, 4);

    cout << "After removing edge (1, 4):" << endl;
    g.printAdjList();

    return 0;
}