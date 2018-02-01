#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >
#define INF 100000000

int n, nums[110], pos[60];
vector < int > primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
vector < int > lft[1 << 16], factors[60];
pii dp[101][1 << 16];

bool prime(int u) {
    for (int v : primes)
        if (v == u)
            return true;
    return false;
}

pii solve(int ind, int mask) {
	if (dp[ind][mask] != pii(0, 0)) return dp[ind][mask];
    if (ind == n) return pii(0, 0);

    pii ret = pii(1, solve(ind+1, mask).second + nums[ind] - 1);

    for (int v : lft[mask]) {
        int newm = mask;
        for (int f : factors[v])
            newm |= 1 << pos[f];

        pii x = solve(ind+1, newm);
        if (x.second + abs(nums[ind] - v) < ret.second) {
            ret.first = v;
            ret.second = x.second + abs(nums[ind] - v);
        }
    }

	return dp[ind][mask] = ret;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &nums[i]);

	for (int i = 0; i < (1 << 16); i++)
		for (int j = 2; j < 59; j++) {
			bool valid = true;
			for (int k = 0; k < 16; k++)
				if ((i & (1 << k)) && j % primes[k] == 0)
					valid = false;

			if (valid) lft[i].push_back(j);
		}

    for (int i = 2; i < 59; i++)
        for (int j = 2; j <= i; j++)
            if (prime(j) && i % j == 0)
                factors[i].push_back(j);

    int cont = 0;
    for (int v : primes)
        pos[v] = cont++;

	solve(0, 0);

    pii aux = dp[0][0];
    int ind = 0, mask = 0;

    while (aux.first != 0) {
        if (ind) printf(" ");
        printf("%d", aux.first);

        if (aux.first == 1) aux = dp[ind+1][mask];
        else {
            for (int f : factors[aux.first])
                mask |= 1 << pos[f];
            aux = dp[ind+1][mask];
        }
        ind++;
    }
    printf("\n");

	return 0;
}
