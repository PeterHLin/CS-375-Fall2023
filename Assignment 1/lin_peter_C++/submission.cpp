//
// Created by Peter Lin on 9/13/23.
//

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

bool binarySearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return true;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return false;
}

string findKeyWithDifference(const vector<int>& arr) {
    int n = arr.size();
    vector<int> sortedArr = arr;
    sort(sortedArr.begin(), sortedArr.end());

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int diff = abs(sortedArr[j] - sortedArr[i]);
            if (binarySearch(arr, diff)) {
                return to_string(diff);
            }
        }
    }

    return "";
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

    vector<int> arr;
    int num;

    while (inputFile >> num) {
        arr.push_back(num);
    }

    if (findKeyWithDifference(arr).empty()) {
        outputFile.close();
    }
    else
        outputFile << findKeyWithDifference(arr);
        outputFile.close();

    return 0;
}
