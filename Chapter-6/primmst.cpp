#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Graph {
private:
    int V; // Number of vertices
    vector<vector<int>> adjMatrix;

public:
    Graph(int V) : V(V), adjMatrix(V, vector<int>(V, 0)) {}

    void addEdge(int u, int v, int w) {
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w; // For undirected graph
    }

    int minKey(vector<int>& key, vector<bool>& mstSet) {
        int min = INT_MAX, min_index;

        for (int v = 0; v < V; v++) {
            if (mstSet[v] == false && key[v] < min) {
                min = key[v], min_index = v;
            }
        }

        return min_index;
    }

    void primMST() {
        vector<int> parent(V, -1); // Array to store constructed MST
        vector<int> key(V, INT_MAX); // Key values used to pick minimum weight edge in cut
        vector<bool> mstSet(V, false); // To represent set of vertices not yet included in MST

        key[0] = 0; // Make key 0 so that this vertex is picked as first vertex
        parent[0] = -1; // First node is always root of MST

        for (int count = 0; count < V - 1; count++) {
            int u = minKey(key, mstSet);

            mstSet[u] = true;

            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] && mstSet[v] == false && adjMatrix[u][v] < key[v]) {
                    parent[v] = u, key[v] = adjMatrix[u][v];
                }
            }
        }

        printMST(parent);
    }

    void printMST(vector<int>& parent) {
        cout << "Edge \tWeight\n";
        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - " << i << " \t" << adjMatrix[i][parent[i]] << " \n";
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

    g.primMST();

    return 0;
}
