#include <stdio.h>

int n, max = -128, mat[110][110], x;

void solve(int x, int y) {
	for (int i = x; i < n; i++) {
		int sum = 0;
		for (int j = y; j < n; j++)
			sum += mat[i][j];	
		if (max < sum) max = sum;
	}			 
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int sum = 0;
		for (int j = 0; j < n; j++) {
			scanf("%d", &x);
			sum += x;
			mat[i][j] = sum;
		}
	}
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			solve(i,j);

	printf("%d\n", max);
	return 0;
}
