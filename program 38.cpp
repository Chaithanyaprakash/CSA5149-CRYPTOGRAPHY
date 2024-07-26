#include <stdio.h>
#include <stdlib.h>
#define N 3  
void getKeyMatrix(int plaintext[][N], int ciphertext[][N], int keyMatrix[][N]);
int findDeterminant(int matrix[][N], int n);
void getCofactor(int matrix[][N], int temp[][N], int p, int q, int n);
void adjoint(int matrix[][N], int adjointMatrix[][N]);
int modInverse(int a, int m);
void inverseMatrix(int matrix[][N], int inverseMatrix[][N]);
void printMatrix(int matrix[][N]);
int main() {
    int plaintext[N][N] = {
        {6, 24, 1},
        {13, 16, 10},
        {20, 17, 15}
    };

    int ciphertext[N][N] = {
        {8, 5, 10},
        {21, 18, 21},
        {21, 18, 21}
    };

    int keyMatrix[N][N];

    getKeyMatrix(plaintext, ciphertext, keyMatrix);

    printf("The Key Matrix is:\n");
    printMatrix(keyMatrix);

    return 0;
}

void getKeyMatrix(int plaintext[][N], int ciphertext[][N], int keyMatrix[][N]) {
    int inversePlaintext[N][N];
    inverseMatrix(plaintext, inversePlaintext);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            keyMatrix[i][j] = 0;
            for (int k = 0; k < N; k++) {
                keyMatrix[i][j] += inversePlaintext[i][k] * ciphertext[k][j];
            }
            keyMatrix[i][j] = keyMatrix[i][j] % 26;
            if (keyMatrix[i][j] < 0) {
                keyMatrix[i][j] += 26;
            }
        }
    }
}

int findDeterminant(int matrix[][N], int n) {
    int determinant = 0;
    if (n == 1) {
        return matrix[0][0];
    }

    int temp[N][N];
    int sign = 1;

    for (int f = 0; f < n; f++) {
        getCofactor(matrix, temp, 0, f, n);
        determinant += sign * matrix[0][f] * findDeterminant(temp, n - 1);
        sign = -sign;
    }

    return determinant;
}

void getCofactor(int matrix[][N], int temp[][N], int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = matrix[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

void adjoint(int matrix[][N], int adjointMatrix[][N]) {
    if (N == 1) {
        adjointMatrix[0][0] = 1;
        return;
    }

    int sign = 1;
    int temp[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            getCofactor(matrix, temp, i, j, N);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adjointMatrix[j][i] = (sign * findDeterminant(temp, N - 1)) % 26;
            if (adjointMatrix[j][i] < 0) {
                adjointMatrix[j][i] += 26;
            }
        }
    }
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = -m; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 0;
}

void inverseMatrix(int matrix[][N], int inverseMatrix[][N]) {
    int determinant = findDeterminant(matrix, N);
    int inverseDeterminant = modInverse(determinant, 26);

    if (inverseDeterminant == 0) {
        printf("Inverse doesn't exist\n");
        exit(1);
    }

    int adjointMatrix[N][N];
    adjoint(matrix, adjointMatrix);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            inverseMatrix[i][j] = (adjointMatrix[i][j] * inverseDeterminant) % 26;
            if (inverseMatrix[i][j] < 0) {
                inverseMatrix[i][j] += 26;
            }
        }
    }
}

void printMatrix(int matrix[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

