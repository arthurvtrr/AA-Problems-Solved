#include <stdio.h>
#include <algorithm>

using namespace std;

int n, nums[110000], dp[110000];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &nums[i]);

    int aux = 0;
	for (int i = 1; i <= n; i++) {
		aux = min(aux, nums[i]-i);
        dp[i] = aux + i;
	}
	aux = n+1;
	for (int i = n; i >= 1; i--) {
		aux = min(aux, nums[i]+i);
		dp[i] = min(dp[i], aux - i);
    }

	int sol = 0;
	for (int i = 1; i <= n; i++)
		sol = max(sol, dp[i]);

	printf("%d\n", sol);
	return 0;
}
