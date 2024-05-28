#include <bits/stdc++.h>
using namespace std;

class Matrix {
    public:
    int m, n;
    vector<vector<float>> matrix;

    Matrix(int m = 1, int n = 1) {
        this->m = m;
        this->n = n;
        matrix = vector<vector<float>>(m, vector<float>(n));
    }

    void input() {
        cout << "Enter the values for a " << m << "x" << n << " matrix:" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << "Enter element at position (" << i + 1 << "),(" << j + 1 << "): ";
                cin >> matrix[i][j];
            }
        }
    }

    Matrix operator*(Matrix &det) {
        if (n != det.m) {
            cout << "Error in matrix order" << endl;
            return Matrix(0, 0);
        }
        Matrix r(m, det.n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < det.n; j++) {
                float s = 0;
                for (int k = 0; k < n; k++) {
                    s += matrix[i][k] * det.matrix[k][j];
                }
                r.matrix[i][j] = s;
            }
        }
        return r;
    }

    void print() {
        cout << "Matrix " << m << "x" << n << ":" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "Enter m and n values of A and B matrix" << endl;
    int m, n;
    cin >> m >> n;
    Matrix A = Matrix(m, n);
    A.input();
    Matrix B = Matrix(n, m);
    B.input();
    Matrix C = Matrix();
    C = A * B;
    cout << "The A matrix is:" << endl<<endl;
    A.print();
    cout << "The B matrix is:" << endl<<endl;
    B.print();
    cout << "The C matrix i.e. A * B is:" << endl<<endl;
    C.print();
    return 0;
}
