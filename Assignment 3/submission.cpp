//
// Created by Peter on 10/15/23.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

void floyd(const vector<vector<int > >& graph, vector<vector<int > >& dist, vector<vector<int > >& pred) {
    int N = graph.size();

    // Initialize the distance and predecessor arrays
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dist[i][j] = graph[i][j];
            if (graph[i][j] != INF && i != j) {
                pred[i][j] = i;
            } else {
                pred[i][j] = -1;
            }
        }
    }

    // Floyd-Warshall main loop
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pred[i][j] = pred[k][j];
                }
            }
        }
    }
}



int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " inputFile.txt outputFile.txt" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cout << "Error: Unable to open input file " << argv[1] << endl;
        return 1;
    }

    ofstream outputFile(argv[2]);
    if (!outputFile) {
        cout << "Error: Unable to open output file " << argv[2] << endl;
        return 1;
    }

    int N;  // number of nodes
    inputFile >> N;

    vector<vector<int > > graph(N, vector<int>(N, INF));
    for (int i = 0; i < N; i++) {
        graph[i][i] = 0;  // distance to self is 0
    }

    int i, j, dij;
    while (inputFile >> i >> j >> dij) {
        graph[i-1][j-1] = dij;
        graph[j-1][i-1] = dij;  //undirected graph
    }

    vector<vector<int > > dist(N, vector<int>(N));
    vector<vector<int > > pred(N, vector<int>(N));

    floyd(graph, dist, pred);

    // Printing D and P tables
    outputFile << "D table (shortest distances):" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            outputFile << dist[i][j] << " ";
        }
        outputFile << endl;
    }

    outputFile << "P table (predecessors):" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            outputFile << pred[i][j] << " ";
        }
        outputFile << endl;
    }

    // Extracting the shortest path from #1 to #N
    int start = 0;
    int end = N - 1;

    int start_node = start;
    int end_node = end;

    outputFile << "Shortest path from city #1 to city #" << N << ":" << endl;
    if (dist[start][end] != INF) {
        vector<int> path;
        while (end != start) {
            path.push_back(end + 1);  // adding 1 to get the city number
            end = pred[start][end];
        }
        path.push_back(start + 1);  // adding 1 to get the city number
        reverse(path.begin(), path.end());

        for (int v : path) {
            outputFile << v << " ";
        }
        outputFile << endl;
    } else {
        outputFile << "No path exists between city #1 and city #" << N << "." << endl;
    }

    //total distance

    outputFile << "Total distance from city #1 to " << N << " is: " << endl << dist[start_node][end_node] << endl;
    // Running time
    outputFile << "The running time of the algorithm is O(N^3)." << endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
