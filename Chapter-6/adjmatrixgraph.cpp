#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Abstract base class
class Graph {
protected:
    int V; // Number of vertices
    vector<vector<bool>> adj; // Adjacency matrix

public:
    Graph(int numVertices) {
        V = numVertices;
        adj = vector<vector<bool>>(V, vector<bool>(V, 0));
    }

    virtual void addEdge(int src, int dest) = 0;
    virtual void removeEdge(int src, int dest) = 0;
    bool isEdge(int src, int dest) {
        return adj[src][dest] == 1;
    }

    void printAdjMatrix() {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << adj[i][j] << " ";
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

            for (int i = 0; i < V; i++) {
                if (adj[u][i] && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }

private:
    void DFSUtil(int start, vector<bool>& visited) {
        visited[start] = true;
        cout << start << " ";

        // Recursive call for all unvisited neighbors
        for (int i = 0; i < V; i++) {
            if (adj[start][i] && !visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }
};

// Derived class for undirected graph
class UndirectedGraph : public Graph {
public:
    UndirectedGraph(int numVertices) : Graph(numVertices) {}

    void addEdge(int src, int dest) override {
        adj[src][dest] = 1;
        adj[dest][src] = 1;
    }

    void removeEdge(int src, int dest) override {
        adj[src][dest] = 0;
        adj[dest][src] = 0;
    }
};

// Derived class for directed graph
class DirectedGraph : public Graph {
public:
    DirectedGraph(int numVertices) : Graph(numVertices) {}

    void addEdge(int src, int dest) override {
        adj[src][dest] = 1;
    }

    void removeEdge(int src, int dest) override {
        adj[src][dest] = 0;
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

    cout << "Undirected Graph Adjacency Matrix:" << endl;
    ug.printAdjMatrix();
    cout << "DFS: " << endl;
    ug.DFS(2);
    cout << "BFS: " << endl;
    ug.BFS(2);

    // Directed graph operations
    dg.addEdge(0, 1);
    dg.addEdge(0, 4);
    dg.addEdge(1, 2);
    dg.addEdge(1, 3);
    dg.addEdge(1, 4);
    dg.addEdge(2, 3);
    dg.addEdge(3, 4);

    cout << "Directed Graph Adjacency Matrix:" << endl;
    dg.printAdjMatrix();

    cout << "DFS: " << endl;
    dg.DFS(0);
    cout << "BFS: " << endl;
    dg.BFS(0);

    return 0;
}