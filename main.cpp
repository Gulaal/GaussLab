#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<math.h>
#include<iosfwd>
#include<fstream>

using namespace std;

const long double DELTA = 1e-10;

bool isZero(long double value) {
    return fabs(value) < DELTA;
}

int getColumnWidth(const vector<vector<long double>>& matrix, int col) {
    int maxWidth = 0;
    for (const auto& row : matrix) {
        if (col < row.size()) {
            ostringstream oss;
            oss << fixed << setprecision(6) << row[col];
            int width = oss.str().length();
            if (width > maxWidth) {
                maxWidth = width;
            }
        }
    }
    return maxWidth;
}

void printMatrix(const vector<vector<long double>>& matrix, const string& title = "") {
    if (!title.empty()) {
        cout << title << ":" << endl;
    }
    
    if (matrix.empty()) {
        cout << "Empty matrix" << endl;
        return;
    }
    
    vector<int> colWidths;
    for (int col = 0; col < matrix[0].size(); col++) {
        colWidths.push_back(getColumnWidth(matrix, col));
    }
    
    for (const auto& row : matrix) {
        cout << "| ";
        for (int col = 0; col < row.size(); col++) {
            cout << setw(colWidths[col]) << fixed << setprecision(6) << row[col] << " ";
        }
        cout << "|" << endl;
    }
    cout << endl;
}

void printVector(vector<long double>& B){
    cout << "\n__________\n";
    for(int i = 0; i < B.size(); i++){
        cout << B[i] << "                 ";
    }
    cout << "\n__________\n";
}

vector<long double> gauss(vector<vector<long double>> A, vector<long double>& B){
    int n = B.size();

    for (int i = 0; i < n; i++){
        A[i].push_back(B[i]);
    }

    for (int c = 0; c < n; c++){
        int maxRow = c;
        for (int i = 0; i < n; i++){
            if (fabs(A[i][c]) > fabs(A[maxRow][c])){
                maxRow = c;
            }
        }

        swap(A[c], A[maxRow]);

        if (fabs(A[c][c]) < DELTA){
            continue;
        }

        long double coef = A[c][c];
        for(int j = 0; j <= n; j++){
            A[c][j] /= coef;
        }

        for(int i = c + 1; i < n; i++){
            long double coef = A[i][c];
            for(int j = c; j <= n; j++){
                A[i][j] -= coef * A[c][j];
            } 
        }
        printMatrix(A);
    }

    for (int i = 0; i < n; i++) {
        bool allZero = true;
        for (int j = 0; j < n; j++) {
            if (!isZero(A[i][j])) {
                allZero = false;
                break;
            }
        }
        if (allZero && !isZero(A[i][n])) {
            throw runtime_error("Система не имеет решений");
        }
    }
    
    int rankA = 0;
    for (int i = 0; i < n; i++) {
        bool nonZeroRow = false;
        for (int j = 0; j < n; j++) {
            if (!isZero(A[i][j])) {
                nonZeroRow = true;
                break;
            }
        }
        if (nonZeroRow) rankA++;
    }
    
    int rankAB = 0;
    for (int i = 0; i < n; i++) {
        bool nonZeroRow = false;
        for (int j = 0; j <= n; j++) {
            if (!isZero(A[i][j])) {
                nonZeroRow = true;
                break;
            }
        }
        if (nonZeroRow) rankAB++;
    }
    
    if (rankA < rankAB) {
        throw runtime_error("Система имеет бесконечно много решений");
    }

    vector<long double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = A[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
    }

    return x;
}

int main(){
    try {
        vector<vector<long double>> A1 = {{1, 2}, {1, 2}};
        vector<long double> b1 = {3, 4};
        vector<long double> x1 = gauss(A1, b1);
        cout << "Решение системы 1: ";
        for (long double val : x1) cout << val << " ";
        cout << endl;
    } catch (const exception& e) {
        cout << "Система 1: " << e.what() << endl;
    }

    try {
        vector<vector<long double>> A2 = {{1, 2}, {2, 4}};
        vector<long double> b2 = {3, 6};
        vector<long double> x2 = gauss(A2, b2);
        cout << "Решение системы 2: ";
        for (long double val : x2) cout << val << " ";
        cout << endl;
    } catch (const exception& e) {
        cout << "Система 2: " << e.what() << endl;
    }
    
    try {
        vector<vector<long double>> A3 = {{2, 1}, {1, -1}};
        vector<long double> b3 = {5, 2};
        vector<long double> x3 = gauss(A3, b3);
        cout << "Решение системы 3: ";
        for (long double val : x3) cout << val << " ";
        cout << endl;
    } catch (const exception& e) {
        cout << "Система 3: " << e.what() << endl;
    }

    return 0;
}