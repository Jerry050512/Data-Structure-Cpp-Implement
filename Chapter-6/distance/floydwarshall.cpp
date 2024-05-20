#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;

public:
    Graph(int V) : V(V), adjMatrix(V, vector<int>(V, INT_MAX)) {
        for (int i = 0; i < V; i++) {
            adjMatrix[i][i] = 0; // Set diagonal elements to 0
        }
    }

    void addEdge(int u, int v, int w) {
        adjMatrix[u][v] = adjMatrix[v][u] = w;
    }

    void floydWarshall() {
        vector<vector<int>> dist(adjMatrix); // Initialize distances with adjMatrix

        // Apply Floyd-Warshall algorithm
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        // Print the shortest distances
        cout << "Shortest distances between all pairs of vertices:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] == INT_MAX) {
                    cout << "INF ";
                } else {
                    cout << dist[i][j] << " ";
                }
            }
            cout << "\n";
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
    g.floydWarshall();

    return 0;
}