#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

void printMatrix(vector<vector<long double>>& A){
    cout << "\n_________\n";
    for(int i = 0; i < A.size(); i++){
        for(int j = 0; j < A[i].size(); j++){
            cout << A[i][j] << "   ";
        }
        cout << '\n';
    }
    cout << "__________\n";
}

void printVector(vector<long double>& B){
    cout << "\n__________\n";
    for(int i = 0; i < B.size(); i++){
        cout << B[i] << "   ";
    }
    cout << "\n__________\n";
}

void gauss(vector<vector<long double>> A, vector<long double> B){
    for (int k = 1; k < A.size(); k++)
    {
        for(int i = k; i < A.size(); i++){
            long double coef = A[i][k-1];
            for (int j = k-1; j < A[i].size(); j++){
                A[i][j] -= A[k-1][j] * (coef / A[k-1][k-1]); 
            }
            B[i] -= B[k-1] * (coef / A[k-1][k-1]);
            printMatrix(A);
            printVector(B);
        }
    }
}

int main(){
    vector<vector<long double>> A = {
        {1, 2, 3},
        {4, 5, 6},
        {1, 10, 7},
    };
    vector<long double> B = {4, 2, 1};
    if (A.size() == B.size()){
        gauss(A, B);
    }
    else{
        cout << "Sizes don't match";
    }
    return 0;
}