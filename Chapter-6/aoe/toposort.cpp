#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// Node structure for the adjacency list
struct Node {
    int vertex;
    Node* next;
    Node(int v) : vertex(v), next(nullptr) {}
};

// Graph class
class Graph {
private:
    int V;
    unordered_map<int, Node*> adjList;

    void topologicalSortUtil(int v, vector<bool>& visited, vector<int>& result) {
        visited[v] = true;

        // Traverse all adjacent vertices
        Node* temp = adjList[v];
        while (temp != nullptr) {
            int adj = temp->vertex;
            if (!visited[adj]) {
                topologicalSortUtil(adj, visited, result);
            }
            temp = temp->next;
        }

        // Push the current vertex to the result after all its dependencies are visited
        result.push_back(v);
    }

public:
    Graph(int V) : V(V) {}

    void addEdge(int u, int v) {
        Node* newNode = new Node(v);
        newNode->next = adjList[u];
        adjList[u] = newNode;
    }

    void topologicalSort() {
        vector<bool> visited(V, false);
        vector<int> result;

        // Call the recursive helper function for all unvisited vertices
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, result);
            }
        }

        // Print the topological order
        cout << "Topological Sort:\n";
        for (int i = result.size() - 1; i >= 0; i--) {
            cout << result[i] << " ";
        }
        cout << "\n";
    }
};

int main() {
    int V = 5;
    Graph g(V);
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 4);

    g.topologicalSort();

    return 0;
}