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

    int n = 4; // Number of nodes for graph (ii)
    vector<int> adjList[n];

    // Add edges according to graph (ii)
    adjList[0].push_back(1); // a - b
    adjList[0].push_back(2); // a - c
    adjList[0].push_back(3); // a - d
    adjList[1].push_back(0); // b - a
    adjList[1].push_back(2); // b - c
    adjList[1].push_back(3); // b - d
    adjList[2].push_back(0); // c - a
    adjList[2].push_back(1); // c - b
    adjList[2].push_back(3); // c - d
    adjList[3].push_back(0); // d - a
    adjList[3].push_back(1); // d - b
    adjList[3].push_back(2); // d - c


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
