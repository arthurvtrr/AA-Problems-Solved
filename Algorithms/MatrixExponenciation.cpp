#include <bits/stdc++.h>
#define SIZE 2
#define ll long long int

using namespace std;

ll M;

struct Matrix{
    ll mat[SIZE][SIZE];
    Matrix() { memset(mat, 0,sizeof(mat));};
    Matrix operator * (const Matrix & in) const {
        Matrix aux;
        for(int i = 0; i < SIZE;i++){
            for(int j = 0;j < SIZE;j++){
                for(int k = 0; k < SIZE;k++){
                    aux.mat[i][j] = (mat[i][k] * in.mat[k][j] + aux.mat[i][j]);
                }
            }
        }
        return aux;
    }
};

Matrix matExpo(Matrix x, ll y){

	Matrix result;
	if(y <= 1) return x;

	result = matExpo(x, y/2);
	result = result * result;
	if(y % 2 == 1) result = result * x;
	return result;
}
