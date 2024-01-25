#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream>

using namespace std;
typedef vector<double> Vector;
typedef vector<Vector> Matrix;

using Matrix = vector<vector<double> >;
using Vector = vector<double>;

class Simplex {
private:
    Matrix A; //c of the constraints
    Vector B; //c of the constraints right-hand side
    Vector C; //c of the objective function
    double V; //value of the objective function

    //index of the most negative value in the objective function coefficients
    int findPivotColumn() const {
        auto it = min_element(C.begin(), C.end());
        return *it < 0 ? distance(C.begin(), it) : -1;
    }

    //find the row for the pivot
    int findPivotRow(int pivotCol) const {
        int index = -1;
        double minRatio = std::numeric_limits<double>::max();
        for (size_t i = 0; i < B.size(); ++i) {
            if (A[i][pivotCol] > 0) {
                double ratio = B[i] / A[i][pivotCol];
                if (ratio < minRatio) {
                    minRatio = ratio;
                    index = i;
                }
            }
        }
        return index;
    }

    //pivot it
    void pivot(int pivotRow, int pivotCol) {
        double pivotValue = A[pivotRow][pivotCol];
        int cols = A[0].size();

        //normalize the pivot row
        for (double &elem : A[pivotRow]) {
            elem /= pivotValue;
        }
        B[pivotRow] /= pivotValue;

        //eliminate the pivot column in other rows
        for (size_t i = 0; i < A.size(); ++i) {
            if (i != pivotRow) {
                double factor = A[i][pivotCol];
                for (int j = 0; j < cols; ++j) {
                    A[i][j] -= factor * A[pivotRow][j];
                }
                B[i] -= factor * B[pivotRow];
            }
        }

        //uddate the objective function and value
        double coefficient = C[pivotCol];
        for (int j = 0; j < cols; ++j) {
            C[j] -= coefficient * A[pivotRow][j];
        }
        V += coefficient * B[pivotRow];
    }

public:
    Simplex(const Matrix& inputA, const Vector& inputB, const Vector& inputC)
            : A(inputA), B(inputB), C(inputC), V(0) {}

    void solve() {
        while (true) {
            int pivotCol = findPivotColumn();
            if (pivotCol == -1) break; // Solution found

            int pivotRow = findPivotRow(pivotCol);
            if (pivotRow == -1) break; // Unbounded solution

            pivot(pivotRow, pivotCol);
        }
    }

    double getOptimalValue() const { return V; }
    Vector getSolution() const { return B; }

    void printTable(std::ostream& os) const {
        for (const auto& row : A) {
            for (double val : row) {
                os << val << " ";
            }
            os << endl;
        }
        for (double val : B) {
            os << "| " << val << endl;
        }
        for (double val : C) {
            os << val << " ";
        }
        os << "| " << V << endl;
    }
};
int main() {
    ofstream outFile("output.txt");

    // First problem
    Matrix A1(2, Vector(5, 0));
    A1[0][0] = 60; A1[0][1] = 12; A1[0][2] = 10; A1[0][3] = 1; A1[0][4] = 0;
    A1[1][0] = 60; A1[1][1] = 6;  A1[1][2] = 30; A1[1][3] = 0; A1[1][4] = 1;
    Vector B1(2, 0);
    B1[0] = 0.12; B1[1] = 0.15;
    Vector C1(5, 0);
    C1[0] = -300; C1[1] = -36; C1[2] = -90; C1[3] = 0; C1[4] = 0;

    Simplex solver1(A1, B1, C1);
    auto start1 = chrono::high_resolution_clock::now();
    solver1.solve();
    auto end1 = chrono::high_resolution_clock::now();
    solver1.printTable(outFile);

    auto duration1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
    outFile << "Solution for the first problem:" << endl;
    outFile << "Max Z = " << solver1.getOptimalValue() << endl;
    for (size_t i = 0; i < B1.size(); i++) {
        outFile << "x" << (i + 1) << " = " << solver1.getSolution()[i] << endl;
    }
    outFile << "Running time: " << duration1 << " microseconds" << endl;
    outFile << endl;

    // Second problem
    Matrix A2(4, Vector(7, 0));
    A2[0][0] = 3; A2[0][1] = 2; A2[0][2] = 5; A2[0][3] = 1; A2[0][4] = 0; A2[0][5] = 0; A2[0][6] = 0;
    A2[1][0] = 2; A2[1][1] = 1; A2[1][2] = 1; A2[1][3] = 0; A2[1][4] = 1; A2[1][5] = 0; A2[1][6] = 0;
    A2[2][0] = 1; A2[2][1] = 1; A2[2][2] = 3; A2[2][3] = 0; A2[2][4] = 0; A2[2][5] = 1; A2[2][6] = 0;
    A2[3][0] = 5; A2[3][1] = 2; A2[3][2] = 4; A2[3][3] = 0; A2[3][4] = 0; A2[3][5] = 0; A2[3][6] = 1;

    Vector B2(4, 0);
    B2[0] = 55; B2[1] = 26; B2[2] = 30; B2[3] = 57;

    Vector C2(7, 0);
    C2[0] = -20; C2[1] = -10; C2[2] = -15; C2[3] = 0; C2[4] = 0; C2[5] = 0; C2[6] = 0;

    Simplex solver2(A2, B2, C2);
    auto start2 = chrono::high_resolution_clock::now();
    solver2.solve();
    auto end2 = chrono::high_resolution_clock::now();
    solver2.printTable(outFile);

    auto duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
    outFile << "Solution for the second problem:" << endl;
    outFile << "Max Z = " << solver2.getOptimalValue() << endl;
    for (size_t i = 0; i < B2.size(); i++) {
        outFile << "x" << (i + 1) << " = " << solver2.getSolution()[i] << endl;
    }
    outFile << "Running time: " << duration2 << " microseconds" << endl;

    outFile.close();

    return 0;
}
