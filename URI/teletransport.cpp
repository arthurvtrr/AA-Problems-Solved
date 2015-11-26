#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>

using namespace std;

#define SIZE 102
#define M 10000

struct Matrix {
    int mat[SIZE][SIZE];
    Matrix() {
        memset(mat, 0, sizeof(mat));
    };
    Matrix operator * (const Matrix & in) const {
        Matrix aux;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < SIZE; k++) {
                    aux.mat[i][j] = (mat[i][k] * in.mat[k][j] + aux.mat[i][j]);
                    aux.mat[i][j] %= M;
                }
            }
        }
        return aux;
    }
};

Matrix matExpo(Matrix x, int y) {
	Matrix result;
	if(y <= 1) return x;

	result = matExpo(x, y/2);
	result = result * result;
	if(y % 2 == 1) result = result * x;
	return result;
}

int main() {
    int n, l, s, t, x, y, w, z;
    while (scanf("%d %d", &n, &l) != EOF) {
        scanf("%d %d", &s, &t);
        Matrix adjM;
        for (int i = 1; i <= n; i++) {
            scanf("%d %d %d %d", &x, &y, &w, &z);
            adjM.mat[i][x]++;
            adjM.mat[i][y]++;
            adjM.mat[i][w]++;
            adjM.mat[i][z]++;
        }

        if (s == t && l == 0)
            printf("1\n");
        else if (l == 0)
            printf("0\n");
        else {
            Matrix aux = matExpo(adjM, l);
            printf("%d\n", aux.mat[s][t]);
        }
    }

    return 0;
}
