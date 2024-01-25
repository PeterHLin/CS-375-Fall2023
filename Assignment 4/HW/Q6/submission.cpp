#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool isBipartite(vector<vector<int > >& graph, int v, vector<int>& color) {
    queue<int> q;
    q.push(v);
    color[v] = 1; // Color the first vertex as 1

    while (!q.empty()) {
        int vertex = q.front();
        q.pop();

        for (int neighbor : graph[vertex]) {
            if (color[neighbor] == -1) { // If not colored
                color[neighbor] = 1 - color[vertex]; // Color with opposite color
                q.push(neighbor);
            } else if (color[neighbor] == color[vertex]) { // If same color
                return false; // Graph is not bipartite
            }
        }
    }
    return true;
}

int main() {
    vector<vector<int>> graph = {
            {1, 2},   // Vertex 0 is connected to Vertex 1 and 2
            {0, 2, 3},
            {0, 1},
            {1, 4},
            {3, 5, 7},
            {4, 6},
            {5, 9},
            {4, 8, 10},
            {7, 10},
            {6},
            {7, 8}
    };

    int n = graph.size();
    vector<int> color(n, -1); // -1 means no color, 0 and 1 are the two colors

    for (int i = 0; i < n; ++i) {
        if (color[i] == -1) {
            if (!isBipartite(graph, i, color)) {
                cout << "The graph is not bipartite." << endl;
                return 0;
            }
        }
    }

    // Printing the two sets
    cout << "Set V1: ";
    for (int i = 0; i < n; ++i)
        if (color[i] == 0) cout << i+1 << " ";
    cout << endl;

    cout << "Set V2: ";
    for (int i = 0; i < n; ++i)
        if (color[i] == 1) cout << i+1 << " ";
    cout << endl;

    return 0;
}