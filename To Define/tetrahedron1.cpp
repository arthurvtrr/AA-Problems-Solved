#include <bits/stdc++.h>

using namespace std;

//Multiply matrix a and b. put result in c. Result mod M
void matmult(long long  a[][2], long long  b[][2], long long c[][2], long long  M) {
    int i, j, k;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            c[i][j] = 0;
            for (k = 0; k < 2; k++) {
                c[i][j] += (a[i][k] * b[k][j]);
                c[i][j] = c[i][j] % M;
            }
        }
    }
}

//find (Z^n) % M and return result in ans
void matpow(long long Z[][2], int n, long long ans[][2], long long M) {

    long long temp[2][2];
    //assign ans = the identity matrix
    ans[0][0] = 1;
    ans[1][0] = 0;
    ans[0][1] = 0;
    ans[1][1] = 1;
    int i, j;
    while (n > 0) {
        if (n & 1) {
            matmult(ans, Z, temp, M);
            for (i = 0; i < 2; i++)
                for (j = 0; j < 2; j++)
                    ans[i][j] = temp[i][j];
        }
        matmult(Z, Z, temp, M);
        for (i = 0; i < 2; i++)
            for(j = 0; j < 2; j++)
                Z[i][j] = temp[i][j];

        n = n / 2;
    }
    return;
}

long long fib(long long n) {
    long long Z[2][2] = {{1,1},{1,0}}, result[2][2];
    long long res;
    matpow(Z, n-2, result, INT_MAX);
    res = result[0][0] * 1 + result[0][1] * 1;
    return res;
}

int main() {
    long long n, M;
    while (scanf("%lld %lld", &n, &M) != EOF)
        printf("%d\n", fib(fib(n)) % M);

    return 0;
}
