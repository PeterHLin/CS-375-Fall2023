#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int timeCounter = 0;

enum EdgeType { TREE, FORWARD, BACKWARD, CROSS };

void DFS_Visit(int node, vector<vector<int> >& adjList, vector<int>& color, vector<int>& discovery, vector<int>& finish,
               vector<int>& parent, vector<EdgeType>& edgeType) {
    color[node] = 1;
    discovery[node] = ++timeCounter;

    for(int neighbor : adjList[node]) {
        if(color[neighbor] == 0) {
            parent[neighbor] = node;
            edgeType[neighbor] = TREE;
            DFS_Visit(neighbor, adjList, color, discovery, finish, parent, edgeType);
        } else if(color[neighbor] == 1) {
            edgeType[neighbor] = BACKWARD;
        } else {
            if(discovery[node] < discovery[neighbor]) {
                edgeType[neighbor] = FORWARD;
            } else {
                edgeType[neighbor] = CROSS;
            }
        }
    }

    color[node] = 2;
    finish[node] = ++timeCounter;
}

int main() {
    clock_t start, end;
    start = clock();

    int n = 8; // Number of nodes
    vector<vector<int> > adjList(n+1);

    // Add edges according to your graph
    adjList[1].push_back(4);
    adjList[1].push_back(2);
    adjList[1].push_back(7);
    adjList[2].push_back(4);
    adjList[2].push_back(7);
    adjList[2].push_back(3);
    adjList[3];
    adjList[4].push_back(8);
    adjList[5].push_back(2);
    adjList[5].push_back(3);
    adjList[6].push_back(4);
    adjList[6].push_back(2);
    adjList[6].push_back(5);

    vector<int> color(n+1, 0), discovery(n+1, 0), finish(n+1, 0), parent(n+1, -1);
    vector<EdgeType> edgeType(n+1, CROSS);

    for(int i = 1; i <= n; i++) {
        if(color[i] == 0) {
            DFS_Visit(i, adjList, color, discovery, finish, parent, edgeType);
        }
    }

    // Printing the results
    for(int i = 1; i <= n; i++) {
        cout << "Node " << i << ": Discovery Time = " << discovery[i] << ", Finishing Time = " << finish[i] << ", ";
        switch(edgeType[i]) {
            case TREE: cout << "Edge Type: TREE"; break;
            case FORWARD: cout << "Edge Type: FORWARD"; break;
            case BACKWARD: cout << "Edge Type: BACKWARD"; break;
            case CROSS: cout << "Edge Type: CROSS"; break;
            default: cout << "Edge Type: UNKNOWN"; break;
        }
        cout << endl;
    }

    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken: " << fixed << time_taken << setprecision(5) << " sec" << endl;
    return 0;
}
