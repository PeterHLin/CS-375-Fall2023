#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

class CourseScheduler {
private:
    vector<int> inDegree;
    vector<vector<int> > adjList;
    int numCourses;

    void buildGraph(const vector<pair<int, int> >& prerequisites) {
        inDegree.resize(numCourses, 0);
        adjList.resize(numCourses);

        for (auto& pre : prerequisites) {
            adjList[pre.second].push_back(pre.first);
            inDegree[pre.first]++;
        }
    }

public:
    CourseScheduler(int n) : numCourses(n) {}

    int findMinSemesters(const vector<pair<int, int> >& prerequisites) {
        buildGraph(prerequisites);
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        int semesters = 0;
        while (!q.empty()) {
            int courseCount = q.size();
            semesters++;
            for (int i = 0; i < courseCount; ++i) {
                int course = q.front();
                q.pop();
                for (int nextCourse : adjList[course]) {
                    if (--inDegree[nextCourse] == 0) {
                        q.push(nextCourse);
                    }
                }
            }
        }

        for (int i : inDegree) {
            if (i > 0) {
                return -1; // Indicates a cycle
            }
        }
        return semesters;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " inputFile.txt outputFile.txt" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Error: Unable to open input file " << argv[1] << endl;
        return 1;
    }

    ofstream outputFile(argv[2]);
    if (!outputFile) {
        cerr << "Error: Unable to open output file " << argv[2] << endl;
        inputFile.close();
        return 1;
    }

    const int numCourses = 15;
    CourseScheduler scheduler(numCourses);
    vector<pair<int, int> > prerequisites;

    int a, b;
    while (inputFile >> a >> b) {
        prerequisites.push_back(make_pair(a, b));
    }
    inputFile.close();

    auto start = high_resolution_clock::now();
    int minSemesters = scheduler.findMinSemesters(prerequisites);
    auto end = high_resolution_clock::now();

    if (minSemesters != -1) {
        outputFile << "Minimum number of semesters required: " << minSemesters << endl;
    } else {
        outputFile << "There is a cycle so we can't figure it out" << endl;
    }

    auto duration = duration_cast<microseconds>(end - start);
    outputFile << "Time: " << duration.count() << " ms" << endl;
    outputFile.close();

    return 0;
}
