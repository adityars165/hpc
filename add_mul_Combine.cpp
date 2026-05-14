#include <iostream>
#include <omp.h>

using namespace std;

// ================= VECTOR ADDITION =================

void vectorAddition() {

    int n;

    cout << "\n===== VECTOR ADDITION =====\n";

    cout << "Enter size of vectors: ";

    cin >> n;

    int *A = new int[n];
    int *B = new int[n];
    int *C = new int[n];

    cout << "Enter elements of A:\n";

    for (int i = 0; i < n; i++)
        cin >> A[i];

    cout << "Enter elements of B:\n";

    for (int i = 0; i < n; i++)
        cin >> B[i];

    // Parallel Vector Addition
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {

        C[i] = A[i] + B[i];
    }

    cout << "\nResultant Vector:\n";

    for (int i = 0; i < n; i++)
        cout << C[i] << " ";

    cout << endl;

    delete[] A;
    delete[] B;
    delete[] C;
}

// ================= MATRIX MULTIPLICATION =================

void matrixMultiplication() {

    int rowsA, colsA, rowsB, colsB;

    cout << "\n===== MATRIX MULTIPLICATION =====\n";

    cout << "Enter rows and columns of Matrix A: ";

    cin >> rowsA >> colsA;

    cout << "Enter rows and columns of Matrix B: ";

    cin >> rowsB >> colsB;

    if (colsA != rowsB) {

        cout << "Matrix multiplication not possible!" << endl;

        return;
    }

    int *A = new int[rowsA * colsA];
    int *B = new int[rowsB * colsB];
    int *C = new int[rowsA * colsB];

    cout << "Enter elements of Matrix A:\n";

    for (int i = 0; i < rowsA * colsA; i++)
        cin >> A[i];

    cout << "Enter elements of Matrix B:\n";

    for (int i = 0; i < rowsB * colsB; i++)
        cin >> B[i];

    // Parallel Matrix Multiplication
    #pragma omp parallel for
    for (int i = 0; i < rowsA; i++) {

        for (int j = 0; j < colsB; j++) {

            int sum = 0;

            for (int k = 0; k < colsA; k++) {

                sum += A[i * colsA + k] * B[k * colsB + j];
            }

            C[i * colsB + j] = sum;
        }
    }

    cout << "\nResultant Matrix C:\n";

    for (int i = 0; i < rowsA; i++) {

        for (int j = 0; j < colsB; j++) {

            cout << C[i * colsB + j] << " ";
        }

        cout << endl;
    }

    delete[] A;
    delete[] B;
    delete[] C;
}

// ================= MAIN FUNCTION =================

int main() {

    // Vector Addition
    vectorAddition();

    // Matrix Multiplication
    matrixMultiplication();

    return 0;
}

/*

========================= SAMPLE INPUT =========================

===== VECTOR ADDITION =====

Enter size of vectors: 3

Enter elements of A:
1 2 3

Enter elements of B:
4 5 6


===== MATRIX MULTIPLICATION =====

Enter rows and columns of Matrix A: 2 2

Enter rows and columns of Matrix B: 2 2

Enter elements of Matrix A:
1 2 3 4

Enter elements of Matrix B:
5 6 7 8


========================= SAMPLE OUTPUT =========================

===== VECTOR ADDITION =====

Resultant Vector:
5 7 9


===== MATRIX MULTIPLICATION =====

Resultant Matrix C:
19 22
43 50

*/
