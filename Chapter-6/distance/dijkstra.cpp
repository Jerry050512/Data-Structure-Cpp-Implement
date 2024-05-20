#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;

public:
    Graph(int V) : V(V), adjMatrix(V, vector<int>(V, 0)) {}

    void addEdge(int u, int v, int w) {
        adjMatrix[u][v] = adjMatrix[v][u] = w;
    }

    void dijkstra(int src) {
        vector<int> dist(V, INT_MAX);  // Vector to store shortest distances
        vector<bool> visited(V, false); // Vector to keep track of visited vertices

        // Create a priority queue to get the vertex with the minimum distance
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Start from the source vertex
        dist[src] = 0;
        pq.push(make_pair(0, src));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) {
                continue;
            }

            visited[u] = true;

            // Traverse all adjacent vertices
            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] && !visited[v] && dist[v] > dist[u] + adjMatrix[u][v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        // Print the shortest distances
        cout << "Vertex\tDistance from Source\n";
        for (int i = 0; i < V; i++) {
            cout << i << "\t" << dist[i] << "\n";
        }
    }
};

int main() {
    // int V, E;
    // cout << "Enter the number of vertices and edges: ";
    // cin >> V >> E;

    // Graph g(V);

    // cout << "Enter the edges (source, destination, weight):\n";
    // for (int i = 0; i < E; i++) {
    //     int src, dest, weight;
    //     cin >> src >> dest >> weight;
    //     g.addEdge(src, dest, weight);
    // }

    // int source;
    // cout << "Enter the source vertex: ";
    // cin >> source;

    int V = 5, source = 0;
    Graph g(V);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    g.dijkstra(source);

    return 0;
}