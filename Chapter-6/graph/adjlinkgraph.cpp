#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Node structure for linked list
struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

// Abstract base class
class Graph {
protected:
    int V; // Number of vertices
    vector<Node*> adj; // Adjacency list using linked lists

public:
    Graph(int numVertices) {
        V = numVertices;
        adj = vector<Node*>(V, nullptr);
    }

    virtual void addEdge(int src, int dest) = 0;
    virtual void removeEdge(int src, int dest) = 0;

    bool isEdge(int src, int dest) {
        Node* current = adj[src];
        while (current != nullptr) {
            if (current->data == dest)
                return true;
            current = current->next;
        }
        return false;
    }

    void printAdjList() {
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << ": ";
            Node* current = adj[i];
            while (current != nullptr) {
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        DFSUtil(start, visited);
        cout << endl;
    }

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";

            Node* current = adj[u];
            while (current != nullptr) {
                int neighbor = current->data;
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
                current = current->next;
            }
        }
        cout << endl;
    }

private:
    void DFSUtil(int start, vector<bool>& visited) {
        visited[start] = true;
        cout << start << " ";

        Node* current = adj[start];
        while (current != nullptr) {
            int neighbor = current->data;
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
            current = current->next;
        }
    }
};

// Derived class for undirected graph
class UndirectedGraph : public Graph {
public:
    UndirectedGraph(int numVertices) : Graph(numVertices) {}

    void addEdge(int src, int dest) override {
        Node* newNode = new Node(dest);
        newNode->next = adj[src];
        adj[src] = newNode;

        newNode = new Node(src);
        newNode->next = adj[dest];
        adj[dest] = newNode;
    }

    void removeEdge(int src, int dest) override {
        Node* current = adj[src], *prev = nullptr;
        while (current != nullptr) {
            if (current->data == dest) {
                if (prev == nullptr) {
                    adj[src] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                break;
            }
            prev = current;
            current = current->next;
        }

        current = adj[dest], prev = nullptr;
        while (current != nullptr) {
            if (current->data == src) {
                if (prev == nullptr) {
                    adj[dest] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                break;
            }
            prev = current;
            current = current->next;
        }
    }
};

// Derived class for directed graph
class DirectedGraph : public Graph {
public:
    DirectedGraph(int numVertices) : Graph(numVertices) {}

    void addEdge(int src, int dest) override {
        Node* newNode = new Node(dest);
        newNode->next = adj[src];
        adj[src] = newNode;
    }

    void removeEdge(int src, int dest) override {
        Node* current = adj[src], *prev = nullptr;
        while (current != nullptr) {
            if (current->data == dest) {
                if (prev == nullptr) {
                    adj[src] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                break;
            }
            prev = current;
            current = current->next;
        }
    }
};

int main() {
    int numVertices = 5;
    UndirectedGraph ug(numVertices);
    DirectedGraph dg(numVertices);

    // Undirected graph operations
    ug.addEdge(0, 1);
    ug.addEdge(0, 4);
    ug.addEdge(1, 2);
    ug.addEdge(1, 3);
    ug.addEdge(1, 4);
    ug.addEdge(2, 3);
    ug.addEdge(3, 4);

    cout << "Undirected Graph Adjacency List:" << endl;
    ug.printAdjList();
    cout << "DFS: " << endl;
    ug.DFS(0);
    cout << "BFS: " << endl;
    ug.BFS(0);

    // Directed graph operations
    dg.addEdge(0, 1);
    dg.addEdge(0, 4);
    dg.addEdge(1, 2);
    dg.addEdge(1, 3);
    dg.addEdge(1, 4);
    dg.addEdge(2, 3);
    dg.addEdge(3, 4);

    cout << "Directed Graph Adjacency List:" << endl;
    dg.printAdjList();
    cout << "DFS: " << endl;
    dg.DFS(0);
    cout << "BFS: " << endl;
    dg.BFS(0);

    return 0;
}