#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;
    vector<Edge> edges;

    int findParent(int x, vector<int>& parent) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = findParent(parent[x], parent);
    }

    void unionSets(int x, int y, vector<int>& parent, vector<int>& rank) {
        int xroot = findParent(x, parent);
        int yroot = findParent(y, parent);

        if (rank[xroot] < rank[yroot]) {
            parent[xroot] = yroot;
        } else if (rank[xroot] > rank[yroot]) {
            parent[yroot] = xroot;
        } else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }

public:
    Graph(int V) : V(V), adjMatrix(V, vector<int>(V, 0)) {}

    void addEdge(int u, int v, int w) {
        adjMatrix[u][v] = adjMatrix[v][u] = w;
        edges.emplace_back(u, v, w);
    }

    void kruskalMST() {
        vector<Edge> mst;

        // Sort the edges based on weight
        sort(edges.begin(), edges.end());

        // Create a parent and rank vector for Union-Find
        vector<int> parent(V);
        vector<int> rank(V, 0);
        for (int i = 0; i < V; i++) {
            parent[i] = i;
        }

        // Iterate through the sorted edges
        for (const Edge& edge : edges) {
            int x = findParent(edge.src, parent);
            int y = findParent(edge.dest, parent);

            if (x != y) {
                mst.push_back(edge);
                unionSets(x, y, parent, rank);
            }
        }

        printMST(mst);
    }

    void printMST(vector<Edge>& mst) {
        cout << "Edge \tWeight\n";
        int totalWeight = 0;
        for (const Edge& edge : mst) {
            cout << edge.src << " - " << edge.dest << "\t" << edge.weight << "\n";
            totalWeight += edge.weight;
        }
        cout << "Total Weight: " << totalWeight << "\n";
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

    g.kruskalMST();

    return 0;
}