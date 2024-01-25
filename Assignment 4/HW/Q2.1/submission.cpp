#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool dfs(int node, vector<int>* adjList, vector<bool>& visited, vector<int>& parent) {
    visited[node] = true;

    for(int neighbor : adjList[node]) {
        if(!visited[neighbor]) {
            parent[neighbor] = node;
            if(dfs(neighbor, adjList, visited, parent))
                return true;
        }
        else if(parent[node] != neighbor)
            return true;
    }

    return false;
}

int main() {
    clock_t start, end;
    start = clock();

    int n = 6; // Number of nodes for graph (i)
    vector<int> adjList[n];

    // Add edges according to graph (i)
    adjList[0].push_back(1); // x1 - y1
    adjList[0].push_back(3); // x1 - y2
    adjList[1].push_back(0); // y1 - x1
    adjList[1].push_back(2); // y1 - x2
    adjList[1].push_back(4); // y1 - x3
    adjList[2].push_back(1); // x2 - y1
    adjList[2].push_back(3); // x2 - y2
    adjList[2].push_back(5); // x2 - y3
    adjList[3].push_back(0); // y2 - x1
    adjList[3].push_back(2); // y2 - x2
    adjList[4].push_back(1); // x3 - y1
    adjList[4].push_back(5); // x3 - y3
    adjList[5].push_back(2); // y3 - x2
    adjList[5].push_back(4); // y3 - x3

    vector<bool> visited(n, false);
    vector<int> parent(n, -1);

    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            if(dfs(i, adjList, visited, parent)) {
                cout << "Cycle detected:" << endl;
                int cycle_end = i;
                int cycle_start = parent[i];
                while(cycle_start != cycle_end) {
                    cout << cycle_start << " <- ";
                    cycle_start = parent[cycle_start];
                }
                cout << cycle_end << endl;

                end = clock();
                double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
                cout << "Time taken: " << fixed << time_taken << setprecision(5) << " sec" << endl;
                return 0;
            }
        }
    }

    cout << "No cycle detected." << endl;
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken: " << fixed << time_taken << setprecision(5) << " sec" << endl;
    return 0;
}
