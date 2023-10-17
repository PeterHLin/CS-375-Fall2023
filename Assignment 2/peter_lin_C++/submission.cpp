//
// Created by Peter on 9/25/23.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cfloat>
#include <sstream>
using namespace std;

struct Coords{
    double x, y;
};

//Euclidean distance between two points
double distance(Coords p1, Coords p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

//compare p1 and p2 x coords
bool compareX(Coords p1, Coords p2){
    return p1.x < p2.x;
}
//compare p1 and p2 y coords
bool compareY(Coords& p1, Coords& p2) {
    return p1.y < p2.y;
}

struct ClosestPairResult {
    double i , j;
    double distance;
};

//divide and conquer
ClosestPairResult closestPair(vector<Coords> &points, int left, int right){
    if(right - left <=3) {
        //use brute force if there are less than or equal to 3 points
        ClosestPairResult result;
        result.distance = DBL_MAX;
        for (int i = left; i < right; i++) {
            for (int j = i + 1; j < right; j++) {
                double dist = distance(points[i], points[j]);
                if (dist < result.distance) {
                    result.i = i;
                    result.j = j;
                    result.distance = dist;
                }
            }
        }
        return result;
    }

    int mid = (left + right) / 2;
    ClosestPairResult leftResult = closestPair(points, left, mid);
    ClosestPairResult rightResult = closestPair(points, mid, right);
    ClosestPairResult result  = (leftResult.distance < rightResult.distance) ? leftResult : rightResult;

    //store the points within the strip
    vector<Coords> strip;
    for(int i = left; i <right; i++){
        double x_distance = fabs(points[i].x - points[mid].x);
        if (x_distance < result.distance){
            strip.push_back(points[i]);
        }
    }

    sort(strip.begin(), strip.end(), compareY);

    //find minDistance in strip vector if found
    int stripSize = strip.size();
    for (int i = 0; i <stripSize; i++){
        for(int j = i + 1; j < stripSize && (strip[j].y - strip[i].y ) < result.distance; j++){
            double dist = distance(strip[i], strip[j]);
            if (dist < result.distance) {
                result.i = i;
                result.j = j;
                result.distance = dist;
            }
        }
    }

    return result;
}

double closestPairBruteForce(vector<Coords>& point){
    int n = point.size();

    double minDistance = DBL_MAX;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            minDistance = min(minDistance, distance (point[i], point[j]));
        }
    }

    return minDistance;
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

    vector<Coords> inputCoords;
    string line;
    while (getline(inputFile, line)) {
        string x, y, z;
        istringstream iss(line);
        Coords n;
        iss >> n.x >> n.y;
        inputCoords.push_back(n);
    }
    inputFile.close();

    sort(inputCoords.begin(), inputCoords.end(), compareX);

    int n = 10000;
    vector<Coords> testOne(n);
    vector<Coords> testTwo(n);

    for (int i = 0; i <n; i++){
        testOne[i].x = n-i;
        testOne[i].y = n-i;
    }

    sort(testOne.begin(), testOne.end(), compareX);

    for (int i = 0; i <n; i++){
        testTwo[i].x = i*i;
        testTwo[i].y = i*i;
    }

    sort(testTwo.begin(), testTwo.end(), compareX);
//
//    //test one
//    auto s1 = chrono::high_resolution_clock::now();
//    ClosestPairResult minDistanceDandCOne = closestPair(testOne, 0, n);
//    auto e1 = chrono::high_resolution_clock::now();
//    auto timeOne = chrono::duration_cast<chrono::microseconds>(e1 - s1);
//    cout << "Execution time for Test One (Divide and Conquer): " << timeOne.count() << " ms" << endl;
//
//    auto s2 = chrono::high_resolution_clock::now();
//    double minDistanceBFOne = closestPairBruteForce(testOne);
//    auto e2 = chrono::high_resolution_clock::now();
//    auto timeTwo = chrono::duration_cast<chrono::microseconds>(e2 - s2);;
//    cout << "Execution time for Test One (Brute Force): " << timeTwo.count() << " ms" << endl;
//
//    //test one
//    outputFile << minDistanceDandCOne.i << " " << minDistanceDandCOne.j << " " << minDistanceDandCOne.distance << endl;
//
//
//    //test two
//    auto s3 = chrono::high_resolution_clock::now();
//    ClosestPairResult minDistanceDandCTwo = closestPair(testTwo, 0, n);
//    auto e3 = chrono::high_resolution_clock::now();
//    auto timeThree = chrono::duration_cast<chrono::microseconds>(e3 - s3);
//    cout << "Execution time for Test Two (Divide and Conquer): " << timeThree.count() << " ms" << endl;
//
//    auto s4 = chrono::high_resolution_clock::now();
//    double minDistanceBFTwo = closestPairBruteForce(testTwo);
//    auto e4 = chrono::high_resolution_clock::now();
//    auto timeFour = chrono::duration_cast<chrono::microseconds>(e4 - s4);
//    cout << "Execution time for Test Two (Brute Force): " << timeFour.count() << " ms" << endl;
//
//    //test two
//    outputFile << minDistanceDandCTwo.i << " " << minDistanceDandCTwo.j << " " << minDistanceDandCTwo.distance << endl;


    //test input
    int m = inputCoords.size();
    auto start_time = chrono::high_resolution_clock::now();
    ClosestPairResult minDistanceDandCInput = closestPair(inputCoords, 0, m);
    auto end_time = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<chrono::microseconds>( end_time - start_time);
    cout << "Execution time for Test Input (Divide and Conquer): " << elapsed_time.count() << " ms" << endl;

    auto start_time_two = chrono::high_resolution_clock::now();
    double minDistanceBFInput = closestPairBruteForce(inputCoords);
    auto end_time_two = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::microseconds>(end_time_two - start_time_two);
    cout << "Execution time for Test Input (Brute Force): " << time.count() << " ms" << endl;

    outputFile << minDistanceDandCInput.i << " " << minDistanceDandCInput.j << " " << minDistanceDandCInput.distance << endl;

    outputFile.close();

    return 0;
}

