#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

using namespace std;

// Node structure for the adjacency list
struct Node {
    int vertex;
    int weight;
    Node* next;
    Node(int v, int w) : vertex(v), weight(w), next(nullptr) {}
};

// Graph class
class Graph {
private:
    int V;
    unordered_map<int, Node*> adjList;

    void topologicalSortUtil(int v, vector<bool>& visited, vector<int>& order) {
        visited[v] = true;

        // Traverse all adjacent vertices
        Node* temp = adjList[v];
        while (temp != nullptr) {
            int adj = temp->vertex;
            if (!visited[adj]) {
                topologicalSortUtil(adj, visited, order);
            }
            temp = temp->next;
        }

        // Push the current vertex to the order after all its dependencies are visited
        order.push_back(v);
    }

public:
    Graph(int V) : V(V) {}

    void addEdge(int u, int v, int w) {
        Node* newNode = new Node(v, w);
        newNode->next = adjList[u];
        adjList[u] = newNode;
    }

    void criticalPath() {
        vector<bool> visited(V, false);
        vector<int> order;

        // Perform topological sort
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, order);
            }
        }

        // Calculate earliest and latest start times
        vector<int> earliest(V, 0);
        vector<int> latest(V, 0);

        for (int i = 0; i < order.size(); i++) {
            int u = order[i];
            Node* temp = adjList[u];
            earliest[u] = (i == 0) ? 0 : INT_MIN;

            while (temp != nullptr) {
                int v = temp->vertex;
                int w = temp->weight;
                earliest[u] = max(earliest[u], earliest[v] + w);
                temp = temp->next;
            }
        }

        latest[order.back()] = earliest[order.back()];

        for (int i = order.size() - 2; i >= 0; i--) {
            int u = order[i];
            Node* temp = adjList[u];
            latest[u] = INT_MAX;

            while (temp != nullptr) {
                int v = temp->vertex;
                int w = temp->weight;
                latest[u] = min(latest[u], latest[v] - w);
                temp = temp->next;
            }
        }

        // Print critical paths
        cout << "Critical Paths:\n";
        for (int i = 0; i < V; i++) {
            Node* temp = adjList[i];
            while (temp != nullptr) {
                int v = temp->vertex;
                int w = temp->weight;
                if (earliest[i] + w == latest[v]) {
                    cout << i << " -> " << v << " (weight: " << w << ")\n";
                }
                temp = temp->next;
            }
        }
    }
};

int main() {
    int V = 5;
    Graph g(V);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    g.criticalPath();

    return 0;
}